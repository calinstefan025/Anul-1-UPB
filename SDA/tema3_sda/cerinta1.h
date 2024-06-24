// Avramoniu Calin-Stefan 312CC
#ifndef CERINTA1_H
#define CERINTA1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura pentru un oras
// se retine si ruta formata din tronsoane pana in orasul respectiv
typedef struct oras {
    int id, nr_tronsoane;
    int id_drum;
    float uzura[1000];
    float uzura_medie;
    struct oras *next;
} Oras;

int verif_exist(char *oras, char nume_orase[1000][100], int *id_maxim);
void adauga_oras(Oras **oras, int id, float uzura[1000], int nr_tronsoane,
                 int id_drum);
void sort(int *id_rute_bune, int k);
void afisare(int id_maxim, Oras *lista_orase[1000], char nume_orase[1000][100],
             int nr_rute, int uzura_acceptata, FILE *g);
float max(float a, float b);
void calculare_uzura_medie(Oras *lista_orase[1000], int id_maxim);

#endif