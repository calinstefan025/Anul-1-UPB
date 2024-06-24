function coef = vandermonde(x, y)
    % x = [x0, x1, ..., xn]'
    % y = [y0, y1, ..., yn]'
    % coef = [a0, a1, a2, ..., an]'

    % nr de puncte de interp
    n = length(x);
    coef = zeros(n , 1);

    % construim matricea vandermonde
    for i = 1:n
        for j = 1:n
            coef(j, i) = x(j) ^ (i - 1);
        endfor
    endfor

    % rezolvam sistemul
    coef = coef \ y';
endfunction
