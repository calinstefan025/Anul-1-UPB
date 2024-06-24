#include "game.h"
#include "movement.h"

#ifndef AI_DECISION
#define AI_DECISION

void copy_matrix(int *copie[], int *mat[]);
int empty_cells(int *copie[]);
int verificare_max(int a, int b, int c, int d);
int automated_decision(int *mat[]);

#endif