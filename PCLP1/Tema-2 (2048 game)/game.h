#include <alloca.h>
#include <ctype.h>
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifndef GAME_H
#define GAME_H

///////////////////////////////////

void init_colors();
int start_game(int *mat[]);
void update_score(int val, int *scor, WINDOW *panou);
void free_mat(int *mat[], int *last_move[]);

///////////////////////////////////

int verificare_valid(int *mat[], int copie[][5]);
int verificare_winner(int *mat[]);
int verificare_lose(int *mat[]);
void verificare_mutari_valide(int *mat[], int *sus, int *st, int *dr, int *jos);

///////////////////////////////////

void generate_rand(int *mat[], int *val, int *posx, int *posy);
void generate_initial_matrix(int *mat[]);
void generate_next_move(int *mat[]);

///////////////////////////////////

void print_values(int *mat[], WINDOW *tabla);
void afisare_meniu(WINDOW *meniu, int actiune_dorita);
void afisare_tabla(WINDOW *tabla);
void afisare_instruct(WINDOW *instruct, int sus, int st, int dr, int jos);
void afisare_panou(WINDOW *panou, int scor, struct tm *timp_local);
void afisare_art(WINDOW *art);
void afisare_winner(WINDOW *winner);
void afisare_lose(WINDOW *lose);
void afisare_stats(WINDOW *stats, int *sus, int *jos, int *stanga, int *dreapta,
                   int *auto_move, int *undo);

///////////////////////////////////

#endif