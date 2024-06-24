function run_test()
    "task_3";
    fout = fopen("out", "w");

    load("../../input/task_3/data_1.mat");

    similarity = cosine_similarity(mat(:, 1), mat(:, 2));
    fprintf(fout, "%f", similarity);

    fclose(fout);

endfunction

