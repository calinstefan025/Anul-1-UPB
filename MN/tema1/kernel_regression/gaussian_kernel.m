function retval = gaussian_kernel (x, y, sigma)
  # TO DO: implement gaussian kernel function
  factor = ((norm(x - y) ^ 2) / (2 * sigma ^ 2));
  retval = exp(-factor);
endfunction
