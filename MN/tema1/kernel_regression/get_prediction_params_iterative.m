function [a] = get_prediction_params_iterative (K, y, lambda)
  # TO DO: folosind metode iterative, implementati logica
  # pentru a obtine vectorul coloana a, asa cum este descris in enuntul temei
  n = size(K);
  I = eye(n);
  a = zeros(n,1);
  x0 = zeros(n,1);
  
  a = conjugate_gradient(K + lambda * I , y , x0 , 1e-5 , 1000); 
endfunction
