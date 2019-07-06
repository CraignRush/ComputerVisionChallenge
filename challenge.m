%% Computer Vision Challenge 2019

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
scene_path = 'test/motorcycle';
 
% Calculate disparity map and Euclidean motion
[D, R, T] = disparity_map(scene_path);

%% Validation
% Specify path to ground truth disparity map
gt_path = 'test/motorcycle/disp0.pfm';

% Load the ground truth
G = readpfm(gt_path);
 
% Estimate the quality of the calculated disparity map
p = validate_dmap(D, G);

%% Stop timer here
elapsed_time = toc;


%% Print Results
disp(R);
disp(T);
disp(p);
disp(elapsed_time);


%% Display Disparity
figure,
imshow(D);
