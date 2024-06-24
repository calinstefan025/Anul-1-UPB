#include "movement.h"

// functia de mutare la stanga
int move_left(int *mat[], int *scor, WINDOW *panou, int ai_move) {
    int i, j, k, aux[5], mutare_valida = 0, copie_matrice[5][5];

    // copiem matricea pentru a verifica ulterior validitatea mutarii
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            copie_matrice[i][j] = mat[i][j];
        }
    }

    // combinam valorile egale intre ele
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            // verificam numai casutele ocupate
            if (mat[i][j] != 0) {
                for (k = j + 1; k < 4; k++) {
                    // identificam urmatoarea casuta ocupata
                    if (mat[i][k] != 0) {
                        // comparam casutele ocupate
                        if (mat[i][j] == mat[i][k]) {
                            mat[i][j] = mat[i][j] + mat[i][k];
                            mat[i][k] = 0;
                            if (ai_move == 0) {
                                // updatam doar daca este inputul jucatorului
                                // nu updatam daca se testeaza mutarea automata
                                update_score(mat[i][j], scor, panou);
                            }
                        }
                        // ne oprim la gasirea altei valori diferite de 0 chiar
                        // daca nu le combinam
                        break;
                    }
                }
            }
        }

        // foloim auxiliar pt a shifta valorile nenule la stanga
        k = 0;
        for (j = 0; j < 4; j++) {
            if (mat[i][j] != 0) {
                aux[k] = mat[i][j];
                k++;
            }
        }

        // completam auxiliarul cu 0
        for (j = k; j < 4; j++) {
            aux[j] = 0;
        }

        // copiem auxiliarul in linia matricii
        for (j = 0; j < 4; j++) {
            mat[i][j] = aux[j];
        }
    }

    mutare_valida = verificare_valid(mat, copie_matrice);

    return mutare_valida;
}

// functia de mutare in sus
int move_up(int *mat[], int *scor, WINDOW *panou, int ai_move) {
    int i, j, k, aux[5], mutare_valida = 0, copie_matrice[5][5];

    // copiem matricea pentru a verifica ulterior validitatea mutarii
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            copie_matrice[i][j] = mat[i][j];
        }
    }

    // combinam valorile egale intre ele
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            // verificam numai casutele ocupate
            if (mat[i][j] != 0) {
                for (k = i + 1; k < 4; k++) {
                    // identificam urmatoarea casuta ocupata
                    if (mat[k][j] != 0) {
                        // comparam casutele ocupate
                        if (mat[i][j] == mat[k][j]) {
                            mat[i][j] = mat[i][j] + mat[k][j];
                            mat[k][j] = 0;
                            if (ai_move == 0) {
                                // updatam doar daca este inputul jucatorului
                                // nu updatam daca se testeaza mutarea automata
                                update_score(mat[i][j], scor, panou);
                            }
                        }
                        // ne oprim la gasirea altei valori diferite de 0 chiar
                        // daca nu le combinam
                        break;
                    }
                }
            }
        }

        // foloim auxiliar pt a shifta valorile nenule in sus
        k = 0;
        for (i = 0; i < 4; i++) {
            if (mat[i][j] != 0) {
                aux[k] = mat[i][j];
                k++;
            }
        }

        // completam auxiliarul cu 0
        for (i = k; i < 4; i++) {
            aux[i] = 0;
        }

        // copiem auxiliarul in linia matricii
        for (i = 0; i < 4; i++) {
            mat[i][j] = aux[i];
        }
    }

    mutare_valida = verificare_valid(mat, copie_matrice);

    return mutare_valida;
}

// functia de mutare la dreapta
int move_right(int *mat[], int *scor, WINDOW *panou, int ai_move) {
    // aplicam acelasi procedeu ca la functiile move_left / move_up
    int i, j, k, aux[5], mutare_valida = 0, copie_matrice[5][5];

    // copiem matricea pentru a verifica ulterior validitatea mutarii
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            copie_matrice[i][j] = mat[i][j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 3; j > 0; j--) {
            if (mat[i][j] != 0) {
                for (k = j - 1; k >= 0; k--) {
                    if (mat[i][k] != 0) {
                        if (mat[i][j] == mat[i][k]) {
                            mat[i][j] = mat[i][j] + mat[i][k];
                            mat[i][k] = 0;
                            if (ai_move == 0) {
                                // updatam doar daca este inputul jucatorului
                                // nu updatam daca se testeaza mutarea automata
                                update_score(mat[i][j], scor, panou);
                            }
                        }
                        break;
                    }
                }
            }
        }

        k = 3;
        for (j = 3; j >= 0; j--) {
            if (mat[i][j] != 0) {
                aux[k] = mat[i][j];
                k--;
            }
        }

        for (j = k; j >= 0; j--) {
            aux[j] = 0;
        }

        for (j = 3; j >= 0; j--) {
            mat[i][j] = aux[j];
        }
    }

    mutare_valida = verificare_valid(mat, copie_matrice);

    return mutare_valida;
}

// functia de mutare in jos
int move_down(int *mat[], int *scor, WINDOW *panou, int ai_move) {
    int i, j, k, aux[5], mutare_valida = 0, copie_matrice[5][5];

    // copiem matricea pentru a verifica ulterior validitatea mutarii
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            copie_matrice[i][j] = mat[i][j];
        }
    }

    for (j = 0; j < 4; j++) {
        for (i = 3; i > 0; i--) {
            if (mat[i][j] != 0) {
                for (k = i - 1; k >= 0; k--) {
                    if (mat[k][j] != 0) {
                        if (mat[i][j] == mat[k][j]) {
                            mat[i][j] = mat[i][j] + mat[k][j];
                            mat[k][j] = 0;
                            if (ai_move == 0) {
                                // updatam doar daca este inputul jucatorului
                                // nu updatam daca se testeaza mutarea automata
                                update_score(mat[i][j], scor, panou);
                            }
                        }
                        break;
                    }
                }
            }
        }

        k = 3;
        for (i = 3; i >= 0; i--) {
            if (mat[i][j] != 0) {
                aux[k] = mat[i][j];
                k--;
            }
        }

        for (i = k; i >= 0; i--) {
            aux[i] = 0;
        }

        for (i = 3; i >= 0; i--) {
            mat[i][j] = aux[i];
        }
    }

    mutare_valida = verificare_valid(mat, copie_matrice);

    return mutare_valida;
}

// functia de executare a mutarii (se foloseste de cele de mai sus) si
// returneaza validitatea
int do_move(int (*op)(int *mat[], int *scor, WINDOW *panou, int ai_move),
            int *mat[], WINDOW *tabla, int *scor, WINDOW *panou) {
    int valid;
    // efectuam mutarea propriu-zisa
    valid = op(mat, scor, panou, 0);

    // exista alte mutari posibile
    if (valid == 1) {
        // mutare valida => generam urmatoarea valoare random
        generate_next_move(mat);
    }
    print_values(mat, tabla);
    refresh();

    // returnam validitatea mutarii
    return valid;
}
