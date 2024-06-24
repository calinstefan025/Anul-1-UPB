function coef = spline_c2 (x, y)
	% Remember that the indexes in Matlab start from 1, not 0

	% si(x)   = ai + bi(x - xi) + ci(x - xi)^2 + di(x - xi)^3
	% si'(x)  =      bi         + 2ci(x - xi)  + 3di(x - xi)^2
	% si''(x) =                   2ci          + 6di(x - xi)

	% TOOD 1: si(xi) = yi, i = 0 : n - 1

	% TODO 2: s_n-1(xn) = yn

	% TODO 3: si(x_i+1) = s_i+1(x_i+1), i = 0 : n - 1

	% TODO 4: si'(x_i+1) = s_i+1'(x_i+1), i = 0 : n - 1

	% TODO 5: si''(x_i+1) = s_i+1''(x_i+1), i = 0 : n - 1

	% TODO 6: s0''(x0) = 0

	% TODO 7: s_n-1''(x_n) = 0

	% Solve the system of equations
end
