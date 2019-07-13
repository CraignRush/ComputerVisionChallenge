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

%% Convert Images to Black and White

% Frequency filter percentage
fil_perc = 0.1;

im0_fft = fftshift(fft2(im0g));
im1_fft = fftshift(fft2(im1g));

im0_fft_fil = im0_fft;
im1_fft_fil = im1_fft;

im0_fft_fil(floor(end/2-end/2*fil_perc):ceil(end/2+end/2*fil_perc),...
    floor(end/2-end/2*fil_perc):ceil(end/2+end/2*fil_perc)) = 0;
im1_fft_fil(floor(end/2-end/2*fil_perc):ceil(end/2+end/2*fil_perc),...
    floor(end/2-end/2*fil_perc):ceil(end/2+end/2*fil_perc)) = 0;
%     figure;
%     imshow([im0_fft_fil im1_fft_fil]);

im0_fil = ifft2(ifftshift(im0_fft_fil));
im1_fil = ifft2(ifftshift(im1_fft_fil));

im0_fil = abs(im0_fil);
im1_fil = abs(im1_fil);

im0_fil = (im0_fil) ./ max(im0_fil(:)) * 255;
im1_fil = (im1_fil) ./ max(im1_fil(:)) * 255;

im0_bw = im0_fil;
im1_bw = im1_fil;

% im0_bw = im0g;
% im1_bw = im1g;

figure;
imshow([im0_bw im1_bw],[0 255]);

%% Feature extraction
disp("Extracting features...");
% % Optionally add: 'segment_length',9,'k',0.05,'min_dist',50,'N',20
% feature0 = harris_detektor( im0g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 );
% feature1 = harris_detektor( im1g, 'segment_length',9,'k',0.05,'min_dist',30,'N',20 );
%
% if do_debug
%     figure('Name','Harris Detection','NumberTitle','off');
%     title 'Harris detection';
%     subplot(121); imshow(uint8(im0g)); hold on;
%     plot(feature0(1,:),feature0(2,:),'go');
%     subplot(122); imshow(uint8(im1g)); hold on;
%     plot(feature1(1,:),feature1(2,:),'go');
% end

feature0 = harris_detektor( im0_bw, 'segment_length',15,'k',0.04,'min_dist',10,'N',40 );
feature1 = harris_detektor( im1_bw, 'segment_length',15,'k',0.04,'min_dist',10,'N',40 );

if do_debug
    figure('Name','Harris Detection','NumberTitle','off');
    title 'Harris detection';
    subplot(121); imshow(uint8(im0_bw)); hold on;
    plot(feature0(1,:),feature0(2,:),'go');
    subplot(122); imshow(uint8(im1_bw)); hold on;
    plot(feature1(1,:),feature1(2,:),'go');
end

fprintf("Number of found features: %d, %d\n",size(feature0,2),size(feature1,2));
%% TEST


do_debug = true;



%% Correspondence estimation
disp("Estimate correspondences...");
% % Optionally adD: 'window_length',25,'min_corr', 0.90
% correspondence = punkt_korrespondenzen(im0,im1g,feature0,feature1, ...
%     'min_corr', 0.7, 'do_plot', do_debug);

correspondence = punkt_korrespondenzen(im0_bw,im1_bw,feature0,feature1, ...
    'window_length',25,'min_corr', 0.7, 'do_plot', do_debug);

fprintf("Number of found correspondences: %d\n", size(correspondence,2));

%%  Find robust correspondence point pairs with RANSAC-algorithm
disp("Selecting for robust correspondences...");
% correspondence = F_ransac(correspondence, 'tolerance', 0.04);
% if do_debug
%     figure('Name','Robust Correspondence Estimation','NumberTitle','off');
%     title 'Robust Correspondence Estimation';
%     imshow(uint8(im0g)); hold on
%     plot(correspondence(1,:),correspondence(2,:),'go');
%     imshow(uint8(im1g)); alpha(0.5);
%     plot(correspondence(3,:),correspondence(4,:),'ro')
%     for i=1:size(correspondence,2)
%         pt1 = [correspondence(1,i), correspondence(3,i)];
%         pt2 = [correspondence(2,i), correspondence(4,i)];
%         line(pt1,pt2);
%     end
% end

% correspondence = F_ransac(correspondence,'p',0.99,'tolerance',0.01,...
%     'epsilon',0.1);
%
% fprintf("Number of robust correspondences: %d\n", size(correspondence,2));
%
% if do_debug
%     figure('Name','Robust Correspondence Estimation','NumberTitle','off');
%     title 'Robust Correspondence Estimation';
%     imshow(uint8(im0_bw)); alpha(0.5); hold on
%     plot(correspondence(1,:),correspondence(2,:),'go');
%     imshow(uint8(im1_bw));alpha(0.5);
%     plot(correspondence(3,:),correspondence(4,:),'ro')
%     for i=1:size(correspondence,2)
%         pt1 = [correspondence(1,i), correspondence(3,i)];
%         pt2 = [correspondence(2,i), correspondence(4,i)];
%         line(pt1,pt2);
%     end
% end

%% Get "robust" correspondences via an angle estimation
comp_num = ceil(length(correspondence));
angle = NaN(comp_num);
parallels = [];
indices = randi([1 comp_num],comp_num,1);
for i = 1:comp_num
    ind = indices(i);
    ref(1) = abs(correspondence(1,ind)-correspondence(3,ind));
    ref(2) = abs(correspondence(2,ind)-correspondence(4,ind));
    acc = 0;
    parallels = [];
    
    for j = 1:comp_num
        vec(1) = abs(correspondence(1,j)-correspondence(3,j));
        vec(2) = abs(correspondence(2,j)-correspondence(4,j));
        
        % get angle between both vetors via dot product identity
        angle(i,j) = acos(dot(ref,vec)/(norm(ref,2)*norm(vec,2)));
        
        if angle(i,j) <= 1 && norm(vec,2) <= norm(ref,2)*1.1 && ...
                norm(vec,2) > norm(ref,2)*0.9
            acc = acc + 1;
            parallels = [parallels, correspondence(:,j)];
            if acc > 20
                break
            end
        end
    end
    if acc > 7
        break
    end
end

if do_debug
    figure('Name','Own Correspondence Estimation','NumberTitle','off');
    title 'Own Correspondence Estimation';
    imshow(uint8(im0_bw)); alpha(0.5); hold on
    plot(parallels(1,:),parallels(2,:),'go');
    imshow(uint8(im1_bw));alpha(0.5);
    plot(parallels(3,:),parallels(4,:),'ro')
    for i=1:size(parallels,2)
        pt1 = [parallels(1,i), parallels(3,i)];
        pt2 = [parallels(2,i), parallels(4,i)];
        line(pt1,pt2);
    end
end

correspondence = parallels;
%% Calculate essential matrix E
disp("Calculating E...");
E = achtpunktalgorithmus(correspondence,cam0, cam1);

%% Epipolar Lines
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
figure
imagesc(im0_bw);
colormap(gray);
figure(5)
imagesc(im1_bw)
colormap(gray)
xx = 0:size(im1_bw,2);



for i =1:size(correspondence)-1
    temp = E*[x(i) y(i) 1]';
    temp = temp./temp(3);
    yy = - temp(1)/temp(2) * xx - temp(3)/temp(2);
    figure(5)
    hold on
    plot(xx,yy,color(mod(i,7)+1),'LineWidth',2)
    temp2 = [x2(i) y2(i) 1]*E;
    temp2 = temp2./temp2(3);
    yy = -temp2(1)/temp2(2)* xx - temp2(3)/temp2(2);
    figure(2)
    hold on
    plot(xx,yy,color(mod(i,7)+1),'LineWidth',2)
end


epiLines = epipolarLine(E,correspondence(1:2,:)');
points = lineToBorderPoints(epiLines,size(im0_bw));
figure;
imshow(uint8(im0_bw)); alpha(0.5); hold on
line(points(:,[1,3])',points(:,[2,4])');

epiLines = epipolarLine(E,correspondence(3:4,:)');
points = lineToBorderPoints(epiLines,size(im1_bw));
figure;
imshow(uint8(im1_bw)); alpha(0.5); hold on
line(points(:,[1,3])',points(:,[2,4])');

%% Calculate possible T and R
[T1, R1, T2, R2, ~, ~] = TR_aus_E(E);

%% Calculate correct euklidian transformation and 3D reconstruction
disp("Reconstructing...");
[T, R,~,~] = rekonstruktion(T1, T2, R1, R2, correspondence, ...
    cam0, cam1, do_debug);

%% Image rectification

pm0 = [cam0 .* T, cam0 * T]
pm1 = [cam1 .* T, cam1 * T]
%% Calculate Disparity Map
disp("Computing disparity map...");
do_debug = 0;
im0 = imread(['im0_rect.jpg']);
im0g= rgb_to_gray(im0);
im1 = imread(['im1_rect.jpg']);
im1g= rgb_to_gray(im1);
if do_debug
   % D = disparity(im0g, im1g);
else
    D = dmap(im0g, im1g);
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