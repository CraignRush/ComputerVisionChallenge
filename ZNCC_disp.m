% Testscript

%% Load
scene_path = 'test/motorcycle';
im0 = imread([scene_path '/im0.png']);
im0g= rgb_to_gray(im0);
im1 = imread([scene_path '/im1.png']);
im1g= rgb_to_gray(im1);

%% Shrink images
scale = 0.3;
im0_small = interpolateImage(im0g,scale);
im1_small = interpolateImage(im1g,scale);

%% Compute Disparity
window = 15;
disparity_max = 200*scale;
[dispMap, timeTaken]=denseMatch(im0_small, im1_small, window,0, disparity_max, 'ZNCC');

%%
fprintf("Time taken: %02.0f:%02.0f:%02.3f \n",timeTaken/3600,timeTaken/60,mod(timeTaken,60));

%% 

disp_norm = (dispMap - min(dispMap(:))) ./ max([dispMap - min(dispMap(:))]) .* 255;
figure; imagesc(disp_norm); colormap hot;

%% Scale up
disp_big = interpolateImage(disp_norm,5);
figure; imagesc(disp_norm); colormap hot;
