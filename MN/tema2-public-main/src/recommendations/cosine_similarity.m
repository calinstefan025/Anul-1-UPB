function similarity = cosine_similarity(A, B)
   prod = A' * B;
   prod_norm = norm(A) * norm(B);
   similarity = prod / prod_norm;
endfunction
