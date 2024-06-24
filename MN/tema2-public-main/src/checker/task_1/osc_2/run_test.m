function run_test()
    "task-1";
    tol = 1e-4;

    fout = fopen("out", "w");

    load("../../input/task_1/in_osc_2.mat");
    load("../../input/task_1/ref_osc_2.mat");

    _osc = oscillator(freq, fs, duration, attack, decay, sustain, release);
    save 'output.mat' _osc;

    dosc = abs(_osc - osc);

    is_osc_good = mean(dosc) < tol

    fprintf(fout, "%d", is_osc_good);

    fclose(fout);
endfunction

