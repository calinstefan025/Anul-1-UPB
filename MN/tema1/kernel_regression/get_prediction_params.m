function [a] = get_prediction_params (K, y, lambda)
  # TO DO: folosind metode neiterative, implementati logica
  # pentru a obtine vectorul coloana a, asa cum este descris in enuntul temei
  n = size(K);
  I = eye(n);
  L = cholesky(K + lambda * I);

  P = get_lower_inverse(L);
  
  a = P' * P * y * lambda;
endfunction