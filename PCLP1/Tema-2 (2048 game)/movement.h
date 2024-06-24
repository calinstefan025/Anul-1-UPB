#include "game.h"

#ifndef MOVE_H
#define MOVE_H

int move_left(int *mat[], int *scor, WINDOW *panou, int ai_move);
int move_up(int *mat[], int *scor, WINDOW *panou, int ai_move);
int move_right(int *mat[], int *scor, WINDOW *panou, int ai_move);
int move_down(int *mat[], int *scor, WINDOW *panou, int ai_move);
int do_move(int (*op)(int *mat[], int *scor, WINDOW *panou, int ai_move),
            int *mat[], WINDOW *tabla, int *scor, WINDOW *panou);

#endif