function gradients = correspondence_daniel(img,imgc,feature,varargin)
    % Matlab inspired correspondence algorithm
    img = double(img);
    imgc = double(imgc);
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_size',  9, @isnumeric)
    P.addOptional('gray_weight',  6, @isnumeric)
    P.addOptional('pos_weight',   1, @isnumeric)
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_size  = P.Results.window_size;
    gweight = P.Results.gray_weight;
    posweight = P.Results.pos_weight;
    %% Renove border elements
    indices_tooclose = feature(1,:) < ceil(window_size/2) |...
            (size(img,2) - feature(1,:)) < floor(window_size/2) | ...
            feature(2,:) < ceil(window_size/2) | ...
            (size(img,1) - feature(2,:)) < floor(window_size/2);
    feature(:,indices_tooclose) = [];

    %%
    W=ufdwt(1,window_size,1);
    W=W(ceil(window_size/2),:);
    nDirs  = 2; % Directions: x y
    nChans = 3+gweight; % Channels: red green blue gray gray gray ...
    gradients = zeros(length(feature), nDirs*nChans+2*posweight);

    %%
    for i_pt = 1:length(feature)
       pt = feature(:,i_pt);
       pt = [pt(2),pt(1)];
       gradients(i_pt,1) = W * imgc( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
       gradients(i_pt,2) = W * imgc( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
       gradients(i_pt,3) = W * imgc( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
       if gweight > 0
       gradients(i_pt,4:(3+gweight)) = W * double(img( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
       end
       gradients(i_pt,4+gweight) = W * imgc( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
       gradients(i_pt,5+gweight) = W * imgc( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
       gradients(i_pt,6+gweight) = W * imgc( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
       if gweight > 0
       gradients(i_pt,(7+gweight):(6+2*gweight)) = W * double(img(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))'; 
       end
       if posweight > 0
       gradients(i_pt, (7+2*gweight):end) = repmat(reshape(pt ./ size(img),1,[]),1,posweight)*10;
       end
    end

end
