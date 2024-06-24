function run_test()
    fout = fopen("out", "w");

    [x, y] = parse_data("../../input/task_2/input3.txt");
    coef = spline_c2(x, y);

    for i = 1 : length(coef)
        fprintf(fout, "%f ", coef(i));
    endfor

    fclose(fout);
endfunction

