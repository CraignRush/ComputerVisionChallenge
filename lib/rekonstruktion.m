function [T, R, lambda, M1, M2] = rekonstruktion(T1, T2, R1, R2, Korrespondenzen, K)

    do_plot = false;

    %% Preparation

    T_cell = {T1, T2, T1, T2};
    
    % R_cell wird als R1 R1 R2 R2 logisch erschlossen, da Kombination
    R_cell = {R1, R1, R2, R2};
    
    % Anzahl der Korrespondenzpunktpaare
    N = length(Korrespondenzen);
    % Korrespondenzen -> homogene Koordinaten
    x1_ = [Korrespondenzen(1:2,:); ones(1, N)];
    x2_ = [Korrespondenzen(3:4,:); ones(1, N)];
    
    % x1,x2 kallibrieren
    x1 = K \ x1_;
    x2 = K \ x2_;
    
    % Intitalisiere d_cell
    d_cell = {zeros(N,2),zeros(N,2),zeros(N,2),zeros(N,2)};
    
    %% Rekonstruktion

    % Get N
    N = length(Korrespondenzen);
    
    % Iterate over T_cell and R_cell
    for i = 1:4
        % Initialize M1, M2
        M1 = zeros(3*N,N+1);
        M2 = zeros(3*N,N+1);
        
        % get current iteration T,R
        T = T_cell{i};
        R = R_cell{i};
        
        for j=1:N
            % Calculate x1_hat and x2_ht by skewing
            x1_hat = [0 -x1(3,j) x1(2,j); x1(3,j) 0 -x1(1,j); -x1(2,j) x1(1,j) 0];
            x2_hat = [0 -x2(3,j) x2(2,j); x2(3,j) 0 -x2(1,j); -x2(2,j) x2(1,j) 0];
        
            
            M1(j*3-2:j*3,j) = x2_hat * R * x1(:,j);
            M1(j*3-2:j*3,N+1) = x2_hat * T;
            
            M2(j*3-2:j*3,j) = x1_hat * R' * x2(:,j);
            M2(j*3-2:j*3,N+1) = -x1_hat * R' * T;
            
        end
        
        % Calculate Lambdas (d1/d2) by SVD
        [~,~,V1] = svd(M1,0);
        d1 = V1(:,N+1);
        
        [~,~,V2] = svd(M2,0);
        d2 = V2(:,N+1);
        
        % gamma as last entry
        gamma1 = d1(end);
        gamma2 = d2(end);
        
        % normalize d1,2
        d1 = d1 ./ gamma1;
        d2 = d2 ./ gamma2; 

        % Store in d_cell
        d_cell{i} = [d1(1:end-1),d2(1:end-1)];
    end
    
    % calculate the positive depth information
    posdepthinfo = cellfun(@(ds) sum(sum(sign(ds))), d_cell);
    
    % Get index of maximum
    [~,max_posdepthinfo] = max(posdepthinfo);
    
    lambda = d_cell{max_posdepthinfo};
    R = R_cell{max_posdepthinfo};
    T = T_cell{max_posdepthinfo};
    
    %% Berechnung und Darstellung der 3D-Punkte und der Kameras
    
    % Calculate world points from 1
    P1 = bsxfun(@times, lambda(:,1)', x1);
    
    if do_plot
        % Draw P1 in figure and label
        figure,
        hold on
        for i = 1:length(P1)
            scatter3(P1(1,i), P1(2,i), P1(3,i), '.k');
            text(P1(1,i), P1(2,i), P1(3,i),num2str(i));
        end

        % Store edge values
        camC1 = [-0.2,0.2,0.2,-0.2;0.2,0.2,-0.2,-0.2;1,1,1,1];

        % Calculate values for C2 via euklidian transformations...
        camC2 = R \ (bsxfun(@plus, camC1, -T));

        % Calculate camera plane positions (closing the plane)
        cam1_plane = camC1(:,[1:4 1]);
        cam2_plane = camC2(:,[1:4 1]);

        % Plot camera plane
        plot3(cam1_plane(1,:), cam1_plane(2,:), cam1_plane(3,:), 'b');
        text(cam1_plane(1,4), cam1_plane(2,4), cam1_plane(3,4), 'C1');
        plot3(cam2_plane(1,:), cam2_plane(2,:), cam2_plane(3,:), 'r');
        text(cam2_plane(1,4), cam2_plane(2,4), cam2_plane(3,4), 'C2');


        % Set camera position
        campos([43, -22, -87]);
        camup([0,-1,0]);

        % Add grid and axis label
        xlabel('x'); ylabel('y'); zlabel('z');
        grid on;
    end
end