function [D, R, T] = disparity_map(scene_path)
    % This function receives the path to a scene folder and calculates the
    % disparity map of the included stereo image pair. Also, the Euclidean
    % motion is returned as Rotation R and Translation T.
    
    addpath(genpath('lib')); 
    
    %% Do some typical error checking here
    
    
    %% Load images and calibration file from scene folder
    im0 = imread([scene_path '/im0.png']);
    im1 = imread([scene_path '/im1.png']);
    cal = fileread([ scene_path '/calib.txt']);

    %% Create calibration variables
    evalc(cal);
    
    %% Feature extraction
    feature0 = harris_detektor( rgb_to_gray(im0) );
    feature1 = harris_detektor( rgb_to_gray(im1) );
end