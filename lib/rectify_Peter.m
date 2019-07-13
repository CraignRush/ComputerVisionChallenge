% RECTIFY rectify image pair to find homography
% Usage:
%     [H1, H2] = rectify(im1, im2, finalmatches, F)

function [H12,H21,F12, Img1_new,Img2_new]  = rectify_Peter(Img1, Img2, X, F12)

% Transfer between image 1 and 2, i.e. x1' * F12 * x2 = 0

%% Matching 2D points hard coded
[x1,x2] = correspondences_F12(X);

%% Get image size
[rows,cols,depth] = size(Img1);

%% Get homographies
[H12,H21,bSwap] = rectify_homographies( F12, x1, x2, rows, cols );

%% Transform the images
fprintf( 1, 'Rectifying...\n' );
Img1_new = rectify_transform( Img1, H12 );
Img2_new = rectify_transform( Img2, H21 );

%% Chop off excess rows
[Img1_new,Img2_new] = chop_rows( Img1_new, Img2_new, H12, H21, rows, cols );

fprintf( 1, 'Writing images to disk...\n' );

Img1_new = mat2gray(Img1_new);
Img2_new = mat2gray(Img2_new);

if 0
    imwrite( Img1_new, 'im1_rect.png' );
    imwrite( Img2_new, 'im2_rect.png' );
end
end

function [Img1,Img2] = chop_rows( Img1, Img2, H12, H21, rows, cols )
box1 = transform_bbox( H12, rows, cols );
box2 = transform_bbox( H21, rows, cols );
min1 = min( box1(2,:) );
min2 = min( box2(2,:) );
if min1 < min2
    Img1 = Img1(min2-min1+1:end,:,:);
else
    Img2 = Img2(min1-min2+1:end,:,:);
end
max1 = max( box1(2,:) );
max2 = max( box2(2,:) );
if max1 > max2
    Img1 = Img1(1:size(Img1,1)-(max1-max2),:,:);
else
    Img2 = Img2(1:size(Img2,1)-(max2-max1),:,:);
end
end
%-----------------------------------------------------------------------------

function box = transform_bbox( H, rows, cols )

box = [ 1 cols 1 cols ; 1 1 rows rows ; 1 1 1 1 ];
box = H * box;
box = round( box(1:2,:) ./ repmat( box(3,:), 2, 1 ));
end
%-----------------------------------------------------------------------------

function Img_new = rectify_transform( Img, H )

% Peter's image transform wants a specific max width/height for the
% image, but we want the natural width/height, so we have to calculate it.

rows = size( Img, 1 );
cols = size( Img, 2 );
xnew = transform_bbox( H, rows, cols );

sze = max( xnew' )' - min( xnew' )' + [ 1 ; 1 ];

Img_new = imTrans( Img, H, [], max( sze ));
end
%----------------------------------------------------------------------------

function [H1,H2,bSwap] = rectify_homographies( F, x1, x2, rows, cols )

% F: a fundamental matrix
% x1 and x2: corresponding points such that x1_i' * F * x2_i = 0
% Initialize

H1 = [];
H2 = [];
bSwap = 0;

% Center of image
cy = round( rows/2 );
cx = round( cols/2 );

% Fix F to be rank 2 to numerical accuracy
[U,D,V] = svd( F );
D(3,3) = 0;
F = U*D*V';

% Get epipole.  e12 is the epipole in image 1 for camera 2.
e12 = null( F' );             % Epipole in image 1 for camera 2
e21 = null( F );              % Epipole in image 2 for camera 1

% Put epipoles in front of camera
if e12 < 0, e12 = -e12; end
if e21 < 0, e21 = -e21; end

% Make sure the epipoles are inside the images
check_epipoles_in_image( e12, e21, rows, cols );

% Check that image 1 is to the left of image 2
if e12(1)/e12(3) < cx
    fprintf( 1, 'Swapping left and right images...\n' );
    tmp = e12;
    e12 = e21;
    e21 = tmp;
    F = F';
    bSwap = 1;
end

% Now we have
% F' * e12 = 0,
% F  * e21 = 0,
% Let's get the rectifying homography Hprime for image 1 first

Hprime = map_to_infinity( e12, cx, cy );
e12_new = Hprime * e12;
% Normalize Hprime so that Hprime*eprime = (1,0,0)'
Hprime = Hprime / e12_new(1);
e12_new = Hprime * e12;
fprintf( 1, 'Epipole 1/2 mapped to infinity: (%g, %g, %g)\n', e12_new );

% Get canonical camera matrices for F12 and compute H0, one possible
% rectification homography for image 2
[P,Pprime] = get_canonical_cameras( F );
M = Pprime(:,1:3);
H0 = Hprime * M;

% Test that F12 is a valid F for P,Pprime
test_p_f( P, Pprime, F );

% Now we need to find H so that the epipolar lines match
% each other, i.e., inv(H)' * l = inv(Hprime)' * lprime
% and the disparity is minimized, i.e.,
% min \sum_i d(H x_i, Hprime xprime_i)^2

% Transform data initially according to Hprime (img 1) and H0 (img 2)
x1hat = Hprime * x1;
x1hat = x1hat ./ repmat( x1hat(3,:), 3, 1 );
x2hat = H0 * x2;
x2hat = x2hat ./ repmat( x2hat(3,:), 3, 1 );
rmse_x = sqrt( mean( (x1hat(1,:) - x2hat(1,:) ).^2 ));
rmse_y = sqrt( mean( (x1hat(2,:) - x2hat(2,:) ).^2 ));
fprintf( 1, 'Before Ha, RMSE for corresponding points in Y: %g X: %g\n', ...
    rmse_y, rmse_x );

% Estimate [ a b c ; 0 1 0 ; 0 0 1 ] aligning H, Hprime
n = size(x1,2);
A = [ x2hat(1,:)', x2hat(2,:)', ones(n,1) ];
b = x1hat(1,:)';
abc = A\b;
HA = [ abc' ; 0 1 0 ; 0 0 1 ];
H = HA*H0;
x2hat = H * x2;
x2hat = x2hat ./ repmat( x2hat(3,:), 3, 1 );
rmse_x = sqrt( mean(( x1hat(1,:) - x2hat(1,:) ).^2 ));
rmse_y = sqrt( mean(( x1hat(2,:) - x2hat(2,:) ).^2 ));
fprintf( 1, 'After Ha, RMSE for corresponding points in Y: %g X: %g\n', ...
    rmse_y, rmse_x );

% Return the homographies as appropriate
if bSwap
    H1 = H;
    H2 = Hprime;
else
    H1 = Hprime;
    H2 = H;
end
end
%-----------------------------------------------------------------------------

function check_epipoles_in_image( e1, e2, rows, cols )

% Check whether given epipoles are in the image or not
if abs( e1(3) ) < 1e-6 && abs( e2(3) ) < 1e-6, return; end

e1 = e1 / e1(3);
e2 = e2 / e2(3);
if ( e1(1) <= cols && e1(1) >= 1 && e1(2) <= rows && e1(2) >= 1 ) || ...
        ( e2(1) <= cols && e2(1) >= 1 && e2(2) <= rows && e2(2) >= 1 )
    err_msg = sprintf( 'epipole (%g,%g) or (%g,%g) is inside image', ...
        e1(1:2), e2(1:2) );
    error( [ err_msg, ' -- homography does not work in this case!' ] );
end
end
%-----------------------------------------------------------------------------

function [P,Pprime] = get_canonical_cameras( F )

% Get the "canonical" cameras for given fundamental matrix
% according to Hartley and Zisserman (2004), p256, Result 9.14

% But ensure that the left 3x3 submatrix of Pprime is nonsingular
% using Result 9.15, that the general form is
% [ skewsym( e12 ) * F + e12 * v', k * e12 ] where v is an arbitrary
% 3-vector and k is an arbitrary scalar

P = [ 1 0 0 0
    0 1 0 0
    0 0 1 0 ];

e12 = null( F' );
M = skewsym( e12 ) * F + e12 * [1 1 1];
Pprime = [ M, e12 ];
end
%-----------------------------------------------------------------------------

function test_p_f( P, Pprime, F )

% Test that camera matrices Pprime and P are consistent with
% fundamental matrix F
% Meaning  (Pprime*X)' * F * (P*X) = 0,  for all X in 3space

% Get the epipole in camera 1 for camera 2
C2 = null( P );
eprime = Pprime * C2;

% Construct F from Pprime, P, and eprime
Fhat = skewsym( eprime ) * Pprime * pinv( P );

% Check that it's close to F
alpha = Fhat(:)\F(:);
if norm( alpha*Fhat-F ) > 1e-10
    fprintf( 1, 'Warning: supplied camera matrices are inconsistent with F\n' );
else
    fprintf( 1, 'Supplied camera matrices OK\n' );
end
end
%-----------------------------------------------------------------------------

function H = map_to_infinity( x, cx, cy )

% Given a point and the desired origin (point of minimum projective
% distortion), compute a homograph H = G*R*T taking the point to the
% origin, rotating it to align with the X axis, then mapping it to
% infinity.

% First map cx,cy to the origin
T = [ 1 0 -cx
    0 1 -cy
    0 0 1 ];
x = T * x;

% Now rotate the translated x to align with the X axis.
cur_angle = atan2( x(2), x(1) );
R = [ cos( -cur_angle ), -sin( -cur_angle ), 0
    sin( -cur_angle ),  cos( -cur_angle ), 0
    0,                  0, 1 ];
x = R * x;

% Now the transformation G mapping x to infinity
if abs( x(3)/norm(x) ) < 1e-6
    % It's already at infinity
    G = eye(3)
else
    f = x(1)/x(3);
    G = [    1   0  0
        0   1  0
        -1/f  0  1 ];
end;

H = G*R*T;
end
%-----------------------------------------------------------------------------

function s = skewsym( x )
s = [   0   -x(3)  x(2)
    x(3)   0   -x(1)
    -x(2)  x(1)   0   ];
end
%-----------------------------------------------------------------------------

function [x1,x2] = correspondences_F12(X)
x1 = X(:,3:4)';
x2 = X(:,1:2)';
n = size( x1, 2 );
x1 = [ x1 ; ones(1,n) ];
x2 = [ x2 ; ones(1,n) ];
n = size(x1,2);
end
