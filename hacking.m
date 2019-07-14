addpath(genpath('lib'));

%%
scene_path = 'test/motorcycle';
im0 = imread([scene_path '/im0.png']);
im0g= rgb_to_gray(im0);
im1 = imread([scene_path '/im1.png']);
im1g= rgb_to_gray(im1);
%%
fig = figure('Name',['Computer Vision - ' scene_path], ...
    'NumberTitle','off','WindowStyle','docked');
tabgp = uitabgroup(fig);
tab(1) = uitab(tabgp, 'Title', 'Original');
tax(1) = axes('Parent', tab(1));
imshow([im0,im1],'Parent',tax(1), 'InitialMagnification','fit','Border','tight');

%%
im0g_fft = fftshift(fft2(im0g));
im1g_fft = fftshift(fft2(im1g));

%%
tab = [tab,uitab(tabgp, 'Title', 'FFT2')];
tax = [tax,axes('Parent', tab(end))];
imagesc(log2(abs([im0g_fft,im1g_fft])),'Parent',tax(end));

%%
im0g_fft_fil = im0g_fft;
im0g_fft_fil(floor(end/2-end*0.1):ceil(end/2+end*0.1),floor(end/2-end*0.1):ceil(end/2+end*0.1)) = 0;
im0g_fil = real(ifft2(fftshift(im0g_fft_fil)));

im1g_fft_fil = im1g_fft;
im1g_fft_fil(floor(end/2-end*0.1):ceil(end/2+end*0.1),floor(end/2-end*0.1):ceil(end/2+end*0.1)) = 0;
im1g_fil = real(ifft2(fftshift(im1g_fft_fil)));

%%
tab = [tab,uitab(tabgp, 'Title', 'Filtered')];
tax = [tax,axes('Parent', tab(end))];
imshow([im0g_fil,im0g_fil],'Parent',tax(end),'InitialMagnification', 'fit','Border','tight');

%%
im0bw = im0g;
threshold0 = median(im0g,'all');
im0bw(im0bw>threshold0) = 255;
im0bw(im0bw<=threshold0) = 0;
im1bw = im1g;
threshold1 = median(im1g,'all');
im1bw(im1bw>threshold1) = 255;
im1bw(im1bw<=threshold1) = 0;

tab = [tab,uitab(tabgp, 'Title', 'Discrete')];
tax = [tax,axes('Parent', tab(end))];
imshow([im0bw,im1bw],'Parent',tax(end),'InitialMagnification', 'fit','Border','tight');

%% Feature extraction
% Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
feature0 = harris_detektor(im0g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 ); 
feature1 = harris_detektor(im1g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 );

%%
tab = [tab,uitab(tabgp, 'Title', 'Harris (Own)')];
tax = [tax,axes('Parent', tab(end))];
imshow(uint8([im0g,im1g]), 'Parent',tax(end),'InitialMagnification', 'fit','Border','tight'); hold on;
plot(tax(end),[feature0(1,:),feature1(1,:)+size(im0g,2)],[feature0(2,:),feature1(2,:)],'go'); 

%% Fearure extraction Matlab
feature0_ = detectHarrisFeatures(im0g);
feature1_ = detectHarrisFeatures(im1g);

%%
tab = [tab,uitab(tabgp, 'Title', 'Harris (Matlab)')];
tax = [tax,axes('Parent', tab(end))];
imshow(uint8([im0g,im1g]), 'Parent',tax(end)); hold on;
plot(tax(end),[feature0_.Location(:,1);feature1_.Location(:,1)+size(im0g,2)],[feature0_.Location(:,2);feature1_.Location(:,2)],'go'); 

%%
[f1, vpts1] = extractFeatures(im0g, feature0_); %cornerPoints(feature0'));
[f2, vpts2] = extractFeatures(im1g, feature1_); %cornerPoints(feature1'));

tab = [tab, uitab(tabgp, 'Title', 'Features (Matlab)')];
tax = [tab,axes('Parent', tab(end))];
imshow([im0g,im1g],'Parent',tax(end)); hold on;

vpts1 = vpts1.Location;
vpts2 = vpts2.Location;
%plot(tax(end),[f1_(:,1); f2_(:,1)+size(I1,2)],[f1_(:,2);f2_(:,2)],'g+');
plot(tax(end),[vpts1_(:,1); vpts2_(:,1)+size(I1,2)],[vpts1_(:,2);vpts2_(:,2)],'ro');

%% Correspondence estimation
% Optionally adD: 'window_length',25,'min_corr', 0.90
correspondence = punkt_korrespondenzen(im0g,im1g,feature0,feature1, ...
    'min_corr', 0.99, 'do_plot', false);

%% Plot Correspondence
tab = [tab,uitab(tabgp, 'Title', 'Correspondence')];
tax = [tax,axes('Parent', tab(end))];

title 'Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(end),pt1,pt2);
end

%% Find robust correspondence point pairs with RANSAC-algorithm
correspondence = F_ransac(correspondence, 'tolerance', 0.1);

%% Plot robust Correspondence
tab = [tab,uitab(tabgp, 'Title', 'Correspondence (Robust)')];
tax = [tax,axes('Parent', tab(end))];

title 'Robust Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(end),pt1,pt2);
end

%%
window_size = 11;
indices_tooclose = feature0(1,:) < floor(window_size/2) |...
        (size(im0g,2) - feature0(1,:)) < floor(window_size/2) | ...
        feature0(2,:) < floor(window_size/2) | ...
        (size(im0g,1) - feature0(2,:)) < floor(window_size/2);
feature0(:,indices_tooclose) = [];
    
indices_tooclose = feature1(1,:) < floor(window_size/2) |...
        (size(im1g,2) - feature1(1,:)) < floor(window_size/2) | ...
        feature1(2,:) < floor(window_size/2) | ...
        (size(im1g,1) - feature1(2,:)) < floor(window_size/2);
feature1(:,indices_tooclose) = [];
        
im0c = double(im0);
im1c = double(im1);

%%
W=ufdwt(1,window_size,1);
W=W(ceil(window_size/2),:);
nDirs  = 2; % Directions: x y
gweight = 6;
posweight = 1; %todo...
nChans = 3+gweight; % Channels: red green blue gray gray gray
gradients0 = zeros(length(feature0), nDirs*nChans+2*posweight);
gradients1 = zeros(length(feature1), nDirs*nChans+2*posweight);

for i_pt = 1:length(feature0)
   pt = feature0(:,i_pt);
   pt = [pt(2),pt(1)];
   gradients0(i_pt,1) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
   gradients0(i_pt,2) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
   gradients0(i_pt,3) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
   if gweight > 0
   gradients0(i_pt,4:(3+gweight)) = W * double(im0g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   end
   gradients0(i_pt,4+gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients0(i_pt,5+gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients0(i_pt,6+gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   if gweight > 0
   gradients0(i_pt,(7+gweight):(6+2*gweight)) = W * double(im0g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))'; 
   end
   if posweight > 0
   gradients0(i_pt, (7+2*gweight):end) = repmat(reshape(pt ./ size(im0g),1,[]),1,posweight);
   end
end
for i_pt = 1:length(feature1)
   pt = feature1(:,i_pt);
   pt = [pt(2),pt(1)];   
   gradients1(i_pt,1) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
   gradients1(i_pt,2) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
   gradients1(i_pt,3) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
   if gweight > 0
   gradients1(i_pt,4:3+gweight) = W * double(im1g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   end
   gradients1(i_pt,4+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients1(i_pt,5+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients1(i_pt,6+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   if gweight > 0
   gradients1(i_pt,(7+gweight):(6+2*gweight)) = W * double(im1g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))';
   end
   if posweight > 0
   gradients1(i_pt, (7+2*gweight):end) = repmat(reshape(pt ./ size(im1g),1,[]),1,posweight);
   end
end

%%
corresp = inf(length(feature0),length(feature1));

for i1 = 1:length(feature0)
    for i2 = 1:length(feature1)
        corresp(i1,i2) = norm(gradients0(i1,:)/norm(gradients0(i1,:))-...
            gradients1(i2,:)/norm(gradients1(i2,:)));
    end
end
%%
[~,sindxs] = sort(reshape(corresp,[],1));

%%
max_corresp = 100;
correspondence_ = zeros(4,min([max_corresp,length(sindxs)]));
for i = 1:size(correspondence_,2)
    [i2,j2] = ind2sub(size(corresp),sindxs(i));
    correspondence_(1:2,i) = feature0(:,i2);
    correspondence_(3:4,i) = feature1(:,j2);
end

%% Find robust correspondence point pairs with RANSAC-algorithm
correspondence_ = F_ransac(correspondence_, 'tolerance', 0.1);

%% Plot
tab = [tab,uitab(tabgp, 'Title', 'Correspondence (Own)')];
tax = [tax,axes('Parent', tab(end))];
title 'Own Correspondence Estimation';
imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
plot(tax(end),[correspondence_(1,:),correspondence_(3,:)+size(im0g,2)], ...
    [correspondence_(2,:),correspondence_(4,:)],'go');
for i=1:size(correspondence_,2)
    pt1 = [correspondence_(1,i), correspondence_(3,i)+size(im0g,2)];
    pt2 = [correspondence_(2,i), correspondence_(4,i)];
    line(tax(end),pt1,pt2);
end
    
%% Matlab: Harris
I1 = im0g; I2 = im1g;
points1 = detectHarrisFeatures(I1);
points2 = detectHarrisFeatures(I2);

tab = [tab, uitab(tabgp, 'Title', 'Harris (Matlab)')];
tax = [tab,axes('Parent', tab(end))];
imshow([I1,I2],'Parent',tax(end)); hold on;
points1_ = points1.selectStrongest(50).Location;
points2_ = points2.selectStrongest(50).Location;
plot(tax(end),[points1_(:,1); points2_(:,1)+size(I1,2)],[points1_(:,2);points2_(:,2)],'g+');

%% Matlab: Features
[f1, vpts1] = extractFeatures(I1, points1);
[f2, vpts2] = extractFeatures(I2, points2);

tab = [tab, uitab(tabgp, 'Title', 'Features (Matlab)')];
tax = [tab,axes('Parent', tab(end))];
imshow([I1,I2],'Parent',tax(end)); hold on;
%f1_ = f1.selectStrongest(50).Location;
%f2_ = f2.selectStrongest(50).Location;
vpts1_ = vpts1.selectStrongest(50).Location;
vpts2_ = vpts2.selectStrongest(50).Location;
%plot(tax(end),[f1_(:,1); f2_(:,1)+size(I1,2)],[f1_(:,2);f2_(:,2)],'g+');
plot(tax(end),[vpts1_(:,1); vpts2_(:,1)+size(I1,2)],[vpts1_(:,2);vpts2_(:,2)],'ro');


%% Try own algorithm on Matlab features

correspondence__ = punkt_korrespondenzen2(im0g,im1g,im0c,im1c,round(vpts1_)',round(vpts2_)', 'min_corr', 0.9,'do_plot', false);
   
%% Plot
tab = [tab,uitab(tabgp, 'Title', 'Correspondence (Own)')];
tax = [tab,axes('Parent', tab(end))];
title 'Own Correspondence Estimation';
imshow(uint8([im0g,im1g]),'Parent',tax(end)); hold on;
plot(tax(end),[correspondence__(1,:),correspondence__(3,:)+size(im0g,2)], ...
    [correspondence__(2,:),correspondence__(4,:)],'go');
for i=1:size(correspondence__,2)
    pt1 = [correspondence__(1,i), correspondence__(3,i)+size(im0g,2)];
    pt2 = [correspondence__(2,i), correspondence__(4,i)];
    line(tax(end),pt1,pt2);
end    

%%

indexPairs = matchFeatures(f1, f2) ;
matchedPoints1 = vpts1(indexPairs(1:20, 1));
matchedPoints2 = vpts2(indexPairs(1:20, 2));

tab = [tab, uitab(tabgp, 'Title', 'Correspondence (Matlab)')];
tax = [tax, axes('Parent', tab(end))];
showMatchedFeatures(I1,I2,matchedPoints1,matchedPoints2,'montage','Parent',tax(end));
title(tax(end), 'Candidate point matches');
legend(tax(end), 'Matched points 1','Matched points 2');

%% Calibrate
cal = fileread([ scene_path '/calib.txt']);
evalc(cal);

%% Essential Matrix
E = achtpunktalgorithmus(correspondence_,cam0, cam1);

    
%% Calculate possible T and R
[T1, R1, T2, R2, ~, ~] = TR_aus_E(E);

%% Calculate correct euklidian transformation and 3D reconstruction
[T, R,lambda,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence_, ...
    cam0, cam1, false);

%%
% Draw P1 in figure and label
tab = [tab,uitab(tabgp, 'Title', 'Reconstruction (Own)')];
tax = [tax,axes('Parent', tab(end))];
title '3D Reconstruction';
hold on
P1 = bsxfun(@times, lambda(:,1)', cam1 \ [correspondence_(1:2,:); ones(1, size(correspondence_,2))]);
for i = 1:length(P1)
    scatter3(tax(end),P1(1,i), P1(2,i), P1(3,i), '.k');
    text(tax(end),P1(1,i), P1(2,i), P1(3,i),num2str(i));
end

% Store edge values
camC1 = [-0.2,0.2,0.2,-0.2;0.2,0.2,-0.2,-0.2;1,1,1,1];

% Calculate values for C2 via euklidian transformations...
camC2 = R \ (bsxfun(@plus, camC1, -T));

% Calculate camera plane positions (closing the plane)
cam1_plane = camC1(:,[1:4 1]);
cam2_plane = camC2(:,[1:4 1]);

% Plot camera plane
plot3(tax(end),cam1_plane(1,:), cam1_plane(2,:), cam1_plane(3,:), 'b');
text(tax(end),cam1_plane(1,4), cam1_plane(2,4), cam1_plane(3,4), 'C1');
plot3(tax(end),cam2_plane(1,:), cam2_plane(2,:), cam2_plane(3,:), 'r');
text(tax(end),cam2_plane(1,4), cam2_plane(2,4), cam2_plane(3,4), 'C2');


% Set camera position
campos(tax(end),[43, -22, -87]);
camup(tax(end),[0,-1,0]);

% Add grid and axis label
xlabel('x'); ylabel('y'); zlabel('z');
grid on;