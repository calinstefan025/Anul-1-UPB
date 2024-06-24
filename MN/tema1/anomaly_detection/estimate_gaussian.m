% This function estimates the parameters of a Gaussian distribution using the data in X.
% implementarea primelor 2 formule din cerinta
function [mean_values variances] = estimate_gaussian(X)
     [m n] = size(X);
     mean_values = zeros(1,n); % vectorul medie
     variances = zeros(n,n); % matricea de varianta
     
     for i = 1 : n
       suma = 0;
       for k = 1 : m
         suma = suma + X(k , i);
       endfor
       mean_values(i) = suma / m;
     endfor
     
     suma = 0;
     for k = 1 : m
       suma = suma + (((X(k , :) - mean_values)')*(X(k , :) - mean_values))
     endfor
     variances = suma / m;
endfunction
