function [P] = get_lower_inverse (L)
  # TO DO: Determinati printr-o metoda matriceala neiterativa inversa
  # unei matrici de tipul lower
  n = size(L,1);
  P = eye(n);
  
  for j = 1 : n
    for i = j + 1 : n
      % vedem ce element trb eliminat ca sa fie 0 sub diagonala
      elem = L(i,j) / L(j,j);
      % scadem din randul i un multiplu al randului j si in L si in P
      L(i,:) = L(i,:) - elem * L(j,:);
      P(i,:) = P(i,:) - elem * P(j,:);      
    endfor
      P(j,:) = P(j,:) / L(j,j);
  endfor
endfunction