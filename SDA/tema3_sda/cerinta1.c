// Avramoniu Calin-Stefan 312CC
#include "cerinta1.h"

// functie care verifica daca un oras exista deja in matricea de cuvinte
// intoarce id-ul orasului
int verif_exist(char *oras, char nume_orase[1000][100], int *id_maxim) {
    int i;
    for (i = 0; i < *id_maxim; i++) {
        if (strcmp(oras, nume_orase[i]) == 0) {
            return i;
        }
    }
    strcpy(nume_orase[*id_maxim], oras);
    *id_maxim = *id_maxim + 1;

    // daca orasul nu exista ii dam un id nou
    return *id_maxim - 1;
}

// functie care adauga un oras in lista de adiacenta
void adauga_oras(Oras **oras, int id, float uzura[1000], int nr_tronsoane,
                 int id_drum) {
    int i;
    Oras *oras_adaugat = (Oras *)malloc(sizeof(Oras));
    oras_adaugat->id = id;
    oras_adaugat->id_drum = id_drum;
    oras_adaugat->nr_tronsoane = nr_tronsoane;
    for (i = 0; i < nr_tronsoane; i++) {
        oras_adaugat->uzura[i] = uzura[i];
    }
    oras_adaugat->next = NULL;

    if (*oras != NULL) {
        Oras *oras_aux = *oras;
        while (oras_aux->next != NULL) {
            oras_aux = oras_aux->next;
        }
        oras_aux->next = oras_adaugat;
    } else {
        *oras = oras_adaugat;
    }
}

// functie care sorteaza vectorul ce trebuie afisat la final
// vectorul contine rutele bune
void sort(int *id_rute_bune, int k) {
    int i, j, aux;
    for (i = 0; i < k; i++) {
        for (j = i + 1; j < k; j++) {
            if (id_rute_bune[i] > id_rute_bune[j]) {
                aux = id_rute_bune[i];
                id_rute_bune[i] = id_rute_bune[j];
                id_rute_bune[j] = aux;
            }
        }
    }
}

// functie de afisare
void afisare(int id_maxim, Oras *lista_orase[1000], char nume_orase[1000][100],
             int nr_rute, int uzura_acceptata, FILE *g) {
    int i, j, id, id_rute_bune[1000], k = 0;

    for (id = 0; id < nr_rute; id++) {
        for (i = 0; i < id_maxim; i++) {
            Oras *oras_aux = lista_orase[i];
            while (oras_aux != NULL) {
                if (id == oras_aux->id_drum) {
                    fprintf(g, "%s ", nume_orase[i]);
                    fprintf(g, "%s ", nume_orase[oras_aux->id]);
                    fprintf(g, "%d ", oras_aux->nr_tronsoane);
                    for (j = 0; j < oras_aux->nr_tronsoane; j++) {
                        fprintf(g, "%.2f ", oras_aux->uzura[j]);
                    }
                    fprintf(g, "\n");
                }
                oras_aux = oras_aux->next;
            }
        }
    }

    // daca uzura medie < uzura_acceptata
    // adaugam id-ul rutei in vectorul id_rute_bune
    for (i = 0; i < id_maxim; i++) {
        Oras *oras_aux = lista_orase[i];
        while (oras_aux != NULL) {
            if (oras_aux->uzura_medie < uzura_acceptata) {
                id_rute_bune[k] = oras_aux->id_drum + 1;
                k++;
            }
            oras_aux = oras_aux->next;
        }
    }

    // sortare id_rute_bune
    sort(id_rute_bune, k);

    // afisare rute bune
    for (i = 0; i < k; i++) {
        fprintf(g, "%d ", id_rute_bune[i]);
    }
}

// functie care returneaza maximul dintre doua numere float
float max(float a, float b) {
    if (a > b) {
        return a;
    }
    return b;
}

// functie care calculeaza uzura medie a fiecarei rute
void calculare_uzura_medie(Oras *lista_orase[1000], int id_maxim) {
    int i, j;
    float uzura_totala;
    for (i = 0; i < id_maxim; i++) {
        Oras *oras_aux = lista_orase[i];
        uzura_totala = 0;
        while (oras_aux != NULL) {
            uzura_totala = 0;
            for (j = 0; j < oras_aux->nr_tronsoane; j++) {
                uzura_totala += oras_aux->uzura[j];
            }
            oras_aux->uzura_medie = uzura_totala / oras_aux->nr_tronsoane;
            oras_aux = oras_aux->next;
        }
    }
}