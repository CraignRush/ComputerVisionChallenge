function sd = sampson_dist(F, x1_pixel, x2_pixel)
    % Diese Funktion berechnet die Sampson Distanz basierend auf der
    % Fundamentalmatrix F
    % schiefsymmetrische Matrix des Einheitsvektors e3
    e3_hat = [0 -1 0; 1 0 0; 0 0 0];
    
    % Sampson-Distanz
    sd = sum(x2_pixel .* (F * x1_pixel)).^2 ./ ( sum(( e3_hat * F * x1_pixel ).^2) + sum(( e3_hat * F' * x2_pixel ).^2));
    
end