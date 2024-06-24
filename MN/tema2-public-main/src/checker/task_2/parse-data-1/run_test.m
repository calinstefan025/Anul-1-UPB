function run_test()
    fout = fopen("out", "w");

    [x, y] = parse_data("../../input/task_2/input1.txt");

    for i = 1 : length(x)
        fprintf(fout, "%d ", x(i));
    endfor
    fprintf(fout, "\n");
    for i = 1 : length(y)
        fprintf(fout, "%d ", y(i));
    endfor

    fclose(fout);
endfunction

