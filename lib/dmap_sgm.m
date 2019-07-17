function D = dmap_sgm(im0,im1)
% See: https://github.com/epiception/SGM-Census/blob/master/sgm.cpp
% See: https://core.ac.uk/download/pdf/11134866.pdf

    %% Joint probability
    P_01 = histcounts2(im0(:),im1(:),0:258,0:256);
    P_0  = sum(P_01, 2);
    P_1  = sum(P_01, 1);
    %figure, imagesc(P_12); 
    
    %% Parzan Estimation
    n = numel(im0); 
    mu = 0; sigma = 1.3;
    segment_length = 7;
    
    % Gaussian Filter
    gaussian = @(x,mu,sigma) 1/(sigma*sqrt(2*pi))*exp(-1/2*((x-mu)/sigma).^2);
    w = gaussian(-floor(segment_length/2):1:floor(segment_length/2),0,segment_length/5);
    w = w/sum(w);
    
    %% Inner convolution for H 0 1 
    P_x_g = double(conv2(w,w,P_01,'same'));
    P_x_g(P_x_g < eps) = eps;
    
    % Outer convolution for H 0 1
    h_I0I1 = double(-1/n * conv2(w,w,log( P_x_g ), 'same'));
    H_I0I1 = sum(h_I0I1,'all');
    
    %% Inner convolution for H 0
    P_x_g = double(conv(P_0,w,'same'));
    P_x_g(P_x_g < eps) = eps;
    
    % Outer convolution for H 0
    h_I0 = double(-1/n * conv(log( P_x_g ), w, 'same'));
    H_I0 = sum(h_I0,'all');
    
    %% Inner convolution for H 1
    P_x_g = double(conv(P_1,w,'same'));
    P_x_g(P_x_g < eps) = eps;
    
    % Outer convolution for H 1
    h_I1 = double(-1/n * conv(log( P_x_g ), w, 'same'));
    H_I1 = sum(h_I1,'all');
    
    %% Calculate mutal information MI
    MI_I0I1 = H_I0 + H_I1 - H_I0I1;
    mi_I0I1 = repmat(h_I0, size(h_I1)) + repmat(h_I1, size(h_I0)) + h_I0I1;
    
    %% Estimation of C_MI by random D
    d_list = 0:round(size(im0,1)/5);
    D = randi(max(d_list), size(im0));
    C_MI = zeros(n,numel(d_list));
    for p = 1:size(C_MI,1)
        for d = 1:size(C_MI,2)
            % +1 due to intensities of 0, but indices starting at 1
            C_MI(p,d) = -mi_I0I1(im0(p)+1,im1(max(p-d,1))+1);
        end
    end

    %% Calculate disparity energy for D
    P1 = 1;
    P2 = 2;
    all_points = 1:numel(im0);
    E = 0;
    for p = all_points
        E = E + C_MI(p,D(p));
        [p_x, p_y] = ind2sub(size(im0),p);
        q = [sub2ind(size(im0),max(p_x - 1,1), p_y); ...
            sub2ind(size(im0),min(p_x + 1,size(im0,1)), p_y); ...
            sub2ind(size(im0),p_x, max(p_y - 1,1)); ...
            sub2ind(size(im0),p_x, min(p_y + 1,size(im0,2)))];
        E = E + P1*sum(abs(D(p) - D(q))==1) + P2*sum(abs(D(p) - D(q)) > 1);
    end
    
    %% Cost aggregarion
    
    % Scale C with Cmax < 2^11
    s = (2^11-1) / max(C_MI,[],'all');
    
    S = zeros(numel(im0),numel(d_list));
    L = zeros(8, numel(im0), numel(d_list));
    border_pixels = []; % ToDo
    
    % Traversing the paths forward in each direction r (16...)
    for r = 1:8
        last_k = Inf(1,numel(d_list));
        for x = 1:size(im0,1)
            for y = 1:size(im0,2)
                idx = sub2ind(size(im0),x,y);
                
                % If border pixel
                if x==1 || x ==size(im0,1) || y==1 || y==size(im0,2)
                    L(r,idx,:) = s*C_MI(idx,:);
                else
                    [dx_r, dy_r] = r_to_delta(r,8);
                    ind_r = sub2ind(size(im0),x+dx_r,y+dy_r);
                    t1=reshape(L(r,ind_r,:),1,[]);
                    t2=L(r,ind_r,1);
                    t2=[t2, reshape(min(L(r,ind_r,1:end-2),L(r,ind_r,3:end)),1,[])];
                    t2=[t2, L(r,ind_r,end-1)];
                    
                    t1(reshape(L(r,ind_r,:),1,[])<t1-20) = L(r,ind_r,reshape(L(r,ind_r,:),1,[])<t1-20)+20;
                    
                    L(r,idx,:) = C_MI(idx,:)+min(t1,t2)-last_k;
                end
                last_k(reshape(L(r,idx,:),1,[])<last_k) = L(r,idx,reshape(L(r,idx,:),1,[])<last_k);
                
                S(idx,:) = S(idx,:) + reshape(L(r,idx,:),1,[]);
            end
        end
    end
    
    D = S;    
end

%%
function [dx,dy] = r_to_delta(r, r_total)
if nargin < 2
    r_total = 8;
end
if r == r_total/2 
    dx = 0; 
    dy = -1;
elseif r == r_total
    dx = 0;
    dy = 1;
elseif r < r_total/4
    dx = 1;
    dy = 1;
elseif r == r_total/4
    dx = 1;
    dy = 0;
elseif r > r_total/4 && r < r_total/2
    dx = 1;
    dy = -1;
elseif r > r_total/2 && r < r_total*3/4
    dx = -1;
    dy = -1;
elseif r == r_total*3/4
    dx = -1;
    dy = 0;
elseif r > r_total*3/4
    dx = -1;
    dy = 1;
else
    dx = 0;
    dy = 0;
end
end