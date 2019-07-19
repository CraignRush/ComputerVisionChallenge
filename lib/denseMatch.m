% *************************************************************************
% denseMatch.mn
% *************************************************************************
function dispMap = denseMatch(rightImage, leftImage, corrWindowSize,...
    dMin, dMax)


[nrLeft,ncLeft] = size(leftImage);

% Convert the left and right images from uint8 to double
leftImage=im2double(leftImage);
rightImage=im2double(rightImage);

% Create an image of size nrLeft and ncLeft, fill it with zeros and
% assign it to variable dispMap
dispMap=zeros(nrLeft, ncLeft);

% Find out how many rows and columns are to the left/right/up/down
% of the central pixel based on the window size
win=(corrWindowSize-1)/2;

for(i=1+win:1:nrLeft-win)
    % For every row in Left Image
    for(j=1+win:1:ncLeft-win-dMax)
        % For every column in Left Image

        prevcorrScore = 0.0;
        
        % Initialize the temporary variable to store the best
        % matched
        % disparity score
        bestMatchSoFar = dMin;
        for(d=dMin:dMax)
            % For every disparity value in x-direction
            % Construct a region with window around
            % central/selected pixel in left image
            regionLeft=leftImage(i-win : i+win, j-win : j+win);
            % Construct a region with window around
            % central/selected pixel in right image
            regionRight=rightImage(i-win : i+win, j+d-win : j+d+ win);
            % Calculate the local mean in left region
            meanLeft = mean(regionLeft,'all');
            % Calculate the local mean in right region
            meanRight = mean(regionRight,'all');

            % Calculate the correlation score
            % Calculate the term in the denominator (var: den)
            den = sqrt(sum(sum((regionLeft - meanLeft).^2))* ...
                sum(sum((regionRight - meanRight).^2)));
            tempCorrScore = (regionLeft - meanLeft).*(regionRight ...
                - meanRight)/den;
            
            % Compute the final score by summing the values in
            % tempCorrScore,
            % and store it in a temporary variable signifying the
            % distance
            % (var: corrScore)
            corrScore=sum(sum(tempCorrScore));
            if(corrScore>prevcorrScore)
                % If the current disparity value is greater
                % than
                % previous one, then swap them
                prevcorrScore=corrScore;
                bestMatchSoFar=d;
            end

        end
        % Store the final matched value in variable dispMap
        dispMap(i,j) = bestMatchSoFar;
    end
end

end