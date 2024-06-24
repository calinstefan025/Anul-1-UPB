/*AVRAMONIU Calin-Stefan - 312CC*/
#include "queue.h"

// functie de adaugare la coada
void pushq(Coada *q, char *comanda, char *argument) {
    // alocam memorie pentru o noua comanda
    nodComanda *comanda_noua = (nodComanda *)malloc(sizeof(nodComanda));

    // cazul in care este prima comanda adaugata
    if (q->head == NULL && q->tail == NULL) {
        // copiem comanda si argumentul
        strcpy(comanda_noua->comanda, comanda);
        strcpy(comanda_noua->argument, argument);

        comanda_noua->next = NULL;
        comanda_noua->prev = NULL;
        q->head = comanda_noua;
        q->tail = comanda_noua;
    } else {
        strcpy(comanda_noua->comanda, comanda);
        strcpy(comanda_noua->argument, argument);

        q->tail->next = comanda_noua;
        comanda_noua->next = NULL;
        comanda_noua->prev = q->tail;
        q->tail = comanda_noua;
    }

    // crestem capacitatea cozii
    q->capacitate = q->capacitate + 1;
}

// functie de eliminare a unei comenzi din coada
nodComanda *popq(Coada *q) {
    // eliminam prima comanda din lista
    nodComanda *comanda_exec = q->head;
    q->head = q->head->next;

    if (q->head == NULL) {
        // cazul in care am eliminat ultima comanda
        q->tail = NULL;
    } else {
        // cazul in care mai sunt comenzi in coada
        q->head->prev = NULL;
    }

    // scadem capacitatea cozii
    q->capacitate = q->capacitate - 1;
    return comanda_exec;
}