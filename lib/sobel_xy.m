function [Fx, Fy] = sobel_xy(input_image)
    % In dieser Funktion soll das Sobel-Filter implementiert werden, welches
    % ein Graustufenbild einliest und den Bildgradienten in x- sowie in
    % y-Richtung zurueckgibt.

    % Interpolationsfilter
    di = [1  2 1];
    
    % Ableitungsfilter
    dd = [1 0 -1];
    
    % Ausnutzen der Separabilit?t des Sobel-Filters. 
    Fx=conv2(di,dd,input_image,'same');
    Fy=conv2(dd,di,input_image,'same');
end