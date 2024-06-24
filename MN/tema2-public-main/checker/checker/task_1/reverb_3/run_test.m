function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_reverb_3.mat");
    load("../../input/task_1/ref_reverb_3.mat");

    _sig3_low_rev = apply_reverb(sig3_low, impulse_response);
    save "output.mat" _sig3_low_rev;

    dsig = abs(_sig3_low_rev - sig3_low_rev);

    is_sig_good = mean(dsig) < tol

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

