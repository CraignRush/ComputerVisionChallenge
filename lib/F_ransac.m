function [Korrespondenzen_robust] = F_ransac(Korrespondenzen,varargin)

%% Input parser

P = inputParser;

% gewuenschte Wahrscheinlichkeit, dass der Algorithmus einen Satz
% Korrespondenzpunktpaare liefert, in dem sich kein Ausreisser befindet
P.addOptional('p', 0.5, @(x)isnumeric(x) && x > 0 && x < 1)

% geschaetzte Wahrscheinlichkeit, dass ein zufaellig gewaehltes
% Korrespondenzpunktpaar ein Ausreisser ist
P.addOptional('epsilon', 0.5, @(x)isnumeric(x) && x > 0 && x < 1);

% Toleranz, dass innerhalb dessen ein Korrespondenzpaar als zum
% Modell passend (Teil des Consensus-Sets) bewertet wird
P.addOptional('tolerance', 0.01, @isnumeric);

P.parse(varargin{:});

p           = P.Results.p;
epsilon     = P.Results.epsilon;
tolerance   = P.Results.tolerance;

if size(Korrespondenzen,1)==4
    x1_pixel = [Korrespondenzen(1:2,:);ones(1,length(Korrespondenzen))];
    x2_pixel = [Korrespondenzen(3:4,:);ones(1,length(Korrespondenzen))];
end

%Korrespondenzen_robust = {epsilon, p, tolerance, x1_pixel, x2_pixel};

%% RANSAC Algorithmus Vorbereitung - Init vars

% # of needed pts
k = 8;

% iteration number
s = ceil(log(1-p)/log(1-(1-epsilon)^k));

% max size of the currently found consensus set
largest_set_size = 0;

% sampson distance of the set above
largest_set_dist = Inf;

% fundamental matrix of the largest consensus set found
largest_set_F = zeros(3);

%Korrespondenzen_robust = {k, s, largest_set_size, largest_set_dist, largest_set_F};

%% RANSAC
i = 1;

while i <= s
    %choose randomly k points
    index = randperm(length(Korrespondenzen),k);
    
    % compute fundamental matrix from random points
    F = achtpunktalgorithmus(Korrespondenzen(:,index));
    % compute sampson distance
    dist_Sampson = sampson_dist(F,x1_pixel,x2_pixel);
    
    % select all points inside the tolerance
    current = dist_Sampson < tolerance;
    
    % # of inners and sum of Sampson-distances over random k
    current_set_size = numel(dist_Sampson(current));
    current_set_dist = sum(dist_Sampson(current));
    
    if (current_set_size > largest_set_size) || ...
            ((current_set_size == largest_set_size) && ...
            (current_set_dist < largest_set_dist))
        largest_set_dist = current_set_dist;
        largest_set_size = current_set_size;
        largest_set_F = F;
        consensus_indices = current;
    end
    i = i+1;
end

Korrespondenzen_robust = [x1_pixel(1:2,consensus_indices);...
    x2_pixel(1:2,consensus_indices)];

end