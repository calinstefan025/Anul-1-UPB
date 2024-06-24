function B = k_secv (A, k)
  % given an array [a b a b c] and k=2
  % should return [ab ba ab bc]
  % HINT: use strjoin 
  B = {};
  lungime = length(A) - k; %nr de secvente
  
  for i = 1 : lungime
    B{i} = strjoin(A(i : i+k-1), ' '); % concatenam cu spatiu
  end
  
  B = B';
endfunction
