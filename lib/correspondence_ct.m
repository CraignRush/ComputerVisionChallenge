function ct = correspondence_ct(img,feature,varargin)
    % Census Transformation
    
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_size', 5, @(x) isnumeric(x) && x>1 && mod(x,2)==1 && numel(x)==1)
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_size  = P.Results.window_size;
    
    %% Renove border elements
    indices_tooclose = feature(1,:) < floor(window_size/2) |...
            (size(img,2) - feature(1,:)) < floor(window_size/2) | ...
            feature(2,:) < floor(window_size/2) | ...
            (size(img,1) - feature(2,:)) < floor(window_size/2);
    feature(:,indices_tooclose) = [];

    %% Census Transformation of every feature
    
    ct = zeros(size(feature,2),window_size^2);
    for i = 1:size(ct,1)
        ct(i,:) = census_trans(feature(:,i),img,window_size,0);
    end

end

function y = census_trans(pt,img,window_size,do_mean)
    if nargin < 4
        do_mean = 1;
    end
    
    epsilon = 0.05*255;
    
    pt = [pt(2),pt(1)];
    
    window = img((pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)),...
        (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)));
    
    if do_mean
        window_compare = mean(window,'all');
    else
        window_compare = img(pt(1),pt(2));
    end
    
    window_signature = zeros(window_size);
    window_signature = window_signature + double(window>(window_compare-epsilon));
    window_signature = window_signature + double(window>(window_compare+epsilon));
    y = reshape(window_signature,[],1);
end