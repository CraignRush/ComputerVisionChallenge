function [D, R, T] = disparity_map(scene_path, varargin)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    
    %% Input parser
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('do_debug', false, @islogical);
    P.addOptional('method','jo',@ischar);
    
    % Lese den Input
    P.parse(varargin{:});
    
    do_debug = P.Results.do_debug;
    
    %% Do some typical error checking here
    if do_debug
        dbstop if error;
    end
    
    if ~exist(scene_path,'dir')
        error(['Please provide an existing scene path. "', scene_path, ...
            '" does not exists according to Matlab.']);
    end
    
    if ~exist([scene_path '/im0.png'],'file')
        error('Please provide a path with a file called: im0.png');
    end
    
    if ~exist([scene_path '/im1.png'],'file')
        error('Please provide a path with a file called: im1.png');
    end
    
    if ~exist([scene_path '/calib.txt'],'file')
        error('Please provide a path with a file called: calib.txt');
    end
    
    %% Load images and calibration file from scene folder
    im0 = imread([scene_path '/im0.png']);
    im0g= rgb_to_gray(im0);
    im1 = imread([scene_path '/im1.png']);
    im1g= rgb_to_gray(im1);
    cal = fileread([ scene_path '/calib.txt']);

    if do_debug
        fig = figure('Name',['Computer Vision - ' scene_path], ...
            'NumberTitle','off'); %, 'WindowState','minimized');
        tabgp = uitabgroup(fig);
        tab = uitab(tabgp, 'Title', 'Original');
        tax = axes('Parent', tab(end));
        imshow([im0,im1],'Parent',tax(end),'InitialMagnification','fit');
    end
    %% Create calibration variables
    evalc(cal);
    
    %% High pass filter
    im0g_fft = fftshift(fft2(im0g));
    im1g_fft = fftshift(fft2(im1g));
    
    filter_percentage = 0.01;
    im0g_fft_fil = im0g_fft;
    im0g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
    im0g_fil = uint8(real(ifft2(fftshift(im0g_fft_fil))));

    im1g_fft_fil = im1g_fft;
    im1g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
    im1g_fil = uint8(real(ifft2(fftshift(im1g_fft_fil))));
    
    %% Feature extraction
    % Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
    
    har_det = @(img) harris_detektor(img,'segment_length',9,'k',0.05, ...
        'min_dist',30,'N',20);
    
    feature0 = [har_det(im0g_fil), har_det(im0g)]; 
    feature1 = [har_det(im1g_fil), har_det(im1g)]; 
    
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Harris Detection')];
        tax = [tax,axes('Parent', tab(end))];
        title 'Harris detection';
        imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
        plot(tax(end), feature0(1,:),feature0(2,:),'g+'); 
        plot(tax(end), feature1(1,:)+size(im0g,2),feature1(2,:),'g+');  
    end
    
    %% Correspondence estimation - Find Match

    
    correspondence = punkt_korrespondenzen_jo(im0g,im1g,feature0,feature1,'min_corr', 0.85, 'do_plot', false);
    

    %%
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Correspondence')];
        tax = [tax,axes('Parent', tab(end))];

        title 'Correspondence Estimation';

        imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
        plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
        % plot the line
        for i=1:size(correspondence,2)
            pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
            pt2 = [correspondence(2,i), correspondence(4,i)];
            line(tax(end),pt1,pt2);
        end
    end

    %% Correspondence estimation - Find Robust Match
    %  Find robust correspondence point pairs with RANSAC-algorithm
    correspondence = F_ransac(correspondence, 'tolerance', 0.1);
    
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Correspondence (Robust)')];
        tax = [tax,axes('Parent', tab(end))];

        title 'Correspondence Estimation';

        imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
        plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
        % plot the line
        for i=1:size(correspondence,2)
            pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
            pt2 = [correspondence(2,i), correspondence(4,i)];
            line(tax(end),pt1,pt2);
        end
    end

    
    %% Calculate essential matrix E
    E = achtpunktalgorithmus(correspondence,cam0, cam1);
    
    %% Calculate possible T and R
    [T1, R1, T2, R2, ~, ~] = TR_aus_E(E);
    
    %% Calculate correct euklidian transformation and 3D reconstruction
    [T, R,lambda,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
        cam0, cam1, false);

    x1 = cam0 \ [correspondence(1:2,:); ones(1, size(correspondence,2))];
    P1 = bsxfun(@times, lambda(:,1)', x1);
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Reconstruction')];
        tax = [tax,axes('Parent', tab(end))];
        title '3D Reconstruction';
        hold on
        for i = 1:size(P1,2)
            scatter3(tax(end),P1(1,i), P1(2,i), P1(3,i), '.k');
            text(tax(end),P1(1,i), P1(2,i), P1(3,i),num2str(i));
        end

        % Store edge values
        camC1 = [-0.2,0.2,0.2,-0.2;0.2,0.2,-0.2,-0.2;1,1,1,1];

        % Calculate values for C2 via euklidian transformations...
        camC2 = R \ (bsxfun(@plus, camC1, -T));

        % Calculate camera plane positions (closing the plane)
        cam1_plane = camC1(:,[1:4 1]);
        cam2_plane = camC2(:,[1:4 1]);

        % Plot camera plane
        plot3(tax(end),cam1_plane(1,:), cam1_plane(2,:), cam1_plane(3,:), 'b');
        text(tax(end),cam1_plane(1,4), cam1_plane(2,4), cam1_plane(3,4), 'C1');
        plot3(tax(end),cam2_plane(1,:), cam2_plane(2,:), cam2_plane(3,:), 'r');
        text(tax(end),cam2_plane(1,4), cam2_plane(2,4), cam2_plane(3,4), 'C2');


        % Set camera position
        campos(tax(end),[43, -22, -87]);
        camup(tax(end),[0,-1,0]);

        % Add grid and axis label
        xlabel('x'); ylabel('y'); zlabel('z');
        grid on;
    end
    
    %% Define Params
    j = 1;
    switch j
            case 0 
                %% Dummy Params
                 scale = [100 150]; window = 3; disparity_max = 10;% < 30s
            case 1
                %% Fast Params
                scale = [217 356]; window = 5; disparity_max = 30;% < 30s
                
            case 2
                %% Medium Dense Params
                scale = [434,713]; window = 15; disparity_max = 75;% < 5 min
                
            case 3
                %% Very Dense Params
                scale =[868, 1426] ; window = 35; disparity_max = 100;% ~ 2 h
                
            case 4
                %% Ultra Dense Params
                scale = 1; window = 49; disparity_max = 200;% ~ inf d
                
        end
    
    %% Resize Images
        %% Shrink images
        if prod(scale) < numel(im0g)
            im0g_scaled = interpolateImage(im0g, scale);
            im1g_scaled = interpolateImage(im1g, scale);
        else
            im0g_scaled = im0g;
            im1g_scaled = im1g;
        end
    
    %% Calculate Disparity Map 
    D_ = denseMatch(im0g_scaled, im1g_scaled,  window,0, disparity_max);
    D = interpolateImage(D_,size(im0g));

    %% Depth Calculation
    I_3d = cam1(1,1) * baseline ./ D; % baseline = norm(T,2)???
    %% Scale disparity map
    scale_factor = 127 / max(abs(min(D,[],'all')),abs(max(D,[],'all')));
    D = D * scale_factor + 127;
    
    %% Plot disparity map and 3D scene
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Disparity')];
        tax = [tax,axes('Parent', tab(end))];
        title 'Disparity Map';
        imshow(D,[0 255],'Parent',tax(end));
        colormap(tax(end),jet);
        colorbar;
        
        tab = [tab,uitab(tabgp, 'Title', '3D')];
        tax = [tax,axes('Parent', tab(end))];
        title '3D Reconstruction';
        surf(tax(end),I_3d);
        colormap jet; colorbar
    end
end