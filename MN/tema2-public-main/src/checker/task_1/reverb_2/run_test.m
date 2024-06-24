function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_reverb_2.mat");
    load("../../input/task_1/ref_reverb_2.mat");

    _sig3_rev = apply_reverb(sig3, impulse_response);
    save "output.mat" _sig3_rev;

    dsig = abs(_sig3_rev - sig3_rev);

    is_sig_good = mean(dsig) < tol

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

