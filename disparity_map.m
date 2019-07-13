function [D, R, T] = disparity_map(scene_path, varargin)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    
    %% Input parser
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('do_debug', false, @islogical);
    P.addOptional('method','daniel',@isstring);
    
    % Lese den Input
    P.parse(varargin{:});
    
    do_debug = P.Results.do_debug;
    method   = P.Results.method;
    
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
        imshow([im0,im1],'Parent',tax(end));
    end
    %% Create calibration variables
    evalc(cal);
    
    %% Feature extraction
    % Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
    im0bw = im0g; threshold0 = median(im0g,'all');
    im0bw(im0bw>threshold0) = 255;
    im0bw(im0bw<=threshold0) = 0;
    im1bw = im1g; threshold1 = median(im1g,'all');
    im1bw(im1bw>threshold1) = 255;
    im1bw(im1bw<=threshold1) = 0;
    do_extract_color_feature = do_debug & ~do_debug;
    
    feature0 = harris_detektor( im0bw, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 ); 
    feature0 = [feature0,harris_detektor( im0g, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 )]; 
    if do_extract_color_feature
        feature0 = [feature0,harris_detektor( im0(:,:,1), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )]; 
        feature0 = [feature0,harris_detektor( im0(:,:,2), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )]; 
        feature0 = [feature0,harris_detektor( im0(:,:,3), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )]; 
    end
    feature1 = harris_detektor( im1bw, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 );
    feature1 = [feature1, harris_detektor( im1g, 'segment_length', 9, 'k', 0.05, ...
        'min_dist', 30, 'N', 20 )];
    if do_extract_color_feature
        feature1 = [feature1, harris_detektor( im1(:,:,1), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )];
        feature1 = [feature1, harris_detektor( im1(:,:,2), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )];
        feature1 = [feature1, harris_detektor( im1(:,:,3), ...
            'segment_length', 9, 'k', 0.05, 'min_dist', 30, 'N', 20 )];
    end
    
    if do_debug
        tab = [tab,uitab(tabgp, 'Title', 'Harris Detection')];
        tax = [tax,axes('Parent', tab(end))];
        title 'Harris detection';
        imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
        plot(tax(end), feature0(1,:),feature0(2,:),'g+'); 
        plot(tax(end), feature1(1,:)+size(im0g,2),feature1(2,:),'g+');  
    end
    
    %% Correspondence estimation - Find Match

    fm_method = 'NN';
    if strcmp(method, 'matlabgrader')
        correspondence = correspondence_matlabgrader(im0g,im1g,feature0, feature1);
    elseif strcmp(method,'daniel')
        sig0 = correspondence_daniel(im0g,im0,feature0,'gray_weight',6,'pos_weight',1);
        sig1 = correspondence_daniel(im1g,im1,feature1,'gray_weight',6,'pos_weight',1);
        fm_method = 'NN';
    elseif strcmp(method,'ct')
        sig0 = correspondence_ct(im0g,feature0,'window_size',9);
        sig1 = correspondence_ct(im1g,feature1,'window_size',9);
        fm_method = 'Hamming';
    elseif strcmp(method,'lpm')
        sig0 = correspondence_lpm(im0g,feature0);
        sig1 = correspondence_lpm(im1g,feature1);
        fm_method = 'NN';
    end
    
    if ~exist('correspondence','var')
        correspondence = find_matches(sig0,sig1,feature0,feature1,fm_method);
    end
    %% Correspondence estimation - Find Robust Match
    
    %  Find robust correspondence point pairs with RANSAC-algorithm
    correspondence = F_ransac(correspondence, 'tolerance', 0.4);
    
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

    %% Calculate essential matrix E
    E = achtpunktalgorithmus(correspondence,cam0, cam1);
    
    %% Calculate possible T and R
    [T1, R1, T2, R2, ~, ~] = TR_aus_E(E);
    
    %% Calculate correct euklidian transformation and 3D reconstruction
    [T, R,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
        cam0, cam1, false);

    
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