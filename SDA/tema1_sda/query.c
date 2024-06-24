/*AVRAMONIU Calin-Stefan - 312CC*/
#include "query.h"

void show(Tren *tren, FILE *g) {
    // pornim parcurgerea de la primul vagon
    Vagon *vagon_curent = tren->locomotiva->next;
    // mergem pana la intalnirea santinelei
    while (vagon_curent != tren->locomotiva) {
        if (tren->mecanic == vagon_curent) {
            fprintf(g, "|");
            fprintf(g, "%c", vagon_curent->val);
            fprintf(g, "|");
        } else {
            fprintf(g, "%c", vagon_curent->val);
        }
        vagon_curent = vagon_curent->next;
    }
    fprintf(g, "\n");
}

void showCurrent(Tren *tren, FILE *g) {
    fprintf(g, "%c\n", tren->mecanic->val);
}

void switchq(Coada *q) {
    // pornim pargurgerea de la primul element
    nodComanda *nod_curent = q->head;
    nodComanda *aux = NULL;

    // cazul in care este doar un element sau niciunul
    if (q->head == NULL || q->head == q->tail || q->tail == NULL) {
        return;
    }

    while (nod_curent != NULL) {
        // interschimbam pointerii cu un auxiliar
        aux = nod_curent->next;
        nod_curent->next = nod_curent->prev;
        nod_curent->prev = aux;

        // mergem la nodul urmator
        // folosim prev pt ca sunt inversati pointerii
        // in acest caz prev = next
        nod_curent = nod_curent->prev;
    }

    // inversam head cu tail
    aux = q->head;
    q->head = q->tail;
    q->tail = aux;
}