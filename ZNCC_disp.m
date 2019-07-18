% Testscript

%% Load

addpath(genpath('lib')); 

scene_path = 'test/sword';
im0 = imread([scene_path '/im0.png']);
im0g= rgb_to_gray(im0);
im1 = imread([scene_path '/im1.png']);
im1g= rgb_to_gray(im1);

%% Fast Params
scale = [195 288]; window = 5; disparity_max = 30;% ~ 15s

%% Dense Params
%scale = 0.3; window = 17; disparity_max = 70;% ~ 15 min

%% Shrink images
im0_small = interpolateImage(im0g,scale);
im1_small = interpolateImage(im1g,scale);

%% Compute Disparity
% window = 5;
% disparity_max = 30; %200*scale;
[dispMap, timeTaken]=denseMatch(im0_small, im1_small, window,0, disparity_max, 'ZNCC');

%%
fprintf("Time taken: %02.0f:%02.0f:%02.3f \n",timeTaken/3600,timeTaken/60,mod(timeTaken,60));

%% 

disp_norm = uint8((dispMap - min(dispMap(:))) ./ max([dispMap - min(dispMap(:))]) .* 255);
figure; imagesc(disp_norm); colormap hot;

%% Scale up
disp_big = interpolateImage(disp_norm,size(im0g));
figure; subplot(121); image(im0);subplot(122); imagesc(disp_big); colormap hot;
