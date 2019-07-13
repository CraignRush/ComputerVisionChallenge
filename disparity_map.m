function [D, R, T] = disparity_map(scene_path, varargin)
% This function receives the path to a scene folder and calculates the
% disparity map of the included stereo image pair. Also, the Euclidean
% motion is returned as Rotation R and Translation T.

addpath(genpath('lib'));

%% Input parser
P = inputParser;

% Liste der optionalen Parameter
P.addOptional('do_debug', false, @islogical)

% Lese den Input
P.parse(varargin{:});

do_debug = P.Results.do_debug;

%% Do some typical error checking here
if do_debug
    dbstop if error;
end

if ~exist(scene_path,'dir')
    error(['Please provide an existing scene path. "', scene_path, ...
        '" does not exists according to Matlab.']);
end

if ~exist([scene_path '/im0.png'],'file')
    error('Please provide a path with a file called: im0.png');
end

if ~exist([scene_path '/im1.png'],'file')
    error('Please provide a path with a file called: im1.png');
end

if ~exist([scene_path '/calib.txt'],'file')
    error('Please provide a path with a file called: calib.txt');
end

%% Load images and calibration file from scene folder
im0 = imread([scene_path '/im0.png']);
im0g= rgb_to_gray(im0);
im1 = imread([scene_path '/im1.png']);
im1g= rgb_to_gray(im1);
cal = fileread([ scene_path '/calib.txt']);

%% Create calibration variables
evalc(cal);

%% Feature extraction
disp("Extracting features...");
% Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
im0bw = im0g; im0bw(im0bw >  128) = 255;
im1bw = im1g; im1bw(im1bw <= 128) =   0;

feature0 = harris_detektor( im0bw, 'segment_length', 9, 'k', 0.05, ...
    'min_dist', 30, 'N', 20 );
feature1 = harris_detektor( im1bw, 'segment_length', 9, 'k', 0.05, ...
    'min_dist', 30, 'N', 20 );

if do_debug
    figure('Name','Harris Detection','NumberTitle','off');
    title 'Harris detection';
    ax = subplot(1,2,1); imshow(uint8(im0g)); hold on;
    plot(ax, feature0(1,:),feature0(2,:),'go');
    ax = subplot(1,2,2); imshow(uint8(im1g)); hold on;
    plot(ax, feature1(1,:),feature1(2,:),'go');
end

fprintf("Number of found features: %d, %d\n",size(feature0,2),size(feature1,2));
%% Correspondence estimation
disp("Estimate correspondences...");

% Optionally adD: 'window_length',25,'min_corr', 0.90

% correspondence = punkt_korrespondenzen2(im0g,im1g,feature0,...
% feature1, 'min_corr', 0.9, 'do_plot', do_debug);

correspondence = punkt_korrespondenzen2(im0g,im1g,double(im0), ...
    double(im1),feature0,feature1, 'min_corr', 0.9, ...
    'do_plot', do_debug);

fprintf("Number of found correspondences: %d\n", size(correspondence,2));

%%  Find robust correspondence point pairs with RANSAC-algorithm
disp("Selecting for robust correspondences...");

correspondence = F_ransac(correspondence, 'tolerance', 0.04);
if do_debug
    figure('Name','Robust Correspondence Estimation','NumberTitle','off');
    title 'Robust Correspondence Estimation';
    imshow(uint8(im0g)); hold on
    plot(correspondence(1,:),correspondence(2,:),'go');
    imshow(uint8(im1g)); alpha(0.5);
    plot(correspondence(3,:),correspondence(4,:),'ro')
    for i=1:size(correspondence,2)
        pt1 = [correspondence(1,i), correspondence(3,i)];
        pt2 = [correspondence(2,i), correspondence(4,i)];
        line(pt1,pt2);
    end
end

fprintf("Number of robust correspondences: %d\n", size(correspondence,2));

%% Calculate essential matrix E
disp("Calculating E...");
E = achtpunktalgorithmus(correspondence,cam0, cam1);

%% Epipolar Lines TEST
x = correspondence(1,:);
y = correspondence(2,:);
x2 = correspondence(3,:);
y2 = correspondence(4,:);
color = ['r','g','b','c','y','m','k'];

[Dl,~] = eig(E*E');
el = Dl(:,1)./Dl(3,1);
[Dr,~] = eig(E'*E);
er = Dr(:,1)./Dr(3,1);

%plot epipolar lines
figure(4)
imagesc(im0bw);
colormap(gray);
figure(5)
imagesc(im1bw)
colormap(gray)
xx = 0:size(im1bw,2);

for i =1:size(correspondence)-1
    temp = E*[x(i) y(i) 1]';
    temp = temp./temp(3);
    yy = - temp(1)/temp(2) * xx - temp(3)/temp(2);
    figure(4)
    hold on
    plot(xx,yy,color(mod(i,7)+1),'LineWidth',2)
    temp2 = [x2(i) y2(i) 1]*E;
    temp2 = temp2./temp2(3);
    yy = -temp2(1)/temp2(2)* xx - temp2(3)/temp2(2);
    figure(5)
    hold on
    plot(xx,yy,color(mod(i,7)+1),'LineWidth',2)
end

% MATLAB Internal
epiLines = epipolarLine(E,correspondence(1:2,:)');
points = lineToBorderPoints(epiLines,size(im0bw));
figure;
imshow(uint8(im0bw)); alpha(0.5); hold on
line(points(:,[1,3])',points(:,[2,4])');

epiLines = epipolarLine(E,correspondence(3:4,:)');
points = lineToBorderPoints(epiLines,size(im1bw));
figure;
imshow(uint8(im1bw)); alpha(0.5); hold on
line(points(:,[1,3])',points(:,[2,4])');

%% Calculate possible T and R
[T1, R1, T2, R2, ~, ~] = TR_aus_E(E);

%% Calculate correct euklidian transformation and 3D reconstruction
disp("Reconstructing...");
[T, R,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
    cam0, cam1, do_debug);

%% Image rectification

P0 = [cam0 .* R, cam0 * T];
P1 = [cam1 .* R, cam1 * T];

[H0,H1,Pn0,Pn1] = rectifyP(P0,P1);

% The F matrix induced by Pn0,Pn1 shoud be skew([1 0 0])
fprintf('Rectification algebraic error:\t\t %0.5g \n',  ...
    norm (abs(fund(Pn0,Pn1)/norm(fund(Pn0,Pn1))) - abs(skew([1 0 0]))));

[im0r,im1r, bb0, bb1] = imrectify(im0,im1,H0,H1,'crop');

%% Calculate Disparity Map
disp("Computing disparity map...");
do_debug = 0;
if do_debug
    D = disparity(im0r, im1r);
else
    D = dmap(im0r, im1r);
    %D = dynamic_programming(im0g, im1g);
    
    %[D, sim, o3] = istereo(im0g,im1g,[0 16], 3);
    %D = stereo_matching_zncc(im0g, im1g, 9, [0 16]);
end

D(isnan(D)) = 0;
D = D ./ max(D(:)) * 255;


if do_debug
    figure('Name','Disparity Map','NumberTitle','off');
    title 'Disparity Map';
    imshow(D);
    colormap(gca,jet);
end
end