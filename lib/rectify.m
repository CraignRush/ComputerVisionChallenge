function [T0, T1, Pn0, Pn1] = rectify(Po0,Po1)
%% Compute optical centers    
c0 = - inv( Po0(:, 1:3) ) * Po0(:, 4);
c1 = - inv( Po1(:, 1:3) ) * Po1(:, 4);

%% Compute focal length
au = norm( Po0(1, 1:3)' .* Po0(3, 1:3)' );
av = norm( Po0(1, 1:3)' .* Po0(3, 1:3)' );

%% Compute retinal planes
fl = Po0(3, 1:3)';
fr = Po1(3, 1:3)';

nn = fl .* fr;

%% Solve the four systems
A = [ [c0' 1]' [c1' 1]' [nn' 0]' ]';
[~, ~, V] = svd(A);
r = 1 / norm( V([1 2 3], 4) );
a2 = r * V(:, 4);

A = [ [c0' 1]' [c1' 1]' [a2(1:3)' 0]' ]';
[~, ~, V] = svd(A);
r = norm(av) / norm( V([1 2 3], 4) );
a1 = r * V(:, 4);

A = [ [c0' 1]' [a1(1:3)' 0]' [a2(1:3)' 0]' ]';
[~, ~, V] = svd(A);
r = norm(au) / norm( V([1 2 3], 4) );
a0 = r * V(:, 4);

A = [ [c1' 1]' [a1(1:3)' 0]' [a2(1:3)' 0]' ]';
[~, ~, V] = svd(A);
r = norm(au) / norm( V([1 2 3], 4) );
b0 = r * V(:, 4);

%% Adjust Homography Matrix H
H = eye(3);

%% Rectify projection matrices
Pn0 = H * [a0 a1 a2]';
Pn1 = H * [b0 a1 a2]';

%% Rectify image transformation matrix
T0 = Pn0(1:3, 1:3) * inv(Po0(1:3, 1:3));
T1 = Pn1(1:3, 1:3) * inv(Po1(1:3, 1:3));


end