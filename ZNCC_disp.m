% Testscript

%% Specify vars
addpath(genpath('lib'));
scene_path = {'test/motorcycle', 'test/playground', ...
    'test/sword',      'test/terrace'   };
saveFiles = 0;

for i = 1%1:length(scene_path)
    %% Load images
    im0 = imread([scene_path{i} '/im0.png']);
    im0g= rgb_to_gray(im0);
    im1 = imread([scene_path{i} '/im1.png']);
    im1g= rgb_to_gray(im1);
    
    %% Filter high pass
    %     im0g_fft = fftshift(fft2(im0g));
    %     im1g_fft = fftshift(fft2(im1g));
    %
    %     filter_percentage = 0.05;
    %     im0g_fft_fil = im0g_fft;
    %     im0g_fft_fil(floor(end/2-end*filter_percentage):...
    %         ceil(end/2+end*filter_percentage),...
    %         floor(end/2-end*filter_percentage):...
    %         ceil(end/2+end*filter_percentage)) = 0;
    %     im0g_fil = uint8(real(ifft2(fftshift(im0g_fft_fil))));
    %
    %     im1g_fft_fil = im1g_fft;
    %     im1g_fft_fil(floor(end/2-end*filter_percentage):...
    %         ceil(end/2+end*filter_percentage),...
    %         floor(end/2-end*filter_percentage):...
    %         ceil(end/2+end*filter_percentage)) = 0;
    %     im1g_fil = uint8(real(ifft2(fftshift(im1g_fft_fil))));
    
    for j = 0
        
        switch j
            case 0 
                %% Dummy Params
                 scale = [100 150]; window = 3; disparity_max = 10;% < 30s
            case 1
                %% Fast Params
                scale = [217 356]; window = 5; disparity_max = 30;% < 30s
                
            case 2
                %% Medium Dense Params
                scale = [434,713]; window = 15; disparity_max = 75;% < 5 min
                
            case 3
                %% Very Dense Params
                scale =[868, 1426] ; window = 35; disparity_max = 100;% ~ 2 h
                
            case 4
                %% Ultra Dense Params
                scale = 1; window = 49; disparity_max = 200;% ~ inf d
                
        end
        
        %% Shrink images
        if prod(scale) < numel(im0g)
            im0_small = interpolateImage(im0g, scale);
            im1_small = interpolateImage(im1g, scale);
        else
            im0_small = im0g;
            im1_small = im1g;
        end
        
        %% Compute Disparity
        % window = 5;
        % disparity_max = 30; %200*scale;
        [dispMap, timeTaken]=denseMatch(im0_small, im1_small, window,0, disparity_max, 'ZNCC');
        
        %% Bringing time into a readable format
        fprintf("Time taken: %02.0f:%02.0f:%02.3f \n",timeTaken/3600,timeTaken/60,mod(timeTaken,60));
        
        %% Normalizing image to [0 255]
        disp_norm = uint8((dispMap - min(dispMap(:))) ./ max(dispMap - min(dispMap(:))) .* 255);
        
        %% Displaying originally computed disparity map
        figure;subplot(131); imagesc(disp_norm); title('Disparity Small'); colormap hot;
        
        %% Scale up
        disp_big = interpolateImage(disp_norm,size(im0g));
        subplot(1,3,2:3); imagesc([im0g disp_big]);title('Disparity Normal with Reference'); colormap hot;
        
        
        %% Filter with Gaussian
        
        n = numel(im0);
        mu = 3; sigma = .3;
        segment_length = 15;
        
        % Gaussian Filter
        gaussian = @(x,mu,sigma) 1/(sigma*sqrt(2*pi))*exp(-1/2*((x-mu)/sigma).^2);
        w = gaussian(-floor(segment_length/2):1:floor(segment_length/2),0,segment_length/5);
        w = w/sum(w);
        
        disp_test = double(conv2(w,w,disp_big,'same'));
        disp_test(disp_test < eps) = eps;
        
        %% Filter low pass
%         disp_fft = fftshift(fft2(disp_big));         
%         filter_percentage = 0.9;
%         filter_percentage = filter_percentage/2;
%         disp_fft_fil = disp_fft;
%         disp_fft_fil(floor(1:end/2*filter_percentage):...
%             ceil(1:end/2*filter_percentage),...
%             floor(1:end/2*filter_percentage):...
%             ceil(1:end/2*filter_percentage));
%         disp_fil = uint8(real(ifft2(ifftshift(disp_fft_fil))));
%         
%         disp__fil_norm = uint8((disp_fil) ./ ...
%             max(disp_fil(:)) .* 255);
%         
%         figure;imagesc(disp__fil_norm); colormap hot; colorbar;
%         figure;imagesc(disp_big);

if saveFiles
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
    end
end