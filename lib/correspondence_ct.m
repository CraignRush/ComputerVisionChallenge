function correspondence_ = correspondence_ct(im0g,im1g,feature0,feature1,varargin)
    % Census Transformation
    
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_size', 5, @(x) isnumeric(x) && x>1 && mod(x,2)==1 && numel(x)==1)
    P.addOptional('do_plot', false, @islogical);
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_size  = P.Results.window_size;
    do_plot        = P.Results.do_plot;
    
    %% Renove border elements
    indices_tooclose = feature0(1,:) < floor(window_size/2) |...
            (size(im0g,2) - feature0(1,:)) < floor(window_size/2) | ...
            feature0(2,:) < floor(window_size/2) | ...
            (size(im0g,1) - feature0(2,:)) < floor(window_size/2);
    feature0(:,indices_tooclose) = [];

    indices_tooclose = feature1(1,:) < floor(window_size/2) |...
            (size(im1g,2) - feature1(1,:)) < floor(window_size/2) | ...
            feature1(2,:) < floor(window_size/2) | ...
            (size(im1g,1) - feature1(2,:)) < floor(window_size/2);
    feature1(:,indices_tooclose) = [];

    %% Census Transformation of every feature
    
    ct0 = zeros(size(feature0,2),window_size^2);
    ct1 = zeros(size(feature1,2),window_size^2);
    for i = 1:size(ct0,1)
        ct0(i,:) = census_trans(feature0(:,i),im0g,window_size,0);
    end
    for i = 1:size(ct1,1)
        ct1(i,:) = census_trans(feature1(:,i),im1g,window_size,0);
    end
    
    
    %% Hamming distance
    dist = Inf(size(ct0,1),size(ct1,1));
    for i = 1:size(ct0,1)
        for j = 1:size(ct1,1)
            dist(i,j) = sum(ct0(i,:) == ct1(j,:));
        end
    end
    
    %%
    [~,sindxs] = sort(reshape(dist,[],1));

    %%
    max_corresp = 100;
    correspondence_ = zeros(4,min([max_corresp,length(sindxs)]));
    for i = 1:size(correspondence_,2)
        [i2,j2] = ind2sub(size(dist),sindxs(i));
        correspondence_(1:2,i) = feature0(:,i2);
        correspondence_(3:4,i) = feature1(:,j2);
    end

    
    %% Plot

    if do_plot
    figure('Name','Correspondence (Own)', 'NumberTitle','off');
    title 'Own Correspondence Estimation';
    imshow(uint8([im0g,im1g])); hold on;
    plot([correspondence_(1,:),correspondence_(3,:)+size(im0g,2)], ...
        [correspondence_(2,:),correspondence_(4,:)],'go');
    for i=1:size(correspondence_,2)
        pt1 = [correspondence_(1,i), correspondence_(3,i)+size(im0g,2)];
        pt2 = [correspondence_(2,i), correspondence_(4,i)];
        line(pt1,pt2);
    end
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