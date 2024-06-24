function mat = read_mat(path)
  # TODO: Parse the .csv file and return the matrix of values (without row and column headers).
  file_mat = csvread(path);
  mat = file_mat(2 : end, 2 : end);
endfunction
