function signature = correspondence_lpm(img,feature,varargin)
    % Matlab inspired correspondence algorithm
    
    %% Input parser
    
    P = inputParser;
    
    % Liste der optionalen Parameter
    P.addOptional('window_size', 16, @(x) isnumeric(x) && (x==16 || x == 32))
    
    % Lese den Input
    P.parse(varargin{:});
    
    % Extrahiere die Variablen aus dem Input-Parser
    window_size  = P.Results.window_size;

    %% Renove border elements
    indices_tooclose = feature(1,:) < ceil(window_size/2) |...
            (size(img,2) - feature(1,:)) < floor(window_size/2) | ...
            feature(2,:) < ceil(window_size/2) | ...
            (size(img,1) - feature(2,:)) < floor(window_size/2);
    feature(:,indices_tooclose) = [];


    %% LPM
    if window_size == 16
        freq_sel = [17, 33, 49, 65, 81, 97, 18, 34, 50, 66, 82, 98,...
                   19, 35, 51, 67, 83, 99, 20, 36, 52, 68, 84, 100,...
                   145, 161, 177, 193, 209, 225, 146, 162, 178, 194,...
                   210, 226, 147, 163, 179, 195, 211, 227, 148, 164,...
                   180, 196, 212, 228];
    elseif window_size == 32
        freq_sel = [33, 65, 97, 129, 161, 193, 225, 34, 66, 98, 130,...
                    162, 194, 226, 35, 67, 99, 131, 163, 195, 227,...
                    36, 68, 100, 132, 164, 196, 228, 769, 801, 833,...
                    865, 897, 929, 961, 770, 802, 834, 866, 898, 930,...
                    962, 771, 803, 835, 867, 899, 931, 963, 772, 804,...
                    836, 868, 900, 932, 964];
    else
        error('Error!!!');
    end
    
    signature = zeros(size(feature,2),length(freq_sel));
    r = logspace(0,log10(window_size/2),window_size);
    th = linspace(0,2*pi*(1-1/window_size),window_size);
    
    for i_feature = 1:size(feature,2)
        window = extract_circle(feature([2 1],i_feature),img,r,th);
        window_fft = fftshift(fft2(window));
        signature(i_feature,:) = window_fft(freq_sel);
    end

end


function px = extract_circle(pt,img,radius,theta)
    x = radius'*cos(theta) + pt(1);
    y = radius'*sin(theta) + pt(2);
    px = interpolate_pixel([reshape(x,[],1),reshape(y,[],1)],img);
end

function val = interpolate_pixel(pt, img)
    assert(all(pt(:,1) >= 0 & pt(:,1) <= size(img,1)));
    assert(all(pt(:,2) >= 0 & pt(:,2) <= size(img,2)));
    val = zeros(1,size(pt,1));
    for i = 1:size(pt,1)
        if all(round(pt(i,:)) == pt(i,:))
            val(i) = img(pt(i,1),pt(i,2));
        else
            pt_ceil = ceil(pt(i,:));
            window = img(pt_ceil(1)+(0:1),pt_ceil(2)+(0:1));
            window = reshape(window,[],1);
            weight = [pt(i,1)-pt_ceil(1), 1-pt(i,1)+pt_ceil(1), ...
                pt(i,2)-pt_ceil(2), 1-pt(i,2)+pt_ceil(2)];
            val(i) = weight * double(window);
        end 
    end
end