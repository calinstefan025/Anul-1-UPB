function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_2.mat");
    load("../../input/task_3/ref_recommendations_3.mat");

    _recoms = recommendations("../../input/task_3/data_2.csv", 10, 10, 15, 100);
    if _recoms == recoms
        fprintf(fout, "%d", 1);
    else
        fprintf(fout, "%d", 0);
    endif


    fclose(fout);

endfunction

