function [EF] = achtpunktalgorithmus(Korrespondenzen, K1, K2)
    % Diese Funktion berechnet die Essentielle Matrix oder Fundamentalmatrix
    % mittels 8-Punkt-Algorithmus, je nachdem, ob die Kalibrierungsmatrix 'K'
    % vorliegt oder nicht
    % Korrespondenzen in homogene Koordinaten
    x1 = [Korrespondenzen(1:2,:);ones(1,size(Korrespondenzen,2))];
    x2 = [Korrespondenzen(3:4,:);ones(1,size(Korrespondenzen,2))];

    % Wenn K vorliegt
    if(nargin>1)
        x1 = K1 \ x1;
        x2 = K2 \ x2;
    end
    
    % Berechne A mit dem Kronecker produkt (x1 op x2)...
    A = (kron(x1,ones(3,1)) .* kron(ones(3,1),x2))';
    
    % Singulärwertzerlegung für G
    [~,~,V] = svd(A);
    
    %% Schaetzung der Matrizen
    % G ist 9. Spalte von V in 3x3 Form
    G = reshape(V(:,9),3,3);
    
    % Singulärwertzerlegung von G für Minimierung
    [Ug,Sg,Vg] = svd(G);
    
    % Entweder Essentielle Matrix oder Fundamentalmatrix
    if(nargin>1)
        % Essentielle Matrix
        EF = Ug * diag([1,1,0]) * Vg';
    else
        % Fundamentalmatrix
        % Sg -> diag(s1, s2, 0)
        Sg(3,3) = 0;
        EF = Ug * Sg * Vg';
    end
end