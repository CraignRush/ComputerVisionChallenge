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
filter_percentage = 0.05;
im0g_fft_fil = im0g_fft;
im0g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
im0g_fil = uint8(real(ifft2(fftshift(im0g_fft_fil))));

im1g_fft_fil = im1g_fft;
im1g_fft_fil(floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage),floor(end/2-end*filter_percentage):ceil(end/2+end*filter_percentage)) = 0;
im1g_fil = uint8(real(ifft2(fftshift(im1g_fft_fil))));

%%
tab = [tab,uitab(tabgp, 'Title', 'Filtered')];
tax = [tax,axes('Parent', tab(end))];
imshow([im0g_fil,im0g_fil],'Parent',tax(end),'InitialMagnification', 'fit','Border','tight');

%% Feature extraction
% Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
feature0 = [harris_detektor(im0g_fil, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 ), ...
    harris_detektor(im0g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 )];
feature1 = [harris_detektor(im1g_fil, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 ), ...
    harris_detektor(im1g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 )];


%%
tab = [tab,uitab(tabgp, 'Title', 'Harris (Own)')];
tax = [tax,axes('Parent', tab(end))];
imshow(uint8([im0g,im1g]), 'Parent',tax(end),'InitialMagnification', 'fit','Border','tight'); hold on;
plot(tax(end),[feature0(1,:),feature1(1,:)+size(im0g,2)],[feature0(2,:),feature1(2,:)],'go'); 

%% Fearure extraction Matlab
%feature0_ = detectHarrisFeatures(im0g);
%feature1_ = detectHarrisFeatures(im1g);

%%
%tab = [tab,uitab(tabgp, 'Title', 'Harris (Matlab)')];
%tax = [tax,axes('Parent', tab(end))];
%imshow(uint8([im0g,im1g]),'InitialMagnification', 'fit','Border','tight', 'Parent',tax(end)); hold on;
%plot(tax(end),[feature0_.Location(:,1);feature1_.Location(:,1)+size(im0g,2)],[feature0_.Location(:,2);feature1_.Location(:,2)],'go'); 

%%
%[f1, vpts1] = extractFeatures(im0g, feature0_); %cornerPoints(feature0'));
%[f2, vpts2] = extractFeatures(im1g, feature1_); %cornerPoints(feature1'));
%%
%tab = [tab, uitab(tabgp, 'Title', 'Features (Matlab)')];
%tax = [tab,axes('Parent', tab(end))];
%imshow([im0g,im1g],'Parent',tax(end),'InitialMagnification', 'fit','Border','tight'); hold on;

%plot(tax(end),[f1_(:,1); f2_(:,1)+size(I1,2)],[f1_(:,2);f2_(:,2)],'g+');
%plot(tax(end),[vpts1.Location(:,1); vpts2.Location(:,1)+size(im0g,2)],[vpts1.Location(:,2);vpts2.Location(:,2)],'ro');

%% Correspondence estimation
% Optionally adD: 'window_length',25,'min_corr', 0.90
correspondence = punkt_korrespondenzen_jo(im0g,im1g,feature0,feature1, ...
    'min_corr', 0.95, 'do_plot', false);

%% Plot Correspondence
tab = [tab,uitab(tabgp, 'Title', 'Correspondence')];
tax = [tax,axes('Parent', tab(end))];

title 'Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(end),'InitialMagnification', 'fit','Border','tight'); hold on;
plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(end),pt1,pt2);
end

%% Find robust correspondence point pairs with RANSAC-algorithm
try
    correspondence = F_ransac(correspondence, 'tolerance', 0.04);
catch
end
%% Plot robust Correspondence
tab = [tab,uitab(tabgp, 'Title', 'Correspondence (Robust)')];
tax = [tax,axes('Parent', tab(end))];

title 'Robust Correspondence Estimation';

imshow(uint8([im0g,im1g]),'Parent',tax(end),'InitialMagnification', 'fit','Border','tight'); hold on;
plot(tax(end),[correspondence(1,:),correspondence(3,:)+size(im0g,2)],[correspondence(2,:),correspondence(4,:)],'go');
% plot the line
for i=1:size(correspondence,2)
    pt1 = [correspondence(1,i), correspondence(3,i)+size(im0g,2)];
    pt2 = [correspondence(2,i), correspondence(4,i)];
    line(tax(end),pt1,pt2);
end


%% Calibrate
cal = fileread([ scene_path '/calib.txt']);
evalc(cal);

%% Essential Matrix
E = achtpunktalgorithmus(correspondence,cam0, cam1);

    
%% Calculate possible T and R
[T1, R1, T2, R2, ~, ~] = TR_aus_E(E);

%% Calculate correct euklidian transformation and 3D reconstruction
[T, R,lambda,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
    cam0, cam1, false);

%%
% Draw P1 in figure and label
tab = [tab,uitab(tabgp, 'Title', 'Reconstruction (Own)')];
tax = [tax,axes('Parent', tab(end))];
title '3D Reconstruction';
hold on
P1 = bsxfun(@times, lambda(:,1)', cam1 \ [correspondence(1:2,:); ones(1, size(correspondence,2))]);
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