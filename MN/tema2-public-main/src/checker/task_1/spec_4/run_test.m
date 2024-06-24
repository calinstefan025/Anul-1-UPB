function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_spec_4.mat");
    load("../../input/task_1/ref_spec_4.mat");

    [_S _f _t] = spectrogram(sig2_reverb, fs2, window_size);
    save 'output.mat' _S _f _t;

    dS = abs(_S - S);
    df = abs(_f - f);
    dt = abs(_t - t);

    is_S_good = mean(mean(dS)) < tol
    is_f_good = mean(df) < tol
    is_t_good = mean(dt) < tol

    fprintf(fout, "%d", is_S_good & is_f_good & is_t_good);

    fclose(fout);
endfunction

