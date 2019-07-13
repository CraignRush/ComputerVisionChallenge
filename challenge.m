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

%% Debugging
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DEBUG_MODE = false;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Disparity Map
% Specify path to scene folder containing img0 img1 and calib
scene_path = 'test/motorcycle';

% Calculate disparity map and Euclidean motion
[D, R, T] = disparity_map(scene_path, 'do_debug', DEBUG_MODE);

%% Validation
% Specify path to ground truth disparity map
if contains(scene_path,'tsukuba')
    gt_path = [scene_path '/disp0.pgm'];
    G = imread(gt_path);
    figure('Name','Disparity Map - Ground Truth','NumberTitle','off');
    title 'Disparity Map - Ground Truth';
    imshow(G, [0 255]);
    colormap(gca,jet);
    colorbar;
else    
    gt_path = [scene_path '/disp0.pfm'];
    % Load the ground truth
    G = readpfm(gt_path);
    G = (G - min(G(:))) ./ max(G(:) - min(G(:))) * 255;
    
    % Estimate the quality of the calculated disparity map
    p = verify_dmap(D, G);
    disp('PSNR p: '); disp(p);
end
%% Stop timer here
elapsed_time = toc;


%% Print Results
disp('Rotation R:'); disp(R);
disp('Translation T:'); disp(T);
fprintf('Elapsed Time: %2.0f:%2.0f\n',elapsed_time/60,mod(elapsed_time,60));


%% Display Disparity
figure('Name','Disparity Map','NumberTitle','off');
title 'Disparity Map';
imshow(D);
colormap(gca,jet);
colorbar;
