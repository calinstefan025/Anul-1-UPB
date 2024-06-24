function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_lowpass_1.mat");
    load("../../input/task_1/ref_lowpass_1.mat");

    _sig2_lowpass = low_pass(sig2, fs2, low_pass_cutoff);
    save "output.mat" _sig2_lowpass;

    dsig = abs(_sig2_lowpass - sig2_lowpass);

    is_sig_good = mean(dsig) < tol

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

