function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_stereo_to_mono_1.mat");
    in_sig = sig;
    clear sig;

    load("../../input/task_1/ref_stereo_to_mono_1.mat");
    ref_sig = sig;
    clear sig;

    sig = stereo_to_mono(in_sig);
    save "output.mat" sig;

    dsig = abs(sig - ref_sig);

    is_sig_good = mean(dsig) < tol

    fprintf(fout, "%d", is_sig_good);

    fclose(fout);
endfunction

