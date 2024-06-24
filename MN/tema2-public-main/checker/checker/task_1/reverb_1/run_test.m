function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_reverb_1.mat");
    load("../../input/task_1/ref_reverb_1.mat");

    _sig2_reverb = apply_reverb(sig2, impulse_response);
    save "output.mat" _sig2_reverb;

    dsig = abs(_sig2_reverb - sig2_reverb);

    is_sig_good = mean(dsig) < tol

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

