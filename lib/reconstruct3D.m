function I_3d = reconstruct3D(dispMap, B, f)
    I_3d = f*B ./ dispMap;
end