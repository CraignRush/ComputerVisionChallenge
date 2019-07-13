function correspondence_ = punkt_korrespondenzen2(im0g,im1g,im0c,im1c,feature0,feature1,varargin)
    % In dieser Funktion sollen die extrahierten Merkmalspunkte aus einer
    % Stereo-Aufnahme mittels NCC verglichen werden um Korrespondenzpunktpaare
    % zu ermitteln.
    
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_length', 25, @(x) isnumeric(x) && x>1 && mod(x,2)==1 && numel(x)==1)
    P.addOptional('min_corr', 0.95, @(x) isnumeric(x) && x > 0 && x < 1);
    P.addOptional('do_plot', false, @islogical);
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_length  = P.Results.window_length;
    min_corr       = P.Results.min_corr;
    do_plot        = P.Results.do_plot;
    
    %%
    window_size = 11;
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
        
W=ufdwt(1,window_size,1);
W=W(ceil(window_size/2),:);
nDirs  = 2; % Directions: x y
gweight = 6;
posweight = 1; %todo...
nChans = 3+gweight; % Channels: red green blue gray gray gray
gradients0 = zeros(length(feature0), nDirs*nChans+2*posweight);
gradients1 = zeros(length(feature1), nDirs*nChans+2*posweight);

for i_pt = 1:length(feature0)
   pt = feature0(:,i_pt);
   pt = [pt(2),pt(1)];
   gradients0(i_pt,1) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
   gradients0(i_pt,2) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
   gradients0(i_pt,3) = W * im0c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
   gradients0(i_pt,4:3+gweight) = W * double(im0g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   gradients0(i_pt,4+gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients0(i_pt,5:gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients0(i_pt,6:gweight) = W * im0c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   gradients0(i_pt,(7+gweight):(7+2*gweight)) = W * double(im0g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))'; 
   gradients0(i_pt, (7+2*gweight):end) = pt;
end
for i_pt = 1:length(feature1)
   pt = feature1(:,i_pt);
   pt = [pt(2),pt(1)];   
   gradients1(i_pt,1) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),1); 
   gradients1(i_pt,2) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),2); 
   gradients1(i_pt,3) = W * im1c( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2),3); 
   gradients1(i_pt,4:3+gweight) = W * double(im1g( (pt(1)-floor(window_size/2)):(pt(1)+floor(window_size/2)) ,pt(2))); 
   gradients1(i_pt,4+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),1)'; 
   gradients1(i_pt,5+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),2)'; 
   gradients1(i_pt,6+gweight) = W * im1c( pt(1), (pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2)),3)'; 
   gradients1(i_pt,(7+gweight):(7+2*gweight)) = W * double(im1g(pt(1),(pt(2)-floor(window_size/2)):(pt(2)+floor(window_size/2))))';
   gradients1(i_pt,(7+2*gweight):end) = pt;
end

%%
corresp = inf(length(feature0),length(feature1));

for i1 = 1:length(feature0)
    for i2 = 1:length(feature1)
        corresp(i1,i2) = norm(gradients0(i1,:)/norm(gradients0(i1,:)) - ...
            gradients1(i2,:)/norm(gradients1(i2,:)),1);
    end
end
%%
[vals, ~] = min(corresp,[],1);

%indxs(vals>10) = []; % Select threshold
%vals(vals>10) = [];
[svals,sindxs] = sort(vals);
%%
max_corresp = 100;
correspons = zeros(min([max_corresp,length(svals)]),2);
for i = 1:size(correspons,1)
    correspons(i,1) = sindxs(i);
    [~, j] = min(corresp(:,sindxs(i)));
    correspons(i,2) = j;
end

%%
correspondence_ = zeros(4,size(correspons,1));
for i = 1:size(correspons,1)
    correspondence_(:,i) = [feature0(:,correspons(i,2)); feature1(:,correspons(i,1))];
end

end