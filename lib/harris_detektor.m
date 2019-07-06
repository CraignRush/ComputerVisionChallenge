function merkmale = harris_detektor(input_image, varargin)
    % In dieser Funktion soll der Harris-Detektor implementiert werden, der
    % Merkmalspunkte aus dem Bild extrahiert
    %% Input parser
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('segment_length', 15, @(x) isnumeric(x) && x>1 && mod(x,2)==1 && numel(x)==1)
    P.addOptional('k', 0.05, @(x) isnumeric(x) && x >=0 && x <= 1);
    P.addOptional('tau', 1e6, @(x) isnumeric(x) && x>0);
    P.addOptional('do_plot', false, @islogical);
    P.addOptional('min_dist',20,@(x) isnumeric(x) && x>=1);
    P.addOptional('tile_size',[200,200],@(x) isnumeric(x) && numel(x)<=2);
    P.addOptional('N',5,@(x) isnumeric(x) && x>=1);
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    segment_length  = P.Results.segment_length;
    k               = P.Results.k;
    tau             = P.Results.tau;
    do_plot         = P.Results.do_plot;
    min_dist        = P.Results.min_dist;
    tile_size       = P.Results.tile_size;
    if numel(tile_size) == 1
        tile_size = [tile_size,tile_size];
    end
    N               = P.Results.N;
    
    %% Vorbereitung zur Feature Detektion
    % Pruefe ob es sich um ein Grauwertbild handelt
    [n,m,ch] = size(input_image);
    assert(ch==1,"Image format has to be NxMx1");
    
    img = double(input_image);
    
    % Approximation des Bildgradienten
    [Ix, Iy] = sobel_xy(img);
    
    % Gewichtung
    gaussian = @(x,mu,sigma) 1/(sigma*sqrt(2*pi))*exp(-1/2*((x-mu)/sigma).^2);
    w = gaussian(-floor(segment_length/2):1:floor(segment_length/2),0,segment_length/5);
    w = w/sum(w);
    
    % Harris Matrix G
    G11 = double(conv2(w,w,Ix.^2, 'same'));
    G22 = double(conv2(w,w,Iy.^2, 'same'));
    G12 = double(conv2(w,w,Ix.*Iy, 'same'));
    
    %% Merkmalsextraktion ueber die Harrismessung

    % H = det(G) - k*tr(G)^2
    H = ((G11.*G22 - G12.^2) - k*(G11 + G22).^2);
    
    Mask = zeros(size(H));
    Mask((ceil(segment_length/2)+1):(size(H,1)-ceil(segment_length/2)),(ceil(segment_length/2)+1):(size(H,2)-ceil(segment_length/2)))=1;
    
    corners = H .* Mask;
    corners(corners<=tau)=0;
    
    %% Merkmalsvorbereitung
    % Create corners matrix with surrounding zeros by initially creating 
    % an oversized zero matrix and embedding the original corners matrix into
    [n,m] = size(corners);
    corners_w_nullrand = zeros(n+2*min_dist,m+2*min_dist);
    corners_w_nullrand(min_dist+1:end-min_dist,min_dist+1:end-min_dist) = corners;
    corners = corners_w_nullrand;
    
    % Extract all non-zero indices (at first separated into x and y)
    [row,col] = find(corners);
    
    % Create a new matrix that stores the 1-D index with the corresponding H value
    indices = zeros(length(row),2);
    for i = 1:length(row)
        indices(i,:) = [corners(row(i),col(i)), row(i)+col(i)*(n-1)];
    end
    
    % Sort the created matrix by the H values and extract the indices only
    sorted_index = sortrows(indices,'descend');
    sorted_index = sorted_index(:,2);
    
    
    %% Akkumulatorfeld
    % Berechne Anzahl an Kacheln
    img_size = size(input_image);
    kacheln_x = ceil(img_size(1) / tile_size(1));
    kacheln_y = ceil(img_size(2) / tile_size(2));
    
    % Erstelle AKKA
    AKKA = zeros(kacheln_x,kacheln_y);
    
    % Berechne und erstelle merkmale
    merkmale_n = min(numel(AKKA)*N,numel(sorted_index));
    merkmale = zeros(2, merkmale_n);
    
    %% Merkmalsbestimmung mit Mindestabstand und Maximalzahl pro Kachel

    Cake            = cake(min_dist);
    corner          = corners;
   
    
    % Anzahl an Merkmalen ungleich null und Größe des Suchfeldes
    no_points       = numel(sorted_index);
    size_corner     = size(corner);
   
    % Feature-Zähler
    feature_count   = 1;
    
    for current_point = 1:no_points
        % Nehme nächstes Element aus sortierter Liste
        pt_index    = sorted_index(current_point);
        % Überprüfen, ob dieser Merkmalspunkt noch gültig ist    
        if(corner(pt_index)==0)
            continue;
        else
            % Extrahiere Reihen- und Spalten-Index. Die Matlab-Funktion ind2sub macht das gleiche,
            % benötigt aber mehr Zeit.
            col     = floor(pt_index/size_corner(1));
            row     = pt_index - col*size_corner(1);
            col     = col + 1;
        end
    
        % Berechnung der Indizes, und damit der ID der zum gefundenen
        % Merkmalspunkt korrespondierenden Kachel Ex und Ey
        Ex          = floor((row-min_dist-1)/(tile_size(1)))+1;
        Ey          = floor((col-min_dist-1)/(tile_size(2)))+1;
        
        % Erhöhe den entsprechenden Eintrag im Akkumulatorarray
        AKKA(Ex,Ey) = AKKA(Ex,Ey)+1;
        
        % Multipliziere Region um den gefundenen Merkmalspunkt elementweise mit der Kuchenmaske
        corner(row-min_dist:row+min_dist,col-min_dist:col+min_dist) = corner(row-min_dist:row+min_dist,col-min_dist:col+min_dist).*Cake;
        
        % Teste, ob die entsprechende Kachel schon genügend Merkmale beinhaltet
        if AKKA(Ex,Ey) == N
            % Falls ja, setzte alle verbleibenden Merkmale innerhalb dieser Kachel auf 0
            corner((((Ex-1)*tile_size(1))+1+min_dist):min(size(corner,1),Ex*tile_size(1)+min_dist),(((Ey-1)*tile_size(2))+1+min_dist):min(size(corner,2),Ey*tile_size(2)+min_dist))=0;   
        end
        
        % Speichere den Merkmalspunkt und berücksichtige dabei den angefügten Nullrand.
        merkmale(:,feature_count) = [col-min_dist;row-min_dist];
        % Erhöhe den Zähler der Schleife
        feature_count = feature_count+1;
    end
    
    % Reduziere die Merkmalsliste auf die gültigen Merkmale
    merkmale = merkmale(:,1:feature_count-1);

    
    %% Plot
    if do_plot
        figure, colormap('gray');
        imagesc(input_image);
        hold on;
        plot(merkmale(1,:), merkmale(2,:), 'gs');
        plot(merkmale(1,:), merkmale(2,:), 'r.');
        axis('off');
    end
    
end