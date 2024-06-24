function run_test()
    fout = fopen("out", "w");

    [x, y] = parse_data("../../input/task_2/input3.txt");
    coef = spline_c2(x, y);
    xlin = linspace(min(x), max(x), 10000)';
    ylin = P_spline(coef, x, xlin);

    for i = 1 : length(ylin)
        fprintf(fout, "%f ", ylin(i));
    endfor

    fclose(fout);
endfunction

