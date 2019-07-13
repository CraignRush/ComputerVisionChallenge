function [D, R, T] = disparity_map(scene_path, varargin)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    
    %% Input parser
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('do_debug', false, @islogical)
    
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

    %% Create calibration variables
    evalc(cal);
    
    %% Feature extraction
    % Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
    im0bw = im0g; im0bw(im0bw> 128) = 255; 
    im1bw = im1g; im1bw(im1bw<=128) =   0;
    
    feature0 = harris_detektor( im0bw, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 ); 
    feature1 = harris_detektor( im1bw, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 );
    
    if do_debug
        figure('Name','Harris Detection','NumberTitle','off');
        title 'Harris detection';
        ax = subplot(1,2,1); imshow(uint8(im0g)); hold on;
        plot(ax, feature0(1,:),feature0(2,:),'go'); 
        ax = subplot(1,2,2); imshow(uint8(im1g)); hold on;
        plot(ax, feature1(1,:),feature1(2,:),'go');  
    end
    
    %% Correspondence estimation
    % Optionally adD: 'window_length',25,'min_corr', 0.90
    
    % correspondence = punkt_korrespondenzen2(im0g,im1g,feature0,...
    % feature1, 'min_corr', 0.9, 'do_plot', do_debug);
    
    correspondence = punkt_korrespondenzen2(im0g,im1g,double(im0), ...
        double(im1),feature0,feature1, 'min_corr', 0.9, ...
        'do_plot', do_debug);
    %%  Find robust correspondence point pairs with RANSAC-algorithm
    correspondence = F_ransac(correspondence, 'tolerance', 0.04);
    if do_debug
        figure('Name','Robust Correspondence Estimation','NumberTitle','off');
        title 'Robust Correspondence Estimation';
        imshow(uint8(im0g)); hold on
        plot(correspondence(1,:),correspondence(2,:),'go');
        imshow(uint8(im1g)); alpha(0.5);
        plot(correspondence(3,:),correspondence(4,:),'ro')
        for i=1:size(correspondence,2)
            pt1 = [correspondence(1,i), correspondence(3,i)];
            pt2 = [correspondence(2,i), correspondence(4,i)];
            line(pt1,pt2);
        end
    end
    
    %% Calculate essential matrix E
    E = achtpunktalgorithmus(correspondence,cam0, cam1);
    
    %% Calculate possible T and R
    [T1, R1, T2, R2, ~, ~] = TR_aus_E(E);
    
    %% Calculate correct euklidian transformation and 3D reconstruction
    [T, R,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
        cam0, cam1, do_debug);
    
    %% Calculate Disparity Map
   
    if do_debug
        D = disparity(im0g, im1g);
    else
        D = dmap(im0g, im1g);
    end
    
    % Scale
    D(D < -10) = -10;
    D = (D + 10) ./ max(max(D + 10)) * 255;
    
%     if do_debug
%         figure('Name','Disparity Map','NumberTitle','off');
%         title 'Disparity Map';
%         imshow(D, disparityRange);
%         colormap(gca,jet);
%     end
end