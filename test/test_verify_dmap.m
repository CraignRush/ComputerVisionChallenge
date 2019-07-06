
%% Motorcycle
G = readpfm('test/motorcycle/disp0.pfm');
[D,~,~] = disparity_map('test/motorcycle');

p = verify_dmap(D,G);