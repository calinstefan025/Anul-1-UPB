/*AVRAMONIU Calin-Stefan - 312CC*/
#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vagon {
    char val;
    struct Vagon *next;
    struct Vagon *prev;
} Vagon;

typedef struct Tren {
    Vagon *locomotiva;
    Vagon *mecanic;
    int lungime;
} Tren;

typedef struct nodComanda {
    char comanda[105];
    char argument[105];
    struct nodComanda *next;
    struct nodComanda *prev;
} nodComanda;

typedef struct Coada {
    nodComanda *head;
    nodComanda *tail;
    int capacitate;
} Coada;

#endif