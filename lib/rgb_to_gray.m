function gray_image = rgb_to_gray(input_image)
    % Diese Funktion soll ein RGB-Bild in ein Graustufenbild umwandeln. Falls
    % das Bild bereits in Graustufen vorliegt, soll es direkt zurueckgegeben werden.
    
    if size(input_image,3) == 1
        gray_image = input_image;
    elseif size(input_image,3) == 3
        img = double(input_image);
        gray_img = 0.299*img(:,:,1)+0.587*img(:,:,2)+0.114*img(:,:,3);
        gray_image = uint8(gray_img);
    else
        error('Input Image is neither 1 nor 3 channel image!');
    end
end