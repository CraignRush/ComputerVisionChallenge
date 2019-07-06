function [D, R, T] = disparity_map(scene_path)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    do_debug = true;
    dbstop if error
    
    %% Do some typical error checking here
    
    
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
    feature0 = harris_detektor( im0g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 ); 
    feature1 = harris_detektor( im1g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 );
    
    if do_debug
        figure('Name','Harris Detection','NumberTitle','off');
        subplot(121); imshow(uint8(im0g)); hold on;
        plot(feature0(1,:),feature0(2,:),'go'); 
        subplot(122); imshow(uint8(im1g)); hold on;
        plot(feature1(1,:),feature1(2,:),'go'); 
        title 'Harris detection';
    end
    
    %% Correspondence estimation
    % Optionally adD: 'window_length',25,'min_corr', 0.90
    correspondence = punkt_korrespondenzen(im0g,im1g,feature0,feature1, ...
        'min_corr', 0.7, 'do_plot', do_debug);
    
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
    % D = dmap(im0g, im1g);
    disparityRange = [-6 10];
    D = disparity(im0g, im1g, 'BlockSize',15, ...
        'DisparityRange',disparityRange);
    
%     if do_debug
%         figure('Name','Disparity Map','NumberTitle','off');
%         title 'Disparity Map';
%         imshow(D, disparityRange);
%         colormap(gca,jet);
%     end
end