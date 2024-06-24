function y_interp = P_vandermonde (coef, x_interp)
	% P_vandermonde(x) = a0 + a1 * x + a2 * x^2 + ... + an * x^n
	% coef = [a0, a1, a2, ..., an]'
	% y_interp(i) = P_vandermonde(x_interp(i)), i = 0 : length(x_interp) - 1
	
	% TODO: Calcualte y_interp using the Vandermonde coefficients

    % nr de coeficienti
	n = length(coef);
    % nr de puncte de interp
    m = length(x_interp);
    y_interp = zeros(m, 1);

    % calculam pt fiecare punct valorile polinomului
    for i = 1:m
        for j = 1:n
            y_interp(i) = y_interp(i) + coef(j) * x_interp(i)^(j - 1);
        endfor
    endfor

endfunction
