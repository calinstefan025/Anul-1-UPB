function reduced_mat = preprocess(mat, min_reviews)
    [m , n] = size(mat);
    
    valid_ind = zeros(m, 1);
    
    for i = 1:m
        nr_rev = 0;
        for j = 1:n
            if mat(i, j) > 0
                nr_rev = nr_rev + 1;
            endif
        endfor
        if nr_rev >= min_reviews
            valid_ind(i) = 1;
        endif
    endfor
    
    valid_ind = find(valid_ind);
    reduced_mat = mat(valid_ind, :);
endfunction