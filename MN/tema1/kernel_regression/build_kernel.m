function [K] = build_kernel (X, f, f_param)
  [m n] = size(X);
  
  for i = 1:m
    for j = 1:m
      % pentru fiecare element din matrice aplicam functia f
      K(i,j) = f(X(i,:),X(j,:),f_param);
    endfor
  endfor
endfunction