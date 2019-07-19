function Korrespondenzen = correspondence_matlabgrader(I1,I2,Mpt1,Mpt2,varargin)
    % In dieser Funktion sollen die extrahierten Merkmalspunkte aus einer
    % Stereo-Aufnahme mittels NCC verglichen werden um Korrespondenzpunktpaare
    % zu ermitteln.
    
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_length', 25, @(x) isnumeric(x) && x>1 && mod(x,2)==1 && numel(x)==1)
    P.addOptional('min_corr', 0.95, @(x) isnumeric(x) && x > 0 && x < 1);
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_length  = P.Results.window_length;
    min_corr       = P.Results.min_corr;

    % Speichere Bilder I1, I2 als double in Im1, Im2
    Im1 = double(I1);
    Im2 = double(I2);
    
    %% Merkmalsvorbereitung
    min_dist = ceil(window_length/2);
    size_I1 = size(I1);
    size_I2 = size(I2);
    
    % Manipulate Mpt1 - vectorized
    indices_tooclose = Mpt1(1,:) < min_dist |...
        (size(I1,2) - Mpt1(1,:)) < min_dist | ...
        Mpt1(2,:) < min_dist | ...
        (size(I1,1) - Mpt1(2,:)) < min_dist;
    Mpt1(:,indices_tooclose) = [];
    no_pts1 = size(Mpt1,2);
    
    % Manipulate Mpt2 - vectorized
    indices_tooclose = Mpt2(1,:) < min_dist | ...
        (size(I2,2) - Mpt2(1,:)) < min_dist | ...
        Mpt2(2,:) < min_dist | ...
        (size(I2,1) - Mpt2(2,:)) < min_dist;
    Mpt2(:,indices_tooclose) = [];
    no_pts2 = size(Mpt2,2);
    
    %% Normierung
    window_length_half = floor(window_length/2);
    
    Mat_feat_1 = zeros(window_length^2,size(Mpt1,2));
    for i = 1:size(Mpt1,2)
        % Extract window
        Im1_x = Mpt1(1,i) + (-window_length_half:window_length_half);
        Im1_y = Mpt1(2,i) + (-window_length_half:window_length_half);
        window = Im1( Im1_y, Im1_x );
        
        % Mean of matrix
        mu = ones(window_length,1) * ones(1,window_length) * window * ones(window_length,1) * ones(1,window_length) / window_length^2;
        
        % Calculate standard deviation of matrix
        sigma = sqrt(norm(window-mu,'fro')^2/(window_length^2-1));
        
        % Normalize window
        window_n = ( window -  mu) / sigma;
        
        % Reshape normalized matrix and add to stacked matrix
        Mat_feat_1(:,i) = reshape(window_n,[],1);
        
        %Mat_feat_1(:,i) = (window(:)-mean(window(:))) / std(window(:));
    end
    
    Mat_feat_2 = zeros(window_length^2,size(Mpt2,2));
    for i = 1:size(Mpt2,2)
        % Extract window
        Im2_x = Mpt2(1,i)+(-window_length_half:window_length_half);
        Im2_y = Mpt2(2,i)+(-window_length_half:window_length_half);
        window = Im2( Im2_y, Im2_x );
        
        % Mean of matrix
        mu = ones(window_length,1)*ones(1,window_length)*window*ones(window_length,1)*ones(1,window_length)/window_length^2;
        
        % Calculate standard deviation of matrix
        sigma = sqrt(norm(window-mu,'fro')^2/(window_length^2-1));
        
        % Normalize window
        window_n = ( window -  mu) / sigma;
        
        % Reshape normalized matrix and add to stacked matrix
        Mat_feat_2(:,i) = reshape(window_n,[],1);
        
        % Mat_feat_2(:,i) = (window(:)-mean(window(:))) / std(window(:));
    end
    
    %% Normalized Cross Correlation
    
    % create emoty ncc matrix
    NCC_matrix = zeros(size(Mat_feat_1,2),size(Mat_feat_2,2));
    
    % length of vector = number of window matrix entries
    N = size(Mat_feat_1,1);
    
    % create empty matrix unsorted_index for later sorting with [value, index]
    unsorted_index = zeros(size(Mat_feat_1,2)*size(Mat_feat_2,2),2);

    % go through all correlation combinations and fill the ncc matrix
    for i_y = 1:size(Mat_feat_1,2)
        for i_x = 1:size(Mat_feat_2,2)
            % calculate ncc
            entry = 1/(N-1) * Mat_feat_2(:,i_x)' * Mat_feat_1(:,i_y);

            % asign NCC matrix entry with entry if entry >= min_corr
            %NCC_matrix(i_y, i_x) = (entry>=min_corr)*entry;
            NCC_matrix(i_y, i_x) = entry;
            
            % assign to unsorted_index
            unsorted_index(i_x+(i_y-1)*size(Mat_feat_2,2),:) = [NCC_matrix(i_y, i_x), (i_y-1)*size(Mat_feat_2,2)+i_x];
        end
    end
       
    sorted_index = sortrows(unsorted_index, 1,'descend');    
    sorted_index = sorted_index(sorted_index(:,1)>0,2);
    
    %% Korrespondenz
    
    % create empty matrix
    Korrespondenzen = zeros(4,min(size(Mpt1,2),size(Mpt2,2)));
    
    % number of sorted indices, size of ncc
    n_si = numel(sorted_index);
    size_ncc = size(NCC_matrix);
    
    i_korr = 1; % current index in korrrespondenzen
    for i = 1:n_si    
        % next element
        idx = sorted_index(i);
        
        % is column already taken?
        if NCC_matrix(idx)==0
            continue;
        end
        
        % get indices
        [idx_2,idx_1] = ind2sub(size_ncc,idx);
        
        % set ncc column to zero
        NCC_matrix(:,idx_1) = 0;
        
        % add to matrix
        Korrespondenzen(:,i_korr) = [Mpt1(:,idx_2);Mpt2(:,idx_1)];
        
        i_korr = i_korr+1;
    end

    Korrespondenzen = Korrespondenzen(:,1:i_korr-1);
    
end