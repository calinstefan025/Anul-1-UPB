function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_create_sound_1.mat");
    load("../../input/task_1/ref_create_sound_1.mat");

    csv_path = ["../../input/task_1/" filename];
    new_path = ["./" filename];
    copyfile(csv_path, new_path);

    [_sig2 _fs2] = create_sound(filename);
    save 'output.mat' _sig2 _fs2;

    dsig = abs(_sig2 - sig2);
    dfs = abs(_fs2 - fs2);

    is_sig_good = mean(dsig) < tol
    is_fs_good = dfs < tol

    fprintf(fout, "%d", is_sig_good & is_fs_good);

    fclose(fout);
endfunction

