function [repro_error, x2_repro] = rueckprojektion(Korrespondenzen, P1, Image2, T, R, K)
    % Diese Funktion berechnet den mittleren Rueckprojektionsfehler der 
    % Weltkooridnaten P1 aus Bild 1 im Cameraframe 2 und stellt die 
    % korrekten Merkmalskoordinaten sowie die rueckprojezierten grafisch dar.
    
    % P1 in Cameraframe 2
    P1_cam2 = bsxfun(@plus, R*P1, T);

    % Projection of P1_cam2 onto image plane
    x2_repro = K * bsxfun(@times, P1_cam2, 1./P1_cam2(3,:));
    
    % Show image2
    figure,
    imshow(Image2)
    hold on;
    
    % Show Korrespondenten and reprojections...
    for i = 1:length(Korrespondenzen)
        plot(Korrespondenzen(3,i), Korrespondenzen(4,i), 'go');
        plot(x2_repro(1,i), x2_repro(2,i), 'ro');
        line(Korrespondenzen(3:4,i), x2_repro(1:2,i));
        
        % To fix the submit error, add text...
        text(Korrespondenzen(3,i), Korrespondenzen(4,i), num2str(i)); 
        text(x2_repro(1,i), x2_repro(2,i), num2str(i));
    end
    
    % Calculate mean reprojection error
    repro_error = 0;
    for i = 1:length(Korrespondenzen)
        repro_error = repro_error + norm(x2_repro(1:2,i)-Korrespondenzen(3:4,i));
    end
    repro_error = repro_error / length(Korrespondenzen); 
end