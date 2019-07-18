function [newImg] = interpolateImage(img,scale)
% Resize a grey-image
%% get old image size
dim = size(img); 

%% compute new size vector
newDim = dim * scale;

%% Init pixel coordinates
[X, Y] = meshgrid( 1:dim(2), 1:dim(1) );

%% Init pixel transformation coordinates
vecDim{1} = linspace( 1, dim(2), newDim(2) );
vecDim{2} = linspace( 1, dim(1), newDim(1) );

%% Compute new coordinates
[newX, newY] = meshgrid(vecDim{1}, vecDim{2}); 

%% Interpolate from complete image
newImg = interp2(X, Y, img, newX, newY, 'nearest'); 
end