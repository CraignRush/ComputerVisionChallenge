function score = stereo_matching_zncc(image_l, image_r, window, disparity)
%% Returns disparity map computed with the zncc algorithm
% Input param: stereo images Left and Right
% Window for computation
% 2-vector minimal and maximal disparity [min max]
% x; % unsigned int
% i, j, y, left, right, wx2, wy2; %int
% p_l, p_r; %float*
% pix_l, pix_r;%float
% mean_l, mean_r,%float*
% pmean_l, pmean_r; % float*
% ncc, den; %double
% sum, sum_l, sum_r; %double
% disp, right_lim, left_lim, ndisp; %int

[height, width] = size(image_l);

if length(window) == 2
    wx = window(1);
    wy = window(2);
else
    wx = window;
    wy = window;
end

if length(disparity) == 2
    disparity_min = disparity(1);
    disparity_max = disparity(2);
else
    disparity_min = 0;
    disparity_max = disparity;
end

score = NaN(height,width,disparity_max-disparity_min);

mean_l = zeros(width, height);
mean_r = zeros(width, height);

[mean_l,mean_r] = compute_means(image_l, image_r, wx, wy, width, height, mean_l, mean_r);

% following line to all sim metrics PIC
% ndisp = disparity_max - disparity_min + 1;
% if (ndisp < 0)
%     ndisp = -ndisp;
% end
% ndisp = ndisp + 1;

wx2 = (wx - 1) / 2;
wy2 = (wy - 1) / 2;
left = wx2;
right = width - wx2;

for disp = disparity_min:disparity_max-1
    
    for y = wy2:(height-wy2-1)
        if (disp < 0)
            p_l = [wx2, y];
            p_r = [wx2 - disp, y];
            pmean_l = [wx2, y];
            pmean_r = [wx2 - disp, y];
        else
            p_l = [wx2 + disp, y];
            p_r = [wx2, y];
            pmean_l = [wx2 + disp, y];
            pmean_r = [wx2, y];
        end
        
        if (disp < 0)
            right_lim = right + disp;
        else
            right_lim = right;
        end
        
        if (disp < 0)
            left_lim = left;
        else
            left_lim = left + disp;
        end
        
        for x = left_lim:right_lim
            sum = 0;
            sum_l = 0;
            sum_r = 0;
            
            % inner matching loop
            for i = -wx2:wx2      % x
                for j = -wy2:wy2 % y
                    pix_l = image_l(p_l(1) + i, pl(2) + j) - mean_l(pmean_l);
                    pix_r = image_r(p_l(1) + i, pl(2) + j) - mean_r(pmean_r);
                    
                    sum = sum + pix_l * pix_r;
                    sum_l = sum_l + pix_l^2;
                    sum_r = sum_r + pix_r^2;
                end
            end
            
            den = sqrt(sum_l * sum_r);
            
            if (den ~= 0)
                ncc = sum / den;
            else
                ncc = INFINITY;
            end
            % following line to all sim metrics PIC
            score(x,y,disp-disparity_min) = ncc;
            
            % C: Shift pointers completly over images
            % MATLAB: 
            p_l = p_l(1) + 1;
            p_r = p_r + 1;
            pmean_l = pmean_l + 1;
            pmean_r = pmean_r + 1;
        end	% for x
    end		% for y
end			% for disparity
end				%/* match_ZNCC_l */



%/***************************************************************************************
%compute_means
%***************************************************************************************/
function [mean_l, mean_r] = compute_means(image_l, image_r, wx, wy, ...
    width, height, mean_l, mean_r)
% % % % % wx2, wy2, x, y, i, j; % int
% % % % % size_sq; %double

size_sq = wx * wy;
wx2 = (wx - 1) / 2;
wy2 = (wy - 1) / 2;

for y = wy2:(height-wy2)-1
    for x = wx2:(width-wx2)-1
        sum_r = 0.0;
        sum_l = 0.0;
        
        for i = -wx2:wx2
            for j = -wy2:wy2
                sum_l = sum_l + image_l(x+i, y+j);
                sum_r = sum_r + image_r(x+i, y+j);
            end
            
            mean_r(x, y)  = sum_r / size_sq;
            mean_l(x, y) = sum_l / size_sq;
        end
    end
end
end
