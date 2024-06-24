/*AVRAMONIU Calin-Stefan - 312CC*/
#include "update.h"

void insertRight(Tren *tren, char val) {
    // alocam memorie pentru noul vagon
    Vagon *vagon_nou = (Vagon *)malloc(sizeof(Vagon));
    // adaugam valoarea in noul vagon
    vagon_nou->val = val;

    // cazul in care mecanicul este in ultimul vagon
    if (tren->mecanic->next == tren->locomotiva) {
        vagon_nou->next = tren->locomotiva;
        vagon_nou->prev = tren->mecanic;
        tren->mecanic->next = vagon_nou;
        tren->locomotiva->prev = vagon_nou;
        // mutam mecanicul in noul vagon
        tren->mecanic = vagon_nou;
    } else {
        // conectam vagonul la cei 2 vecini
        vagon_nou->next = tren->mecanic->next;
        vagon_nou->prev = tren->mecanic;
        // conectam vecinii la noul vagon
        tren->mecanic->next->prev = vagon_nou;
        tren->mecanic->next = vagon_nou;
        // mutam mecanicul in noul vagon
        tren->mecanic = vagon_nou;
    }
    // marim lungimea trenului
    tren->lungime = tren->lungime + 1;
}

void insertLeft(Tren *tren, char val, FILE *g) {
    if (tren->mecanic->prev == tren->locomotiva) {
        // cazul in care mecanicul este in primul vagon
        fprintf(g, "ERROR\n");
    } else {
        // cazul in care mecanicul nu este in primul vagon
        Vagon *vagon_nou = (Vagon *)malloc(sizeof(Vagon));
        vagon_nou->val = val;
        // conectam vagonul la cei 2 vecini
        vagon_nou->next = tren->mecanic;
        vagon_nou->prev = tren->mecanic->prev;
        // conectam vecinii la noul vagon
        tren->mecanic->prev->next = vagon_nou;
        tren->mecanic->prev = vagon_nou;
        // mutam mecanicul in noul vagon
        tren->mecanic = vagon_nou;
        tren->lungime = tren->lungime + 1;
    }
}

void moveLeft(Tren *tren) {
    if (tren->mecanic->prev == tren->locomotiva) {
        // cazul in care mecanicul este in primul vagon
        // sarim peste santinela
        tren->mecanic = tren->locomotiva->prev;
    } else {
        tren->mecanic = tren->mecanic->prev;
    }
}

void moveRight(Tren *tren) {
    if (tren->mecanic->next == tren->locomotiva) {
        // cazul in care mecanicul este in ultimul vagon
        // apelam insertRight pentru a adauga un nou vagon
        insertRight(tren, '#');
    } else {
        tren->mecanic = tren->mecanic->next;
    }
}

void write(Tren *tren, char val) { tren->mecanic->val = val; }

void clearCell(Tren *tren) {
    Vagon *vagon_eliminat = tren->mecanic;

    if (tren->lungime > 1) {
        // cazul in care vagonul eliminat este primul
        if (vagon_eliminat == tren->locomotiva->next) {
            tren->mecanic = tren->locomotiva->prev;
        } else {
            tren->mecanic = tren->mecanic->prev;
        }
        // conectam vecinii vagonului eliminat
        vagon_eliminat->prev->next = vagon_eliminat->next;
        vagon_eliminat->next->prev = vagon_eliminat->prev;
        // eliberam memoria alocata
        free(vagon_eliminat);
    } else {
        // cazul in care trenul are un singur vagon
        write(tren, '#');
    }

    if (tren->lungime > 1) {
        tren->lungime = tren->lungime - 1;
    }
}

void clearAll(Tren *tren) {
    // pornim de la vagonul 2
    Vagon *vagon_curent = tren->locomotiva->next->next;
    tren->mecanic = tren->locomotiva->next;
    write(tren, '#');

    Vagon *vagon_eliminat;
    while (vagon_curent != tren->locomotiva) {
        vagon_eliminat = vagon_curent;
        vagon_curent = vagon_curent->next;
        free(vagon_eliminat);
    }

    // aducem la starea initiala trenul
    tren->mecanic->next = tren->locomotiva;
    tren->locomotiva->prev = tren->mecanic;
    tren->lungime = 1;
}