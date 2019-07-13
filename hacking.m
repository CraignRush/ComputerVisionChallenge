%%
scene_path = 'test/motorcycle';
im0 = imread([scene_path '/im0.png']);
im0g= rgb_to_gray(im0);
im1 = imread([scene_path '/im1.png']);
im1g= rgb_to_gray(im1);

fig = figure('Name',['Computer Vision - ' scene_path], ...
    'NumberTitle','off'); %, 'WindowState','minimized');
tabgp = uitabgroup(fig);
tab(1) = uitab(tabgp, 'Title', 'Original');
tax(1) = axes('Parent', tab(1));
imshow([im0,im1],'Parent',tax(1),'InitialMagnification', 'fit');

%%
im0g_fft = fftshift(fft2(im0g));
im1g_fft = fftshift(fft2(im1g));

%%
tab(2) = uitab(tabgp, 'Title', 'FFT2');
tax(2) = axes('Parent', tab(2));
imagesc(log2(abs([im0g_fft,im1g_fft])),'Parent',tax(2));

%%
im0g_fft_fil = im0g_fft;
im0g_fft_fil(floor(end/2-end*0.1):ceil(end/2+end*0.1),floor(end/2-end*0.1):ceil(end/2+end*0.1)) = 0;
im0g_fil = real(ifft2(fftshift(im0g_fft_fil)));

im1g_fft_fil = im1g_fft;
im1g_fft_fil(floor(end/2-end*0.1):ceil(end/2+end*0.1),floor(end/2-end*0.1):ceil(end/2+end*0.1)) = 0;
im1g_fil = real(ifft2(fftshift(im1g_fft_fil)));

%%
tab(3) = uitab(tabgp, 'Title', 'Filtered');
tax(3) = axes('Parent', tab(3));
imshow([im0g_fil,im0g_fil],'Parent',tax(3));

%%
im0bw = im0g;
im0bw(im0bw>128) = 255;
im0bw(im0bw<=128) = 0;
im1bw = im1g;
im1bw(im1bw>128) = 255;
im1bw(im1bw<=128) = 0;

tab(4) = uitab(tabgp, 'Title', 'Discrete');
tax(4) = axes('Parent', tab(4));
imshow([im0bw,im1bw],'Parent',tax(4));

%% Feature extraction
% Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
feature0 = harris_detektor( im0g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 ); 
feature1 = harris_detektor( im1g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 );

%%
tab(5) = uitab(tabgp, 'Title', 'Harris Detection');
tax(5) = axes('Parent', tab(5));
imshow(uint8([im0g,im1g]), 'Parent',tax(5)); hold on;
plot(tax(5),[feature0(1,:),feature1(1,:)+size(im0g,2)],[feature0(2,:),feature1(2,:)],'go'); 

%% Correspondence estimation
% Optionally adD: 'window_length',25,'min_corr', 0.90
correspondence = punkt_korrespondenzen(im0g,im1g,feature0,feature1, ...
    'min_corr', 0.99, 'do_plot', false);

%% Plot Correspondence
tab(6) = uitab(tabgp, 'Title', 'Correspondence');
tax(6) = axes('Parent', tab(6));

title 'Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(6)); hold on;
plot(tax(6),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(6),pt1,pt2);
end

%% Find robust correspondence point pairs with RANSAC-algorithm
correspondence = F_ransac(correspondence, 'tolerance', 0.1);

%% Plot robust Correspondence
tab(7) = uitab(tabgp, 'Title', 'Correspondence (Robust)');
tax(7) = axes('Parent', tab(7));

title 'Robust Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(7)); hold on;
plot(tax(7),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(7),pt1,pt2);
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
        
W=ufdwt(1,window_size,1);
im0c = double(im0);
im1c = double(im1);
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
   gradients0(i_pt,4:3+gweight) = W * double(im0g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   gradients0(i_pt,4+gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients0(i_pt,5:gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients0(i_pt,6:gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   gradients0(i_pt,(7+gweight):(7+2*gweight)) = W * double(im0g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))'; 
   gradients0(i_pt, (7+2*gweight):end) = pt;
end
for i_pt = 1:length(feature1)
   pt = feature1(:,i_pt);
   pt = [pt(2),pt(1)];   
   gradients1(i_pt,1) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
   gradients1(i_pt,2) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
   gradients1(i_pt,3) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
   gradients1(i_pt,4:3+gweight) = W * double(im1g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   gradients1(i_pt,4+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients1(i_pt,5+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients1(i_pt,6+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   gradients1(i_pt,(7+gweight):(7+2*gweight)) = W * double(im1g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))';
   gradients1(i_pt,(7+2*gweight):end) = pt;
end

%%
corresp = inf(length(feature0),length(feature1));

for i1 = 1:length(feature0)
    for i2 = 1:length(feature1)
        corresp(i1,i2) = norm(gradients0(i1,:)/norm(gradients0(i1,:)) - ...
            gradients1(i2,:)/norm(gradients1(i2,:)),1);
    end
end
%%
[vals, indxs] = min(corresp,[],1);

indxs(vals>10) = []; % Select threshold
vals(vals>10) = [];
[svals,sindxs] = sort(vals);
%%
max_corresp = 100;
correspons = zeros(min([max_corresp,length(svals)]),2);
for i = 1:size(correspons,1)
    correspons(i,1) = sindxs(i);
    [m, j] = min(corresp(:,sindxs(i)));
    correspons(i,2) = j;
end

%%
correspondence_ = zeros(4,size(correspons,1));
for i = 1:size(correspons,1)
    correspondence_(:,i) = [feature0(:,correspons(i,2)); feature1(:,correspons(i,1))];
end

%% Plot
tab(8) = uitab(tabgp, 'Title', 'Correspondence (Own)');
tax(8) = axes('Parent', tab(8));
title 'Own Correspondence Estimation';
imshow(uint8([im0g,im1g]),'Parent',tax(8)); hold on;
plot(tax(8),[correspondence_(1,:),correspondence_(3,:)+size(im0g,2)], ...
    [correspondence_(2,:),correspondence_(4,:)],'go');
for i=1:size(correspondence_,2)
    pt1 = [correspondence_(1,i), correspondence_(3,i)+size(im0g,2)];
    pt2 = [correspondence_(2,i), correspondence_(4,i)];
    line(tax(8),pt1,pt2);
end
    
%%
I1 = im0g; I2 = im1g;
points1 = detectHarrisFeatures(I1);
points2 = detectHarrisFeatures(I2);


[f1, vpts1] = extractFeatures(I1, points1);
[f2, vpts2] = extractFeatures(I2, points2);



indexPairs = matchFeatures(f1, f2) ;
matchedPoints1 = vpts1(indexPairs(1:20, 1));
matchedPoints2 = vpts2(indexPairs(1:20, 2));

tab(9) = uitab(tabgp, 'Title', 'Correspondence (Matlab)');
tax(9) = axes('Parent', tab(9));
showMatchedFeatures(I1,I2,matchedPoints1,matchedPoints2,'montage','Parent',tax(9));
title(tax(9), 'Candidate point matches');
legend(tax(9), 'Matched points 1','Matched points 2');

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
tab(10) = uitab(tabgp, 'Title', 'Reconstruction (Own)');
tax(10) = axes('Parent', tab(10));
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