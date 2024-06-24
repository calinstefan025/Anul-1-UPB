function coef = spline_c2(x, y)
    % Remember that the indexes in Matlab start from 1, not 0

    % si(x)   = ai + bi(x - xi) + ci(x - xi)^2 + di(x - xi)^3
    % si'(x)  =      bi         + 2ci(x - xi)  + 3di(x - xi)^2
    % si''(x) =                   2ci          + 6di(x - xi)

    % numarul de intervale
    n = length(x) - 1;

    A = zeros(4*n, 4*n);
    b = zeros(4*n, 1);

    rand = 1;

    % TODO 1: si(xi) = yi
    for i = 1:n
        A(rand, 4*(i-1)+1:4*(i-1)+4) = [1, 0, 0, 0];
        b(rand) = y(i);
        rand = rand + 1;
    endfor

    % TODO 2: s_n-1(xn) = yn
    ult_xn = x(n+1) - x(n);
    A(rand, 4*(n-1)+1:4*(n-1)+4) = [1, ult_xn, ult_xn^2, ult_xn^3];
    b(rand) = y(n+1);
    rand = rand + 1;

    % TODO 3: si(x_i+1) = s_i+1(x_i+1)
    for i = 1:n-1
        xi1 = x(i+1) - x(i);
        A(rand, 4*(i-1)+1:4*(i-1)+4) = [1, xi1, xi1^2, xi1^3];
        A(rand, 4*i+1:4*i+4) = [-1, 0, 0, 0];
        b(rand) = 0;
        rand = rand + 1;
    endfor

    % TODO 4: si'(x_i+1) = s_i+1'(x_i+1)
    for i = 1:n-1
        xi1 = x(i+1) - x(i);
        A(rand, 4*(i-1)+1:4*(i-1)+4) = [0, 1, 2*xi1, 3*xi1^2];
        A(rand, 4*i+1:4*i+4) = [0, -1, 0, 0];
        b(rand) = 0;
        rand = rand + 1;
    endfor

    % TODO 5: si''(x_i+1) = s_i+1''(x_i+1)
    for i = 1:n-1
        xi1 = x(i+1) - x(i);
        A(rand, 4*(i-1)+1:4*(i-1)+4) = [0, 0, 2, 6*xi1];
        A(rand, 4*i+1:4*i+4) = [0, 0, -2, 0];
        b(rand) = 0;
        rand = rand + 1;
    endfor

    % TODO 6: s0''(x0) = 0
    A(rand, 3) = 2;
    b(rand) = 0;
    rand = rand + 1;

    % TODO 7: s_n-1''(x_n) = 0
    A(rand, 4*(n-1)+3:4*(n-1)+4) = [2, 6*ult_xn];
    b(rand) = 0;

    % Solve the system of equations
    coef = A\b;
endfunction
