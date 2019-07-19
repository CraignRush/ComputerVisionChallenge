function p = verify_dmap(D,G)
% This function calculates the PSNR of a given disparity map and the ground
% truth. The value range of both is normalized to [0,255].

addpath(genpath('lib'));

%% Check if D and G are in range [0 255]
assert(~any(any((G <= 255 & G >= 0) == 0)), 'G has to be in range [0 255]');
assert(~any(any((D <= 255 & D >= 0) == 0)), 'D has to be in range [0 255]');

%% Calculate psnr
p = psnr(D,G);

end

