function [x] = conjugate_gradient (A, b, x0, tol, max_iter) 
  # Implementati algoritmul pentru metoda gradientului conjugat
  r = b - A * x0;
  v = r;
  x = x0;
  tol_sq = tol ^ 2;
  k = 1;

  while k <= max_iter && (r' * r) > tol_sq
    tk = (r' * r) / (v' * A * v);
    x = x + tk * v;
    rk = r;
    r = r - tk * A * v;
    sk = (r' * r) / (rk' * rk);
    v = r + sk * v;
    k = k + 1;
  endwhile
endfunction