function D_map = dmap2(leftI,rightI)
%DMAP2 Summary of this function goes here
%   Detailed explanation goes here


%% High pass filter the image
im0g_fft = fftshift(fft2(leftI));
im1g_fft = fftshift(fft2(rightI));

filter_percentage = 0.05;
im0g_fft_fil = im0g_fft;
im0g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
leftI_fil = uint8(real(ifft2(fftshift(im0g_fft_fil))));

im1g_fft_fil = im1g_fft;
im1g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
rightI_fil = uint8(real(ifft2(fftshift(im1g_fft_fil))));

%% calculate cost matrix  
% C(x,d) = SUM_(i,j) in W    | D1(i,j) - D2(i-d,j) |
% d(x) = argmin_d C(x,d)
% linearInd = sub2ind(matrixSize, rowSub, colSub)

window_size = 9; % 5x5
d_range = [0 200]; % ToDo: Reduce image size!!!
d_list = (d_range(1):d_range(2));

D_map = zeros(size(leftI));

imL = double(leftI_fil);
imR = double(rightI_fil);

last_id = 1;

for i = ceil(window_size/2):floor(size(leftI,1)-floor(window_size/2))
    for j = ceil(window_size/2):floor(size(leftI,2)-floor(window_size/2))
        costs = Inf(1,length(d_list));
        minimum = [];
        for i_d = [last_id:length(d_list),1:last_id]
            costs(i_d) = cost(imL,imR,i,j,d_list(i_d),window_size);
            if costs(i_d) < minimum(1)
                minimum = [costs(i_d), d_list(i_d), i_d];
            else
                
            end
        end
        last_id = minimum(2);
        [~, min_idx] = min(costs);
        D_map(i,j) = d_list(min_idx);
    end
end


end

function C = cost(leftI,rightI,i,j,d,window_size)
    C = norm( descriptor(window(leftI,i,j,window_size)) - ...
        descriptor(window(rightI,i-d,j,window_size)) , 1);
end

function W = window(img,i,j,window_size)          
    x_range = (i-floor(window_size/2)):(i+floor(window_size/2));
    y_range = (j-floor(window_size/2)):(j+floor(window_size/2));
    
    x_range(x_range < 1) = 1;
    x_range(x_range > size(img,1)) = size(img,1);
    y_range(y_range < 1) = 1;
    y_range(y_range > size(img,2)) = size(img,2);
    
    W = img(x_range, y_range);
end

function D = descriptor(window)
    D = (window(:) - mean(window(:))) ./ std(window(:));
end

function C = cost_NCC(leftI,rightI,i,j,d,window_size)
    C = 0;
end