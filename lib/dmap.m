function [DbasicSubpixel] = dmap(leftI,rightI)
%DMAP Summary of this function goes here
%   Detailed explanation goes here


DbasicSubpixel = zeros(size(leftI), 'single');

% The disparity range defines how many pixels away from the block's location
% in the first image to search for a matching block in the other image.
disparityRange = 50;

% Define the size of the blocks for block matching.
halfBlockSize = 3;
blockSize = 2 * halfBlockSize + 1;

% Get the image dimensions.
[imgHeight, imgWidth] = size(leftI);

% For each row 'm' of pixels in the image...
for (m = 1 : imgHeight)
    	
	% Set min/max row bounds for the template and blocks.
	% e.g., for the first row, minr = 1 and maxr = 4
    minr = max(1, m - halfBlockSize);
    maxr = min(imgHeight, m + halfBlockSize);
	
    % For each column 'n' of pixels in the image...
    for (n = 1 : imgWidth)
        
		% Set the min/max column bounds for the template.
		% e.g., for the first column, minc = 1 and maxc = 4
		minc = max(1, n - halfBlockSize);
        maxc = min(imgWidth, n + halfBlockSize);
        
		% Define the search boundaries as offsets from the template location.
		mind = 0; 
        maxd = min(disparityRange, imgWidth - maxc);

		% Select the block from the right image to use as the template.
        template = rightI(minr:maxr, minc:maxc);
		
		% Get the number of blocks in this search.
		numBlocks = maxd - mind + 1;
		
		% Create a vector to hold the block differences.
		blockDiffs = zeros(numBlocks, 1);
		
		% Calculate the difference between the template and each of the blocks.
		for (i = mind : maxd)
		
			% Select the block from the left image at the distance 'i'.
			block = leftI(minr:maxr, (minc + i):(maxc + i));
		
			% Compute the 1-based index of this block into the 'blockDiffs' vector.
			blockIndex = i - mind + 1;
		
			% Take the sum of absolute differences (SAD) between the template
			% and the block and store the resulting value.
			blockDiffs(blockIndex, 1) = sum(sum(abs(template - block)));
		end
		
		% Sort the SAD values to find the closest match (smallest difference).
		% Discard the sorted vector (the "~" notation), we just want the list
		% of indices.
		[temp, sortedIndeces] = sort(blockDiffs);
		
		% Get the 1-based index of the closest-matching block.
		bestMatchIndex = sortedIndeces(1, 1);
		
		% Convert the 1-based index of this block back into an offset.
		% This is the final disparity value produced by basic block matching.
		d = bestMatchIndex + mind - 1;
			
		% Calculate a sub-pixel estimate of the disparity by interpolating.
		% Sub-pixel estimation requires a block to the left and right, so we 
		% skip it if the best matching block is at either edge of the search
		% window.
		if ((bestMatchIndex == 1) || (bestMatchIndex == numBlocks))
			% Skip sub-pixel estimation and store the initial disparity value.
			DbasicSubpixel(m, n) = d;
		else
			% Grab the SAD values at the closest matching block (C2) and it's 
			% immediate neighbors (C1 and C3).
			C1 = blockDiffs(bestMatchIndex - 1);
			C2 = blockDiffs(bestMatchIndex);
			C3 = blockDiffs(bestMatchIndex + 1);
			
			% Adjust the disparity by some fraction.
			% We're estimating the subpixel location of the true best match.
			DbasicSubpixel(m, n) = d - (0.5 * (C3 - C1) / (C1 - (2*C2) + C3));
		end
    end

	% Update progress every 10th row.
	if (mod(m, 10) == 0)
		fprintf('  Image row %d / %d (%.0f%%)\n', m, imgHeight, (m / imgHeight) * 100);
	end
		
end

end

