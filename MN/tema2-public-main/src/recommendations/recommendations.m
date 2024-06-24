function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
  % citima matricea
  mat = read_mat(path);
  % eliminam userii cu reviewuri insuficiente
  mat = preprocess(mat , min_reviews);
  
  % descompunem in svd
  [U, Sigma, V] = svds(mat, num_features);
  
  % matricea de teme este V
  themes = V;
  n = size(themes , 1);
  similarity = zeros(1 , n);
  
  % daca i = liked_theme il sarim
  for i = setdiff(1:n , liked_theme)
    similarity(i) = cosine_similarity(themes(liked_theme , :)' , themes(i , :)');
  endfor
  
  % sortam temele dupa similaritate
  [unused_var, indici_sort] = sort(similarity , 'descend');
  
  % primele num_recoms sunt date ca recomandari
  for i = 1:num_recoms
    recoms(i) = indici_sort(i);
  endfor
endfunction
