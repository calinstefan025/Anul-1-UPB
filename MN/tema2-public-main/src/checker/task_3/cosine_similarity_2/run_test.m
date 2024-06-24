function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_2.mat");

    similarity = cosine_similarity(mat(:, 124), mat(:, 452));
    fprintf(fout, "%f", similarity);

    fclose(fout);

endfunction

