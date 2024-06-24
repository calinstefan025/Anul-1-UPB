function retval = word_idx (distinct_wds)
    % return the word_idx dictionary HINT: containers.Map
    lungime = length(distinct_wds);
    retval = containers.Map(distinct_wds, 1 : lungime);
endfunction
