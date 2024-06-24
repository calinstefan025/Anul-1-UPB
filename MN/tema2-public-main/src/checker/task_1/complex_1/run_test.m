function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_complex_1.mat");
    load("../../input/task_1/ref_complex_1.mat");

    sig3 = stereo_to_mono(sig3);
    sig3_low = low_pass(sig3, fs3, low_pass_cutoff);

    _sig3_low_rev = apply_reverb(sig3_low, impulse_response);
    save "output.mat" _sig3_low_rev;

    dsig = abs(_sig3_low_rev - sig3_low_rev);

    is_sig_good = mean(dsig) < tol;

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

