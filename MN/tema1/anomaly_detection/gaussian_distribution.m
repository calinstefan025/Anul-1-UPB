% implementarea functiei care descrie probabilitatea de aparitie din cerinta
function probability = gaussian_distribution(X, mean_value, variance)
    probability = 0;
    [m n] = size(X);
    factor1 = ((2 * pi) ^ (n / 2)) * (det(variance) ^ (1 / 2));
    for i = 1 : m
      factor2 = (-1 / 2) * (X(i , :) - mean_value) * inv(variance) * (X(i , :) - mean_value)';
      factor2 = exp(factor2);
      probability(i) = factor2 / factor1;
    endfor
    probability = probability';
endfunction