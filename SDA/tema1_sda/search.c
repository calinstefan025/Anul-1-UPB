/*AVRAMONIU Calin-Stefan - 312CC*/
#include "search.h"

void search(Tren *tren, char *sir, FILE *g) {
    // alfam lungimea sirului cautat
    int len = strlen(sir);
    int poz = 0, gasit = 0;
    // luam un auxiliar unde construim sirul pentru a-l compara
    char aux[105];

    if (len > tren->lungime || len == 0) {
        fprintf(g, "ERROR\n");
        return;
    }

    // pornim de la mecanic
    Vagon *vagon_curent = tren->mecanic;
    Vagon *prima_pozitie;

    // folosim do while pentru a putea verifica si mecanicul la inceput
    do {
        // sarim peste locomotiva in cautarea sirului
        if (vagon_curent == tren->locomotiva) {
            vagon_curent = vagon_curent->next;
        }

        // adaugam valoarea vagonului la auxiliar
        aux[poz++] = vagon_curent->val;
        aux[poz] = '\0';
        // comparam sirurile la fiecare pas
        if (strstr(aux, sir) != NULL) {
            gasit = 1;
            // daca am gasit sirul, ne intoarcem cu "len" pozitii
            while (len - 1 > 0) {
                vagon_curent = vagon_curent->prev;
                len--;
            }
            prima_pozitie = vagon_curent;
            // in cazul in care ajungem pe locomotiva,
            // inseamna ca prima_pozitie este locomotiva->prev
            if (vagon_curent == tren->locomotiva)
                prima_pozitie = vagon_curent->prev;
            break;
        }
        vagon_curent = vagon_curent->next;
        // continuam pana la intalnirea mecanicului a 2-a oara
    } while (vagon_curent != tren->mecanic);

    if (gasit == 0) {
        fprintf(g, "ERROR\n");
        return;
    } else {
        tren->mecanic = prima_pozitie;
        return;
    }
}

// diferenta fata de functia search este ca vom merge pana la locomotiva
// si vom retine ultima pozitie a sirului cautat nu prima,
// astfel nu ne vom mai intoarce cu "len" pozitii in spate
void searchRight(Tren *tren, char *sir, FILE *g) {
    int len = strlen(sir);
    int poz = 0, gasit = 0;
    char aux[105];

    if (len > tren->lungime || len == 0) {
        fprintf(g, "ERROR\n");
        return;
    }

    Vagon *vagon_curent = tren->mecanic;
    Vagon *ultima_pozitie;

    while (vagon_curent != tren->locomotiva) {
        aux[poz++] = vagon_curent->val;
        aux[poz] = '\0';
        if (strstr(aux, sir) != NULL) {
            gasit = 1;
            ultima_pozitie = vagon_curent;
            break;
        }
        vagon_curent = vagon_curent->next;
    }

    if (gasit == 1) {
        tren->mecanic = ultima_pozitie;
        return;
    }
    if (gasit == 0) {
        fprintf(g, "ERROR\n");
        return;
    }
}

// se fac acceasi pasi ca la searchRight, doar ca ne vom deplasa in stanga
// folosind vagon_curent->prev
void searchLeft(Tren *tren, char *sir, FILE *g) {
    int len = strlen(sir);
    int poz = 0, gasit = 0;
    char aux[105];

    if (len > tren->lungime || len == 0) {
        fprintf(g, "ERROR\n");
        return;
    }

    Vagon *vagon_curent = tren->mecanic;
    Vagon *ultima_pozitie;

    while (vagon_curent != tren->locomotiva) {
        aux[poz++] = vagon_curent->val;
        aux[poz] = '\0';
        if (strstr(aux, sir) != NULL) {
            gasit = 1;
            ultima_pozitie = vagon_curent;
            break;
        }
        vagon_curent = vagon_curent->prev;
    }

    if (gasit == 1) {
        tren->mecanic = ultima_pozitie;
        return;
    }
    if (gasit == 0) {
        fprintf(g, "ERROR\n");
        return;
    }
}
