function [T1, R1, T2, R2, U, V]=TR_aus_E(E)
    % Diese Funktion berechnet die moeglichen Werte fuer T und R
    % aus der Essentiellen Matrix
    
    % SVD
    [U,S,V]=svd(E);
    
    % stellen Sie sicher, dass U und V Rotationsmatrizen sind.
    if det(U) < 0
	U = U*diag([1 1 -1]);
    end
    if det(V) < 0
    	V = V*diag([1 1 -1]);
    end
    
    % T im Kern(E^T), U_1,3 auch
    T1=U(:,3); 

    % T2 zeigt in andere Richtung
    T2=-T1;
    
    R1 = U*[0, -1, 0; 1, 0, 0;0, 0, 1]'*V';
    R2 = U*[0, 1, 0;-1, 0, 0;0, 0, 1]'*V';
    
end