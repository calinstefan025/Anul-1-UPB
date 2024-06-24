function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_2.mat");
    load("../../input/task_3/ref_preprocess_2.mat");

    _reduced_mat = preprocess(mat, 15);
    if _reduced_mat == reduced_mat
        fprintf(fout, "%d", 1);
    else
        fprintf(fout, "%d", 0);
    endif


    fclose(fout);

endfunction

