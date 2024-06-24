function [L] = cholesky(A)
    [n n] = size(A);
    
    L = zeros(n);
  
    for j = 1 : n
      % calculam elementele de pe diagonala principala
      suma_l = L(j, 1 : (j - 1)) * L(j, 1 : (j - 1))';
      L(j, j) = sqrt(A(j, j) - suma_l);
        
      for i = (j + 1) : n
        suma_l = L(j, 1 : (j - 1)) * L(i, 1 : (j - 1))';
        L(i, j) = (A(i, j) - suma_l) / L(j, j);
      endfor
    endfor
endfunction