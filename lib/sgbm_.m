% cd '/Users/daniel/Documents/Studium/Module/[TUM] Computer Vision/Challenge/computer-vision/lib'
%mex zncc.c
im0g = rgb_to_gray(imread('../test/teddy/im0.png'));
im1g = rgb_to_gray(imread('../test/teddy/im1.png'));
%  dbmex on;
D = zncc(im0g,im1g);

