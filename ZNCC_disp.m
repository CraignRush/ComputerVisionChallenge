% Testscript

%% Specify vars
addpath(genpath('lib'));
scene_path = {'test/motorcycle', 'test/playground', ...
    'test/sword',      'test/terrace'   };

for i = 1:length(scene_path)
    close all;
    %% Load images
    im0 = imread([scene_path{i} '/im0.png']);
    im0g= rgb_to_gray(im0);
    im1 = imread([scene_path{i} '/im1.png']);
    im1g= rgb_to_gray(im1);
    
    %% Fast Params
    %scale = 0.1; window = 5; disparity_max = 30;% ~ 15s
    
    %% Medium Dense Params
    scale = 0.3; window = 17; disparity_max = 80;% ~ 15 min
    
    %% Very Dense Params
    %scale = 0.75; window = 35; disparity_max = 100;% ~ ? h
    
    %% Ultra Dense Params
    %scale = 1; window = 49; disparity_max = 200;% ~ ? h
    
    %% Shrink images
    im0_small = interpolateImage(im0g,scale);
    im1_small = interpolateImage(im1g,scale);
    
    %% Compute Disparity
    % window = 5;
    % disparity_max = 30; %200*scale;
    [dispMap, timeTaken]=denseMatch(im0_small, im1_small, window,0, disparity_max, 'ZNCC');
    
    %% Bringing time into a readable format
    fprintf("Time taken: %02.0f:%02.0f:%02.3f \n",timeTaken/3600,timeTaken/60,mod(timeTaken,60));
    
    %% Normalizing image to [0 255]    
    disp_norm = uint8((dispMap - min(dispMap(:))) ./ max([dispMap - min(dispMap(:))]) .* 255);
    
    %% Displaying originally computed disparity map
    figure;subplot(131); imagesc(disp_norm); title('Disparity Small'); colormap hot;
    
    %% Scale up
    disp_big = interpolateImage(disp_norm,size(im0g));
    subplot(1,3,2:3); imagesc([im0g disp_big]);title('Disparity Normal with Reference'); colormap hot;
    
    %% Create storage folder
    folder = ['gen_data_s=' num2str(scale) '_w=' num2str(window)...
        '_mdisp=' num2str(disparity_max)];
    if ~exist(folder,'dir')
        mkdir(folder);
    end
    
    sub = strsplit(scene_path{i},'/');
    path = [folder '/' sub{2}];
    if ~exist(path,'dir')
        mkdir(path);
    end
    
    %% Save Workspace
    save(fullfile(path, 'ws.mat'));
    
    %% Save Figure as MATLAB figure
    savefig(fullfile(path, 'dmap.fig'));
    
    %% Save Figure as .pdf
    print(fullfile(path, 'dmap.pdf'),'-dpdf','-bestfit');
end