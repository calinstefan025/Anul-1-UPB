function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_1.mat");

    _mat = read_mat("../../input/task_3/data_1.csv");
    if _mat == mat
        fprintf(fout, "%d", 1);
    else
        fprintf(fout, "%d", 0);
    endif


    fclose(fout);

endfunction

