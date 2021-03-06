%% Computer Vision Challenge 2019

% Group number:
group_number = 10;

% Group members:
members = {'Michael Maas', 'Alexander Schmaus', 'Johann Brenner', 'Daniel Milz'};

% Email-Address (from Moodle!):
mail = {'ga96vur@mytum.de', 'ga96fin@mytum.de', 'ga78zan@mytum.de', 'ga58huv@mytum.de'};

%% Start timer here
tic;

%% Disparity Map
% Specify path to scene folder containing img0 img1 and calib
scenes = {'test/motorcycle', 'test/playground', ...
          'test/sword',      'test/terrace'   , ...
          'test/teddy'};
scene_path = scenes{1};
 
% Calculate disparity map and Euclidean motion
[D, R, T] = disparity_map(scene_path, 'do_debug', true,'method', 'jo');

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
