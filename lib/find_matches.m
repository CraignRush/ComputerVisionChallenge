function correspondence = find_matches(sig0,sig1,f0,f1,method)
%FIND_MATCHES Finds matching points between sig0 and sig1
%   Available methods: 'Hamming', 'NearestNeightbor'/'NN'

    dist = Inf(size(sig0,1),size(sig1,1));
    
    if strcmp(method,'Hamming')
        % Hamming
        for i = 1:size(sig0,1)
            for j = 1:size(sig1,1)
                dist(i,j) = sum(sig0(i,:) == sig1(j,:));
            end
        end
    elseif strcmp(method,'NearestNeightbor') || strcmp(method,'NN')
        for i = 1:size(sig0,1)
            for j = 1:size(sig1,1)
                dist(i,j) = norm(...
                    sig0(i,:)/norm(sig0(i,:)) - ...
                    sig1(j,:)/norm(sig1(j,:)) , 2);
            end
        end
    elseif strcmp(method,'NCC')
        % Normalized Cross Correlation
        NCC_matrix = zeros(size(f0,2),size(f1,2));

        % length of vector = number of window matrix entries
        N = size(f0,1);

        % go through all correlation combinations and fill the ncc matrix
        for i_y = 1:size(f0,2)
            for i_x = 1:size(f1,2)
                % calculate ncc
                entry = 1/(N-1) * f1(:,i_x)' * f0(:,i_y);

                % asign NCC matrix entry with entry if entry >= min_corr
                %NCC_matrix(i_y, i_x) = (entry>=min_corr)*entry;
                NCC_matrix(i_y, i_x) = entry;
            end
        end

        dist = 1 ./ NCC_matrix;
    end


    % Calculate Correspondences between feature0 and feature1
    correspondence = zeros(4,min(size(dist)));
    i_corr = 1;
    while ~all(isinf(dist),'all')
        [~,i_min] = min(dist,[],'all','linear');
        [i2,j2] = ind2sub(size(dist),i_min);
        dist(i2,:) = Inf; dist(:,j2) = Inf;
        correspondence(1:2,i_corr) = f0(:,i2);
        correspondence(3:4,i_corr) = f1(:,j2);
        i_corr = i_corr+1;
    end

    correspondence = correspondence; %(:,1:min(100,length(correspondence)))
end

