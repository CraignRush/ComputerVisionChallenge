function Cake = cake(min_dist)
    % Die Funktion cake erstellt eine "Kuchenmatrix", die eine kreisfoermige
    % Anordnung von Nullen beinhaltet und den Rest der Matrix mit Einsen
    % auffuellt. Damit koennen, ausgehend vom staerksten Merkmal, andere Punkte
    % unterdrueckt werden, die den Mindestabstand hierzu nicht einhalten. 
    
    % Create X and Y directed distance-matrices
    [X,Y] = meshgrid(-min_dist:min_dist,-min_dist:min_dist);
    
    % Since the variable Cake has to logical (for whatever reason...), the variables is
    % assigned to logical 0 if the entry position is in an euklidian range of min_dist.
    Cake = sqrt(X.^2+Y.^2)>min_dist;

end