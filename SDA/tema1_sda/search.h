/*AVRAMONIU Calin-Stefan - 312CC*/
#ifndef SEARCH_H
#define SEARCH_H

#include "query.h"
#include "queue.h"
#include "struct.h"
#include "update.h"

void search(Tren *tren, char *sir, FILE *g);
void searchRight(Tren *tren, char *sir, FILE *g);
void searchLeft(Tren *tren, char *sir, FILE *g);

#endif