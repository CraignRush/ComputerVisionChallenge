function [peaksnr] = psnr(A, ref, peakval)
%% PSNR Peak Signal-To-Noise Ratio.

if nargin < 3 
    peakval = 255;
end

peakval = double(peakval);

if isempty(A) % If A is empty, ref must also be empty
    peaksnr = zeros(0, 'like', A);
    return;
end

%% err = immse(A,ref);
if isinteger(A) || isinteger(ref)     
    A = double(A);
    ref = double(ref);
end

err = (norm(A(:)-ref(:),2).^2)/numel(A);

%% psnr
peaksnr = 10*log10(peakval.^2/err);

end
