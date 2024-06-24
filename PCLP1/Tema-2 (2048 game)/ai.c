#include "ai.h"

// functia copiaza matricea mat in copie
void copy_matrix(int *copie[], int *mat[]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            copie[i][j] = mat[i][j];
        }
    }
}

// functia verifica daca exista casute goale
int empty_cells(int *copie[]) {
    int i, j, empty = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (copie[i][j] == 0) {
                empty++;
            }
        }
    }

    return empty;
}

// functia verifica maximul dintre 4 valori
// este folosita pentru a determina mutarea optima
int verificare_max(int a, int b, int c, int d) {
    int m1 = 0, m2 = 0, m = 0;
    if (a > b)
        m1 = a;
    else
        m1 = b;

    if (c > d)
        m2 = c;
    else
        m2 = d;

    if (m1 > m2)
        m = m1;
    else
        m = m2;

    // nu exista mutari valide
    if (m == 0) return -1;

    // returnam mutarea care produce cele mai multe casute libere
    if (a == m) return 0;
    if (b == m) return 1;
    if (c == m) return 2;
    if (d == m) return 3;

    // nu se ajunge aici (evitam un warning)
    return -1;
}

// functia responsabila pentru decizia automata
int automated_decision(int *mat[]) {
    // functia returneaza miscarea ideala pentru a elibera cat mai multe casute
    // 0 = move_up
    // 1 = move_left
    // 2 = move_right
    // 3 = move_down
    // -1 = toate mutarile sunt invalide

    int max_0 = 0, max_1 = 0, max_2 = 0, max_3 = 0, ai_move = 0, dummy_scor = 0,
        i, valid;
    // copiem matricea intr-o copie pentru a testa mutarile
    int **copie = (int **)malloc(5 * sizeof(int *));
    for (i = 0; i < 4; i++) {
        copie[i] = (int *)malloc(5 * sizeof(int));
    }

    // facem un panou si un scor pentru a avea ce sa punem la parametrii (nu
    // conteaza outputul)
    WINDOW *dummy_win = initscr();

    // verificam mutarile pe matricea copie
    copy_matrix(copie, mat);
    valid = move_up(copie, &dummy_scor, dummy_win, 1);
    if (valid == 1) {
        max_0 = empty_cells(copie);
    }

    copy_matrix(copie, mat);
    valid = move_left(copie, &dummy_scor, dummy_win, 1);
    if (valid == 1) {
        max_1 = empty_cells(copie);
    }

    copy_matrix(copie, mat);
    valid = move_right(copie, &dummy_scor, dummy_win, 1);
    if (valid == 1) {
        max_2 = empty_cells(copie);
    }

    copy_matrix(copie, mat);
    valid = move_down(copie, &dummy_scor, dummy_win, 1);
    max_3 = empty_cells(copie);
    if (valid == 1) {
        max_3 = empty_cells(copie);
    }

    // vedem care mutare elibereaza mai multe casute
    ai_move = verificare_max(max_0, max_1, max_2, max_3);

    for (i = 0; i < 4; i++) {
        free(copie[i]);
    }
    free(copie);

    return ai_move;
}
