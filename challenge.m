%% Computer Vision Challenge 2019

dbstop if error

% Group number:
group_number = 10;

% Group members:
% members = {'Max Mustermann', 'Johannes Daten'};
members = {'Michael Maas', 'Alexander Schmaus', 'Johann Brenner', 'Daniel Milz'};

% Email-Address (from Moodle!):
% mail = {'ga99abc@tum.de', 'daten.hannes@tum.de'};
mail = {'ga96vur@mytum.de', 'ga96fin@mytum.de', 'ga78zan@mytum.de', 'ga58huv@mytum.de'};

%% Start timer here
tic;

%% Disparity Map
% Specify path to scene folder containing img0 img1 and calib
scene_path = 'test/sword';
 
% Calculate disparity map and Euclidean motion
[D, R, T] = disparity_map(scene_path);

%% Validation
% Specify path to ground truth disparity map
gt_path = [scene_path '/disp0.pfm'];

% Load the ground truth
G = readpfm(gt_path);
G = (G - min(min(G))) ./ max(max((G - min(min(G))))) * 255;
% Estimate the quality of the calculated disparity map
p = verify_dmap(D, G);

%% Stop timer here
elapsed_time = toc;


%% Print Results
disp('Rotation R:'); disp(R);
disp('Translation T:'); disp(T);
disp('PSNR p: '); disp(p);
disp('Elapsed Time: '); disp(elapsed_time);


%% Display Disparity
figure('Name','Disparity Map','NumberTitle','off');
title 'Disparity Map';
imshow(D, [0 255]);
colormap(gca,jet);
colorbar;
