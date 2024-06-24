/*AVRAMONIU Calin-Stefan - 312CC*/
#ifndef UPDATE_H
#define UPDATE_H

#include "struct.h"
#include "query.h"
#include "search.h"
#include "queue.h"

void insertRight(Tren *tren, char val );
void insertLeft(Tren *tren, char val, FILE *g);
void moveLeft(Tren *tren);
void moveRight(Tren *tren);
void write(Tren *tren, char val );
void clearCell(Tren *tren);
void clearAll(Tren *tren);

#endif