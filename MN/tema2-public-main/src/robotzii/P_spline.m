function y_interp = P_spline(coef, x, x_interp)
    % nr de intervale 
    n = length(x) - 1;
    % nr de puncte de interpolare
	m = length(x_interp);
    y_interp = zeros(m);

	
    for j = 1:m
        % punctul curent de interpolare
        xi = x_interp(j);

        for i = 1:n
            if xi <= x(i+1)
                % extragem coeficientii
                a = coef(4*(i-1)+1);
                b = coef(4*(i-1)+2);
                c = coef(4*(i-1)+3);
                d = coef(4*(i-1)+4);

                % spline-ul cubic in punctul xi
                y_interp(j) = a + b*(xi - x(i)) + c*(xi - x(i))^2 + d*(xi - x(i))^3;
                break;
            endif
        endfor
    endfor
endfunction
