function [D,header] = readpfm(filename_pfm)

fid = fopen(filename_pfm);

header{1} = fscanf(fid,'%c',[1 2]);
header{2} = fscanf(fid,'%f',[1 2]);
header{3} = fscanf(fid,'%f',1);
fscanf(fid,'%c',1);

if header{3} > 0
    % scale factor > 0 --> big endian encoded file
    endianness = 'ieee-be';
else
    % scale factor < 0 --> little endian encoded file
    endianness = 'ieee-le';
end

if header{1} == 'Pf'
    % grayscale image
    D = fread(fid,[header{2}(1) header{2}(2)],'single',0,endianness);
elseif header{1} == 'PF'
    % color image
    tmp = fread(fid,[header{2}(1)*3 header{2}(2)],'single',0,endianness); 
    D = zeros([header{2} 3]);
    D(:,:,1) = tmp(1:3:end,:);
    D(:,:,2) = tmp(2:3:end,:);
    D(:,:,3) = tmp(3:3:end,:);
else
    error('Header could not be read!');
end

D(D == Inf) = 0;
D = rot90(D);
fclose(fid);



