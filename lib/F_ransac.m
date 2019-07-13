function [Korrespondenzen_robust, F] = F_ransac(Korrespondenzen, varargin)
    % Diese Funktion implementiert den RANSAC-Algorithmus zur Bestimmung von
    % robusten Korrespondenzpunktpaaren
    
    %% Input parser
    P = inputParser;
    
    % List of parameter
    P.addOptional('epsilon', 0.5, @(x)isnumeric(x) && x > 0 && x < 1);
    P.addOptional('p', 0.5, @(x)isnumeric(x) && x > 0 && x < 1);
    P.addOptional('tolerance', 0.01, @isnumeric);
    
    % Get Input
    P.parse(varargin{:});
    
    % Assign variables
    p           = P.Results.p;
    epsilon     = P.Results.epsilon;
    tolerance   = P.Results.tolerance;
    
    % get x1 and x2 array
    x1_pixel = [Korrespondenzen(1:2,:);ones(1,length(Korrespondenzen))];
    x2_pixel = [Korrespondenzen(3:4,:);ones(1,length(Korrespondenzen))];
    
    %% RANSAC Algorithmus Vorbereitung
    % Anzahl der benoetigten Puntke
    k = 8;
    
    % Die Iterationszahl
    s = ceil( log(1-p)/log(1-(1-epsilon)^k) );

    % Zustandsvariable, die die Anzahl der Korrespondenzen im bisher groessten Consensus-Set speichern soll
    largest_set_size = 0;
    
    % Zustandsvariable, die die Sampson-Distanz des bisher groessten Consensus-Set speichern soll
    largest_set_dist = inf;
    
    % Ein Zwischenspeicher für die Fundamentalmatrix mit der das bisher groesste Consensus-Set gefunden wurde
    largest_set_F = zeros(3,3);
    
    selector = [];
    
    %% RANSAC Algorithmus
    
    for i = 1:s
        % Fundamentalmatrix F aus k zufaellig gewaelten Korrespondenzpunktpaaren
        F = achtpunktalgorithmus(Korrespondenzen(:,randperm(length(Korrespondenzen),k)));
        
        % Berechnen Sie die Sampson-Distanz effizient fuer alle Korrespondenzpunktpaaren
        sd = sampson_dist(F, x1_pixel, x2_pixel);
        
        % Korrespondenzpunktpaare in aktuellen Consensus-Set aufnehmen
        consensus_set_idx = sd < tolerance;
        consensus_set = sd(consensus_set_idx);
        
        % Bestimmen Sie für das aktuelle Consensus-Set die Anzahl der enthaltenen Paare 
        % und die absolute Set-Distanz indem sie die Sampson-Distanzen für das aktuelle 
        % Consensus-Set aufsummieren.
        current_set_size = numel(consensus_set);
        current_set_dist = sum(consensus_set);
        
        % Vergleichen Sie diese mit der bisher groessten Set-Groesse gespeichert in largest_set_size
        if current_set_size > largest_set_size || ((current_set_size == largest_set_size) && (current_set_dist < largest_set_dist))
            largest_set_dist = current_set_dist;
            largest_set_size = current_set_size;
            largest_set_F = F;
            selector = consensus_set_idx;
        end
    end
    Korrespondenzen_robust = [x1_pixel(1:2,selector);x2_pixel(1:2,selector)];
    F = largest_set_F;
end