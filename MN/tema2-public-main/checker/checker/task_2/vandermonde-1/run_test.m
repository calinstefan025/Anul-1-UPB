function run_test()
    fout = fopen("out", "w");

    [x, y] = parse_data("../../input/task_2/input1.txt");
    coef = vandermonde(x, y);

    for i = 1 : length(coef)
        fprintf(fout, "%f ", coef(i));
    endfor

    fclose(fout);
endfunction

