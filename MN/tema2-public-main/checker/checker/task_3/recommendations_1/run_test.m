function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_1.mat");
    load("../../input/task_3/ref_recommendations_1.mat");

    _recoms = recommendations("../../input/task_3/data_1.csv", 2, 1, 0, 3);
    if _recoms == recoms
        fprintf(fout, "%d", 1);
    else
        fprintf(fout, "%d", 0);
    endif


    fclose(fout);

endfunction

