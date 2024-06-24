#include "game.h"

// initializam culorile
void init_colors() {
    init_pair(2, 1, COLOR_BLACK);
    init_pair(4, 2, COLOR_BLACK);
    init_pair(8, 3, COLOR_BLACK);
    init_pair(16, 4, COLOR_BLACK);
    init_pair(32, 5, COLOR_BLACK);
    init_pair(64, 6, COLOR_BLACK);
    init_pair(128, 7, COLOR_BLACK);
    init_pair(256, 8, COLOR_BLACK);
    init_pair(512, 9, COLOR_BLACK);
    init_pair(1024, 10, COLOR_BLACK);
    init_pair(2048, COLOR_RED, COLOR_BLACK);
}

// functia verifica daca a inceput jocul
int start_game(int *mat[]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (mat[i][j] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// functia modifica scorul in panou
void update_score(int val, int *scor, WINDOW *panou) {
    *scor = *scor + val;
    mvwprintw(panou, 2, 2, "Scor: %d", *scor);
    box(panou, 0, 0);
    wrefresh(panou);
}

// functia verifica daca mutarea este valida
int verificare_valid(int *mat[], int copie[][5]) {
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (copie[i][j] != mat[i][j]) {
                return 1;
            }
        }
    }

    return 0;
}

void verificare_mutari_valide(int *mat[], int *sus, int *st, int *dr,
                              int *jos) {
    *sus = 0;
    *st = 0;
    *dr = 0;
    *jos = 0;
    int i, j, val;
    // verificam daca exista o casuta care are vecin combinabil (EGAL)

    // verificam colturile
    val = mat[0][0];
    if (val != 0) {
        if (val == mat[0][1] || mat[0][1] == 0) *dr = *dr + 1;
        if (val == mat[1][0] || mat[1][0] == 0) *jos = *jos + 1;
    }

    val = mat[0][3];
    if (val != 0) {
        if (val == mat[0][2] || mat[0][2] == 0) *st = *st + 1;
        if (val == mat[1][3] || mat[1][3] == 0) *jos = *jos + 1;
    }

    val = mat[3][0];
    if (val != 0) {
        if (val == mat[3][1] || mat[3][1] == 0) *dr = *dr + 1;
        if (val == mat[2][0] || mat[2][1] == 0) *sus = *sus + 1;
    }

    val = mat[3][3];
    if (val != 0) {
        if (val == mat[3][2] || mat[3][2] == 0) *st = *st + 1;
        if (val == mat[2][3] || mat[2][3] == 0) *sus = *sus + 1;
    }

    // verificam elementele centrale ale primei coloane
    for (i = 1; i < 3; i++) {
        val = mat[i][0];
        if (val != 0) {
            if (val == mat[i - 1][0] || mat[i - 1][0] == 0) *sus = *sus + 1;
            if (val == mat[i + 1][0] || mat[i + 1][0] == 0) *jos = *jos + 1;
            if (val == mat[i][1] || mat[i][1] == 0) *dr = *dr + 1;
        }
    }
    // verificam elementele centrale ale ultimei coloane
    for (i = 1; i < 3; i++) {
        val = mat[i][3];
        if (val != 0) {
            if (val == mat[i - 1][3] || mat[i - 1][3] == 0) *sus = *sus + 1;
            if (val == mat[i + 1][3] || mat[i + 1][3] == 0) *jos = *jos + 1;
            if (val == mat[i][2] || mat[i][2] == 0) *st = *st + 1;
        }
    }
    // verificam elementele centrale ale primei linii
    for (i = 1; i < 3; i++) {
        val = mat[0][i];
        if (val != 0) {
            if (val == mat[0][i - 1] || mat[0][i - 1] == 0) *st = *st + 1;
            if (val == mat[0][i + 1] || mat[0][i + 1] == 0) *dr = *dr + 1;
            if (val == mat[1][i] || mat[1][i] == 0) *jos = *jos + 1;
        }
    }
    // verificam elementele centrale ale ultimi linii
    for (i = 1; i < 3; i++) {
        val = mat[3][i];
        if (val != 0) {
            if (val == mat[3][i - 1] || mat[3][i - 1] == 0) *st = *st + 1;
            if (val == mat[3][i + 1] || mat[3][i + 1] == 0) *dr = *dr + 1;
            if (val == mat[2][i] || mat[2][i] == 0) *sus = *sus + 1;
        }
    }

    // verificam elementele centrale ale matricei
    for (i = 1; i < 3; i++) {
        for (j = 1; j < 3; j++) {
            val = mat[i][j];
            if (val != 0) {
                if (val == mat[i][j + 1] || mat[i][j + 1] == 0) *dr = *dr + 1;
                if (val == mat[i + 1][j] || mat[i + 1][j] == 0) *jos = *jos + 1;
                if (val == mat[i][j - 1] || mat[i][j - 1] == 0) *st = *st + 1;
                if (val == mat[i - 1][j] || mat[i - 1][j] == 0) *sus = *sus + 1;
            }
        }
    }
}

// functia verifica daca exista o casuta cu valoarea 2048
int verificare_winner(int *mat[]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (mat[i][j] == 2048) {
                return 1;
            }
        }
    }

    return 0;
}

// functia verifica daca mai exista mutari posibile
int verificare_lose(int *mat[]) {
    int i, j, val;
    // verificam daca exista o casuta care are vecin combinabil (EGAL)

    // verificam daca exista casute libere
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (mat[i][j] == 0) {
                return 0;
            }
        }
    }

    // verificam colturile
    val = mat[0][0];
    if (val == mat[0][1] || val == mat[1][0]) return 0;
    val = mat[0][3];
    if (val == mat[0][2] || val == mat[1][3]) return 0;
    val = mat[3][0];
    if (val == mat[3][1] || val == mat[2][0]) return 0;
    val = mat[3][3];
    if (val == mat[3][2] || val == mat[2][3]) return 0;

    // verificam elementele centrale ale primei coloane
    for (i = 1; i < 3; i++) {
        val = mat[i][0];
        if (val == mat[i - 1][0] || val == mat[i + 1][0] || val == mat[i][1]) {
            // jocul inca nu s-a terminat
            return 0;
        }
    }

    // verificam elementele centrale ale ultimei coloane
    for (i = 1; i < 3; i++) {
        val = mat[i][3];
        if (val == mat[i - 1][3] || val == mat[i + 1][3] || val == mat[i][2]) {
            // jocul inca nu s-a terminat
            return 0;
        }
    }

    // verificam elementele centrale ale primei linii
    for (i = 1; i < 3; i++) {
        val = mat[0][i];
        if (val == mat[0][i - 1] || val == mat[0][i + 1] || val == mat[1][i]) {
            // jocul inca nu s-a terminat
            return 0;
        }
    }
    // verificam elementele centrale ale ultimi linii
    for (i = 1; i < 3; i++) {
        val = mat[3][i];
        if (val == mat[3][i - 1] || val == mat[3][i + 1] || val == mat[2][i]) {
            // jocul inca nu s-a terminat
            return 0;
        }
    }

    // verificam elementele centrale ale matricei
    for (i = 1; i < 3; i++) {
        for (j = 1; j < 3; j++) {
            val = mat[i][j];
            if (val == mat[i][j + 1] || val == mat[i + 1][j] ||
                val == mat[i][j - 1] || val == mat[i - 1][j]) {
                // jocul inca nu s-a terminat
                return 0;
            }
        }
    }

    // jocul s-a terminat si este pierdut
    return 1;
}

// functia genereaza o valoare random din {2,4} la o pozitie random
void generate_rand(int *mat[], int *val, int *posx, int *posy) {
    int rand_val[2] = {2, 4};
    int rand_index, ok = 0;
    srand(time(NULL));

    // generam o valoare random din multimea {2,4}
    rand_index = rand() % 2;
    *val = rand_val[rand_index];

    // generam pozitii random dar neocupate in matrice
    while (ok == 0) {
        *posx = rand() % 4;
        *posy = rand() % 4;
        if (mat[*posx][*posy] == 0) ok = 1;
    }
}

///////////////// functiile urmatoare afiseaza ecranele sugerate in antet
void afisare_meniu(WINDOW *meniu, int actiune_dorita) {
    // lista butoanelor din meniu
    char *lista[] = {"New Game", "Resume", "Quit"};
    int i;

    box(meniu, 0, 0);
    mvwaddstr(meniu, 1, 2, "MENIU");

    // aplicam efect de highlight cand selectam butonul
    for (i = 0; i < 3; ++i) {
        if (actiune_dorita == i) {
            wattron(meniu, A_REVERSE);
            mvwaddstr(meniu, (i + 3), 2, lista[i]);
            wattroff(meniu, A_REVERSE);
        } else {
            mvwaddstr(meniu, (i + 3), 2, lista[i]);
        }
    }

    wrefresh(meniu);
}

void afisare_tabla(WINDOW *tabla) {
    box(tabla, 0, 0);
    wrefresh(tabla);

    // desenam liniile orizontale din interiorul matricei
    mvwhline(tabla, 5, 0, ACS_HLINE, 40);
    mvwhline(tabla, 10, 0, ACS_HLINE, 40);
    mvwhline(tabla, 15, 0, ACS_HLINE, 40);
    mvwhline(tabla, 20, 0, ACS_HLINE, 40);

    // desenam liniile verticale din interiorul matricei
    mvwvline(tabla, 0, 10, ACS_VLINE, 20);
    mvwvline(tabla, 0, 20, ACS_VLINE, 20);
    mvwvline(tabla, 0, 30, ACS_VLINE, 20);
    mvwvline(tabla, 0, 40, ACS_VLINE, 20);

    // desenam plusurile dintre casute
    mvwaddch(tabla, 5, 10, ACS_PLUS);
    mvwaddch(tabla, 5, 20, ACS_PLUS);
    mvwaddch(tabla, 5, 30, ACS_PLUS);
    mvwaddch(tabla, 10, 10, ACS_PLUS);
    mvwaddch(tabla, 10, 20, ACS_PLUS);
    mvwaddch(tabla, 10, 30, ACS_PLUS);
    mvwaddch(tabla, 15, 10, ACS_PLUS);
    mvwaddch(tabla, 15, 20, ACS_PLUS);
    mvwaddch(tabla, 15, 30, ACS_PLUS);

    // desenam T pe margini pentru a nu lasa spatii libere
    mvwaddch(tabla, 0, 10, ACS_TTEE);
    mvwaddch(tabla, 0, 20, ACS_TTEE);
    mvwaddch(tabla, 0, 30, ACS_TTEE);

    mvwaddch(tabla, 5, 0, ACS_LTEE);
    mvwaddch(tabla, 10, 0, ACS_LTEE);
    mvwaddch(tabla, 15, 0, ACS_LTEE);

    mvwaddch(tabla, 20, 10, ACS_BTEE);
    mvwaddch(tabla, 20, 20, ACS_BTEE);
    mvwaddch(tabla, 20, 30, ACS_BTEE);

    mvwaddch(tabla, 5, 40, ACS_RTEE);
    mvwaddch(tabla, 10, 40, ACS_RTEE);
    mvwaddch(tabla, 15, 40, ACS_RTEE);

    // colturile tablei
    mvwaddch(tabla, 0, 40, ACS_URCORNER);
    mvwaddch(tabla, 20, 0, ACS_LLCORNER);

    wrefresh(tabla);
}

void afisare_instruct(WINDOW *instruct, int sus, int st, int dr, int jos) {
    // afisam instructiunile necesare pentru a efectua mutari
    box(instruct, 0, 0);

    // mvwprintw(instruct , 0 , 0 , "%d %d %d %d" , sus, st , dr , jos);

    if (sus > 0) {
        mvwaddstr(instruct, 1, 2, "W - sus - VALID    ");
    } else {
        mvwaddstr(instruct, 1, 2, "W - sus - INVALID");
    }
    if (jos > 0) {
        mvwaddstr(instruct, 2, 2, "S - jos - VALID    ");
    } else {
        mvwaddstr(instruct, 2, 2, "S - jos - INVALID");
    }
    if (dr > 0) {
        mvwaddstr(instruct, 3, 2, "D - dreapta - VALID   ");
    } else {
        mvwaddstr(instruct, 3, 2, "D - dreapta - INVALID");
    }
    if (st > 0) {
        mvwaddstr(instruct, 4, 2, "A - stanga - VALID    ");
    } else {
        mvwaddstr(instruct, 4, 2, "A - stanga - INVALID");
    }

    mvwaddstr(instruct, 6, 2, "U - Undo move");
    mvwaddstr(instruct, 8, 2, "Q - MENIU");

    wrefresh(instruct);
}

void afisare_panou(WINDOW *panou, int scor, struct tm *timp_local) {
    // curatam ecranul de valori reziduale ale scorului precedent
    int i;
    for (i = 2; i < 10; i++) {
        mvwprintw(panou, 2, i, "%s", " ");
    }

    // printam data si scorul curent pe panou
    mvwprintw(panou, 1, 2, "Data: %02d/%02d/%d %02d:%02d", timp_local->tm_mday,
              timp_local->tm_mon + 1, timp_local->tm_year + 1900,
              timp_local->tm_hour, timp_local->tm_min);
    mvwprintw(panou, 2, 2, "Scor: %d", scor);

    box(panou, 0, 0);
    wrefresh(panou);
}

void afisare_stats(WINDOW *stats, int *sus, int *jos, int *stanga, int *dreapta,
                   int *auto_move, int *undo) {
    mvwprintw(stats, 1, 2, "STATISTICI MUTARI:");

    mvwprintw(stats, 3, 2, "SUS: %d", *sus);
    mvwprintw(stats, 4, 2, "JOS: %d", *jos);
    mvwprintw(stats, 5, 2, "STANGA: %d", *stanga);
    mvwprintw(stats, 6, 2, "DREAPTA: %d", *dreapta);
    mvwprintw(stats, 7, 2, "AUTO: %d", *auto_move);
    mvwprintw(stats, 8, 2, "UNDO: %d", *undo);

    box(stats, 0, 0);
    wrefresh(stats);
}

void afisare_art(WINDOW *art) {
    // afisam artworkul ASCII pentru efectul vizual placut
    wprintw(art, "\n");
    wprintw(art, "\n");
    wprintw(art, "         ___   ___  _  _   ___  \n");
    wprintw(art, "        |__ \\ / _ \\| || | / _ \\ \n");
    wprintw(art, "           ) | | | | || || (_) |\n");
    wprintw(art, "          / /| | | |__  | > _ < \n");
    wprintw(art, "         / /_| |_| |  | || (_) |\n");
    wprintw(art, "        |____|\\___/   |_| \\___/\n");
    wrefresh(art);
}

void afisare_winner(WINDOW *winner) {
    // afisam mesajul in cazul castigului
    refresh();
    mvwprintw(winner, 5, 5, " __          _______ _   _ ");
    mvwprintw(winner, 6, 5, " \\ \\        / /_   _| \\ | |");
    mvwprintw(winner, 7, 5, "  \\ \\  /\\  / /  | | |  \\| |");
    mvwprintw(winner, 8, 5, "   \\ \\/  \\/ /   | | | . ` |");
    mvwprintw(winner, 9, 5, "    \\  /\\  /   _| |_| |\\  |");
    mvwprintw(winner, 10, 5, "     \\/  \\/   |_____|_| \\_|");
    box(winner, 0, 0);
    wrefresh(winner);
}

void afisare_lose(WINDOW *lose) {
    // afisam mesajul in cazul pierderii
    refresh();
    mvwprintw(lose, 5, 5, "  _      ____   _____ ______ ");
    mvwprintw(lose, 6, 5, " | |    / __ \\ / ____|  ____|");
    mvwprintw(lose, 7, 5, " | |   | |  | | (___ | |__   ");
    mvwprintw(lose, 8, 5, " | |   | |  | |\\___ \\|  __|  ");
    mvwprintw(lose, 9, 5, " | |___| |__| |____) | |____ ");
    mvwprintw(lose, 10, 5, " |______\\____/|_____/|______|");
    box(lose, 0, 0);
    wrefresh(lose);
}
/////////////////

// functia genereaza matricea initiala cu 2 valori random
void generate_initial_matrix(int *mat[]) {
    int i, j, rand_val = 0, rand_posx = 0, rand_posy = 0;

    // golim matricea de valori reziduale in urma jocurilor precedente
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mat[i][j] = 0;
        }
    }

    // generam cele 2 valori random de inceput
    generate_rand(mat, &rand_val, &rand_posx, &rand_posy);
    mat[rand_posx][rand_posy] = rand_val;

    generate_rand(mat, &rand_val, &rand_posx, &rand_posy);
    mat[rand_posx][rand_posy] = rand_val;
}

// functia genereaza o valoare random in casutele libere
void generate_next_move(int *mat[]) {
    int rand_val = 0, rand_posx = 0, rand_posy = 0;

    // se genereaza valoarea random pe pozitia random necesara mutarii urmatoare
    generate_rand(mat, &rand_val, &rand_posx, &rand_posy);
    mat[rand_posx][rand_posy] = rand_val;
}

// functia afiseaza matricea pe tabla de joc
void print_values(int *mat[], WINDOW *tabla) {
    int i;
    afisare_tabla(tabla);
    wrefresh(tabla);

    // se printeaza valorile la coordonatele urmatoare
    // se coloreaza in functie de valoarea elementului
    for (i = 0; i < 4; i++) {
        if (mat[0][i] != 0) {
            wattron(tabla, COLOR_PAIR(mat[0][i]));
            mvwprintw(tabla, 2, (i * 10) + 2, " %4d ", mat[0][i]);
            wattroff(tabla, COLOR_PAIR(mat[0][i]));
        } else {
            mvwprintw(tabla, 2, (i * 10) + 2, "     ");
        }
    }
    for (i = 0; i < 4; i++) {
        if (mat[1][i] != 0) {
            wattron(tabla, COLOR_PAIR(mat[1][i]));
            mvwprintw(tabla, 7, (i * 10) + 2, " %4d ", mat[1][i]);
            wattroff(tabla, COLOR_PAIR(mat[1][i]));
        } else {
            mvwprintw(tabla, 7, (i * 10) + 2, "     ");
        }
    }
    for (i = 0; i < 4; i++) {
        if (mat[2][i] != 0) {
            wattron(tabla, COLOR_PAIR(mat[2][i]));
            mvwprintw(tabla, 12, (i * 10) + 2, " %4d ", mat[2][i]);
            wattroff(tabla, COLOR_PAIR(mat[2][i]));
        } else {
            mvwprintw(tabla, 12, (i * 10) + 2, "     ");
        }
    }
    for (i = 0; i < 4; i++) {
        if (mat[3][i] != 0) {
            wattron(tabla, COLOR_PAIR(mat[3][i]));
            mvwprintw(tabla, 17, (i * 10) + 2, " %4d ", mat[3][i]);
            wattroff(tabla, COLOR_PAIR(mat[3][i]));
        } else {
            mvwprintw(tabla, 17, (i * 10) + 2, "     ");
        }
    }

    wrefresh(tabla);
}

// functia elibereaza memoria matricelor
void free_mat(int *mat[], int *last_move[]) {
    int i;
    for (i = 0; i < 4; i++) {
        free(mat[i]);
        free(last_move[i]);
    }
    free(mat);
    free(last_move);
}