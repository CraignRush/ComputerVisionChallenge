function Korrespondenzen = punkt_korrespondenzen_jo(I1,I2,Mpt1,Mpt2,varargin)
    % In dieser Funktion sollen die extrahierten Merkmalspunkte aus einer
    % Stereo-Aufnahme mittels NCC verglichen werden um Korrespondenzpunktpaare
    % zu ermitteln.
    
    %% Input parser
    p = inputParser;
    
    validationFcn{1} = @(x) isnumeric(x) && rem(x,2) && (x>1);
    validationFcn{2} = @(x) isnumeric(x) && x>0 && x<1;
    
    p.addOptional('window_length',25,validationFcn{1});
    p.addOptional('min_corr',0.9,validationFcn{2});
    p.addOptional('do_plot', false, @islogical);
    
    p.parse(varargin{:});
    
    Im1 = double(I1);
    Im2 = double(I2);
    
    window_length = p.Results.window_length;
    min_corr = p.Results.min_corr;
    do_plot = p.Results.do_plot;
    
    %% Merkmalsvorbereitung
    edges = zeros(4,2);
    % Edges corrected by window size (1:l, 2:b, 3:r, 4:t)
    s=struct('left',1,'bottom',2,'right',3,'top',4);
    
    % Setup edge data for Im1
    edges(s.left,1) = ceil(window_length/2);
    edges(s.right,1) = size(Im1,2) - floor(window_length/2);
    edges(s.top,1) = edges(s.left);
    edges(s.bottom,1) = size(Im1,1) - floor(window_length/2);    
    
    Mpt1(:,(Mpt1(1,:) < edges(s.left,1))| ...
           (Mpt1(1,:) > edges(s.right,1))|...
           (Mpt1(2,:) < edges(s.top,1)) | ...
           (Mpt1(2,:) > edges(s.bottom,1))) = [];
    no_pts1 = size(Mpt1,2);
    
        % Setup edge data for Im2
    edges(s.left,2) = ceil(window_length/2);
    edges(s.right,2) = size(Im2,2) - floor(window_length/2);
    edges(s.top,2) = edges(s.left);
    edges(s.bottom,2) = size(Im2,1) - floor(window_length/2);    
    
    Mpt2(:,(Mpt2(1,:) < edges(s.left,2))| ...
           (Mpt2(1,:) > edges(s.right,2))|...
           (Mpt2(2,:) < edges(s.top,2)) | ...
           (Mpt2(2,:) > edges(s.bottom,2))) = [];
    no_pts2 = size(Mpt2,2);
    
    
 %% Normierung
 Mat_feat_1 = zeros(window_length^2,no_pts1);
 Mat_feat_2 = zeros(window_length^2,no_pts2);
 
 for i = 1:no_pts1
    window = Im1((Mpt1(2,i)-floor(window_length/2)):(floor(window_length/2)+Mpt1(2,i)),...
        (Mpt1(1,i)-floor(window_length/2)):(floor(window_length/2)+Mpt1(1,i)));
    Mat_feat_1(:,i) = (window(:)-mean(window(:)))./std(window(:));
 end
 
  for i = 1:no_pts2
    window = Im2((Mpt2(2,i)-floor(window_length/2)):(floor(window_length/2)+Mpt2(2,i)),...
        (Mpt2(1,i)-floor(window_length/2)):(floor(window_length/2)+Mpt2(1,i)));
    Mat_feat_2(:,i) = (window(:)-mean(window(:)))./std(window(:));
 end
 
 %Korrespondenzen = {Mat_feat_1, Mat_feat_2};
 
 %% NCC Berechung 
    NCC_matrix = 1/(window_length*window_length-1) * Mat_feat_2' * Mat_feat_1;
    NCC_matrix(NCC_matrix < min_corr) = 0;
    
    [sorted_list,sorted_index] = sort(NCC_matrix(:),'descend');
    sorted_index(sorted_list == 0) = [];
    
    %Korrespondenzen = {NCC_matrix, sorted_index};
    
  %% Korrespondenz  
   [x,y] = ind2sub(size(NCC_matrix),sorted_index);
  
   [y_unique,y_ind] = unique(y,'stable');  
  
   Korrespondenzen = [Mpt1(:,y_unique); Mpt2(:,x(y_ind))]; 
  
   
    %% Zeige die Korrespondenzpunktpaare an
    if do_plot
       figure('name', 'Punkt-Korrespondenzen');  
       imshow(uint8(I1));
       hold on
       plot(Korrespondenzen(1,:),Korrespondenzen(2,:),'bs');
       plot(Korrespondenzen(1,:),Korrespondenzen(2,:),'bs');
       imshow(uint8(I2));
       alpha(0.5);       
       plot(Korrespondenzen(3,:),Korrespondenzen(4,:),'gs');
       hold on
       for i = 1:size(Korrespondenzen(1,:),2)
       line([Korrespondenzen(1,i), Korrespondenzen(3,i)],...
            [Korrespondenzen(2,i), Korrespondenzen(4,i)],...
            'Color','red','LineWidth',2);
        hold on
       end
    end
end