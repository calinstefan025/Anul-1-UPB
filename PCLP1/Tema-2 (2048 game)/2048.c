// pentru un aspect optim al aplicatiei se recomanda
// utilizarea terminalului nativ linux in full screen (eran 13")
#include "game.h"
// comtine functiile de afisare, verificare si de generare random
#include "movement.h"
// contine functiile de executare a comenzilor
#include "ai.h"
// contine functiile responsabile pentru decizia automata

#define FOREVER 1

int main(void) {
    // definim variabilele necesare
    int i, actiune_dorita = 0, actiune = -1, next_menu = 0, scor = 0,
           scor_vechi = 0, ai_move, valid = 0, ok = 1;
    // definim tipurile de mutari si le setam la 0
    int sus = 0, jos = 0, stanga = 0, dreapta = 0, auto_move = 0, undo = 0;
    int sus_v = 0, jos_v = 0, st_v = 0, dr_v = 0;
    int c;
    // definim variabilele de timp
    time_t timp, last_key_time, moment_actual;
    struct tm *timp_local;

    // definim matricele jocului si le alocam dinamic
    int **mat = (int **)malloc(5 * sizeof(int *));
    int **last_move = (int **)malloc(5 * sizeof(int *));
    for (i = 0; i < 4; i++) {
        mat[i] = (int *)malloc(5 * sizeof(int));
        last_move[i] = (int *)malloc(5 * sizeof(int));
    }

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    // initializam culorile
    start_color();
    init_colors();

    // generam artorkul principal
    WINDOW *art = initscr();
    art = newwin(10, 40, 0, 50);
    refresh();
    afisare_art(art);

    // generam meniul
    WINDOW *meniu = initscr();
    meniu = newwin(7, 40, 0, 0);
    keypad(meniu, TRUE);
    refresh();
    afisare_meniu(meniu, actiune_dorita);

    // generam panoul care contine data , ora si scorul
    WINDOW *panou = initscr();
    panou = newwin(4, 40, 7, 0);
    time(&timp);
    timp_local = localtime(&timp);
    refresh();
    afisare_panou(panou, scor, timp_local);

    // generam sectiunea cu cele mai bune scoruri
    WINDOW *stats = initscr();
    stats = newwin(10, 40, 11, 0);
    refresh();
    afisare_stats(stats, &sus, &jos, &stanga, &dreapta, &auto_move, &undo);

    // generam tabla ca un alt ecran bordat
    WINDOW *tabla = initscr();
    tabla = newwin(21, 41, 10, 50);
    refresh();
    afisare_tabla(tabla);

    // initializam alte ecrane necesare
    WINDOW *instruct = initscr();
    WINDOW *winner = initscr();
    WINDOW *lose = initscr();

    // se termina declararile de variabile si incepe loopul jocului
    while (FOREVER) {
        // afisam timpul si scorul pe tot parcursul jocului
        time(&timp);
        timp_local = localtime(&timp);
        afisare_panou(panou, scor, timp_local);
        last_key_time = time(NULL);

        // citim comanda din tastatura
        c = wgetch(meniu);

        switch (c) {
            case KEY_UP:
                // daca se apasa SUS cand suntem la prima pozitie mergem la
                // ultima
                if (actiune_dorita == 0) {
                    actiune_dorita = 2;
                    next_menu = 0;
                } else {
                    actiune_dorita = actiune_dorita - 1;
                    next_menu = 0;
                }
                break;

            case KEY_DOWN:
                // daca se apasa JOS cand suntem la ultima pozitie mergem la
                // prima
                if (actiune_dorita == 2) {
                    actiune_dorita = 0;
                    next_menu = 0;
                } else {
                    actiune_dorita = actiune_dorita + 1;
                    next_menu = 0;
                }
                break;

            default:
                break;
        }

        // daca se apasa ENTER inseamna ca selectam optiunea colorata
        if (c == 10) {
            actiune = actiune_dorita;
            next_menu = 1;
        }

        refresh();
        afisare_meniu(meniu, actiune_dorita);

        // daca a fost selectata o optiune se avanseaza la urmatorul meniu
        if (next_menu == 1) {
            // updatam timpul ultimei taste apasate
            last_key_time = time(NULL);

            if (actiune == 0) {
                // generam matricea initiala cu 2 valori din multimea {2,4}
                generate_initial_matrix(mat);
                copy_matrix(last_move, mat);
                print_values(mat, tabla);

                // initializam counterul mutarilor cu 0
                sus = 0;
                jos = 0;
                stanga = 0;
                dreapta = 0;
                auto_move = 0;
                undo = 0;
                wclear(stats);
                afisare_stats(stats, &sus, &jos, &stanga, &dreapta, &auto_move,
                              &undo);

                // regeneram scorul la fiecare joc nou
                wclear(panou);
                scor = 0;
                scor_vechi = 0;
                wrefresh(panou);
                afisare_panou(panou, scor, timp_local);

            // ne intoarcem in punctul acesta la selectarea resume
            // se pastreaza scorul
            currentGame:

                // se genereaza legenda
                instruct = newwin(10, 40, 21, 0);
                keypad(instruct, TRUE);
                refresh();
                verificare_mutari_valide(mat, &sus_v, &st_v, &dr_v, &jos_v);
                afisare_instruct(instruct, sus_v, st_v, dr_v, jos_v);

                nodelay(instruct, TRUE);

                while (FOREVER) {
                    sus_v = 0;
                    dr_v = 0;
                    jos_v = 0;
                    st_v = 0;
                    verificare_mutari_valide(mat, &sus_v, &st_v, &dr_v, &jos_v);
                    afisare_instruct(instruct, sus_v, st_v, dr_v, jos_v);

                    c = wgetch(instruct);

                    if (verificare_winner(mat) == 1) {
                        // inlocuim tabla cu panoul de castig
                        winner = newwin(21, 41, 10, 50);
                        afisare_winner(winner);
                        mvwprintw(winner, 13, 15, "SCOR: %d", scor);
                        wrefresh(winner);
                        c = 'q';
                    }

                    if (verificare_lose(mat) == 1) {
                        // inlocuim tabla cu panoul de lose
                        lose = newwin(21, 41, 10, 50);
                        afisare_lose(lose);
                        mvwprintw(lose, 13, 10, "INCEARCA INCA O DATA");
                        wrefresh(lose);
                        c = 'q';
                    }

                    if (c != ERR) {
                        // se pastreaza momentul ultimei taste apasate
                        // se reseteaza timpul afisat
                        time(&timp);
                        timp_local = localtime(&timp);
                        afisare_panou(panou, scor, timp_local);
                        last_key_time = time(NULL);

                        // daca se apasa Q ne vom intoarce la meniul principal
                        if (tolower(c) == 'q') {
                            keypad(meniu, TRUE);
                            refresh();
                            wrefresh(meniu);
                            next_menu = 0;
                            break;

                        } else if (verificare_lose(mat) == 0 &&
                                   verificare_winner(mat) == 0) {
                            // se executa miscarile pentru fiecare alegere
                            // daca mutarea e valida se modifica statisticile
                            switch (tolower(c)) {
                                case 'w':
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_up, mat, tabla, &scor,
                                                    panou);
                                    if (valid == 1) {
                                        ok = 1;
                                        sus++;
                                        afisare_stats(stats, &sus, &jos,
                                                      &stanga, &dreapta,
                                                      &auto_move, &undo);
                                    }
                                    break;
                                case 'a':
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_left, mat, tabla,
                                                    &scor, panou);
                                    if (valid == 1) {
                                        ok = 1;
                                        stanga++;
                                        afisare_stats(stats, &sus, &jos,
                                                      &stanga, &dreapta,
                                                      &auto_move, &undo);
                                    }
                                    break;
                                case 'd':
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_right, mat, tabla,
                                                    &scor, panou);
                                    if (valid == 1) {
                                        ok = 1;
                                        dreapta++;
                                        afisare_stats(stats, &sus, &jos,
                                                      &stanga, &dreapta,
                                                      &auto_move, &undo);
                                    }
                                    break;
                                case 's':
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_down, mat, tabla,
                                                    &scor, panou);
                                    if (valid == 1) {
                                        ok = 1;
                                        jos++;
                                        afisare_stats(stats, &sus, &jos,
                                                      &stanga, &dreapta,
                                                      &auto_move, &undo);
                                    }
                                    break;
                                case 'u':
                                    // ne intoarcem la ultima mutare
                                    copy_matrix(mat, last_move);
                                    // se reseteaza si scorul
                                    scor = scor_vechi;
                                    if (ok == 1) {
                                        undo++;
                                        ok = 0;
                                        afisare_stats(stats, &sus, &jos,
                                                      &stanga, &dreapta,
                                                      &auto_move, &undo);
                                    }
                                    wclear(panou);
                                    refresh();
                                    update_score(0, &scor, panou);
                                    time(&timp);
                                    timp_local = localtime(&timp);
                                    afisare_panou(panou, scor, timp_local);
                                    print_values(mat, tabla);
                                    wrefresh(tabla);
                                    wrefresh(panou);
                                    break;
                            }
                        }

                    } else if (verificare_winner(mat) == 0 &&
                               verificare_lose(mat) == 0) {
                        // se vede timpul actual
                        moment_actual = time(NULL);

                        if (moment_actual - last_key_time > 5) {
                            // daca nu s-a apasat niciu tasta 5 secunde ai-ul ia
                            // decizia se retuneaza codul mutarii (vezi functia
                            // automated_decision)
                            ai_move = automated_decision(mat);

                            if (ai_move != -1) {
                                if (ai_move == 0) {
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_up, mat, tabla, &scor,
                                                    panou);
                                } else if (ai_move == 1) {
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_left, mat, tabla,
                                                    &scor, panou);
                                } else if (ai_move == 2) {
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_right, mat, tabla,
                                                    &scor, panou);
                                } else if (ai_move == 3) {
                                    copy_matrix(last_move, mat);
                                    scor_vechi = scor;
                                    valid = do_move(move_down, mat, tabla,
                                                    &scor, panou);
                                }

                                if (valid == 1) {
                                    ok = 1;
                                    auto_move++;
                                    afisare_stats(stats, &sus, &jos, &stanga,
                                                  &dreapta, &auto_move, &undo);
                                }

                                // se reseteaza timpul ultimei taste apasate
                                last_key_time = time(NULL);
                            }
                        }
                    }
                }

                wclear(instruct);
                wrefresh(instruct);

            } else if (actiune == 1) {
                last_key_time = time(NULL);

                // ne intoarcem in loopul de joc atat timp cat Resume nu e prima
                // selectie a jucatorului
                if (start_game(mat) == 1) {
                    goto currentGame;
                } else {
                    continue;
                }

            } else if (actiune == 2) {
                // userul a selectat oprirea jocului
                endwin();
                // eliberam memoria
                free_mat(mat, last_move);
                return 0;
            }
        }
    }

    endwin();
    free_mat(mat, last_move);
    return 0;
}
