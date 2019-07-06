function [D, R, T] = disparity_map(scene_path)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    
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
    feature0 = harris_detektor( im0g ); 
    feature1 = harris_detektor( im1g );
    
    % figure, imshow(uint8(im0g)); hold on;
    % plot(feature0(1,:),feature0(2,:),'go'); 
    
    % figure, imshow(uint8(im1g)); hold on;
    % plot(feature1(1,:),feature1(2,:),'go'); 
    
    % figure, imshow(uint8(im0g)); hold on;
    % plot(feature0(1,:),feature0(2,:),'go'); imshow(uint8(im1g));
    % alpha(0.5); plot(feature1(1,:),feature1(2,:),'go'); 
    
    %% Correspondence estimation
    % Optionally adD: 'window_length',25,'min_corr', 0.90
    correspondence = punkt_korrespondenzen(im0g,im1g,feature0,feature1,'min_corr', 0.7);
    
    %%  Find robust correspondence point pairs with RANSAC-algorithm
    correspondence_robust = F_ransac(correspondence, 'tolerance', 0.04);
    
    %% Calculate essential matrix E
    E = achtpunktalgorithmus(correspondence_robust,cam0, cam1);
    
    %% Calculate possible T and R
    [T1, R1, T2, R2, ~, ~] = TR_aus_E(E);
    
    %% Calculate correct euklidian transformation and 3D reconstruction
    [T, R,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence_robust, cam0, cam1);
    
    %% Calculate Disparity Map
    D = dmap(im0g, im1g);
end