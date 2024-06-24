/*AVRAMONIU Calin-Stefan - 312CC*/
#include <alloca.h>

#include "query.h"
#include "queue.h"
#include "search.h"
#include "struct.h"
#include "update.h"

int main() {
    // definim si deschidem fisierele de in si out
    FILE *f = fopen("tema1.in", "r");
    FILE *g = fopen("tema1.out", "w");
    // verificam deschiderea corecta
    if (f == NULL || g == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        return 0;
    }

    // Alocare memorie
    Tren *tren = (Tren *)malloc(sizeof(Tren));
    Vagon *locomotiva = (Vagon *)malloc(sizeof(Vagon));
    Vagon *vagon1 = (Vagon *)malloc(sizeof(Vagon));

    // Initializare coada
    Coada *q = (Coada *)malloc(sizeof(Coada));
    q->head = NULL;
    q->tail = NULL;
    q->capacitate = 0;

    // Initializare tren
    locomotiva->prev = vagon1;
    locomotiva->next = vagon1;
    vagon1->next = locomotiva;
    vagon1->prev = locomotiva;
    vagon1->val = '#';
    tren->locomotiva = locomotiva;
    tren->mecanic = vagon1;
    tren->lungime = 1;

    // citim numarul de comenzi
    int nr_comenzi;
    char comanda[105], argument[105];
    fscanf(f, "%d", &nr_comenzi);

    while (nr_comenzi) {
        fscanf(f, "%s", comanda);
        // citim comenzile si le adaugam la coada daca este cazul
        if (strcmp(comanda, "EXECUTE") == 0) {
            nodComanda *comanda_exec = popq(q);
            // cat timp exista comenzi de executat le executam
            // avem >= 0 deoarece altfel nu putem executa ultima comanda
            if (q->capacitate >= 0) {
                // executam comenzile
                if (strcmp(comanda_exec->comanda, "WRITE") == 0) {
                    write(tren, comanda_exec->argument[0]);
                } else if (strcmp(comanda_exec->comanda, "INSERT_RIGHT") == 0) {
                    insertRight(tren, comanda_exec->argument[0]);
                } else if (strcmp(comanda_exec->comanda, "INSERT_LEFT") == 0) {
                    insertLeft(tren, comanda_exec->argument[0], g);
                } else if (strcmp(comanda_exec->comanda, "MOVE_LEFT") == 0) {
                    moveLeft(tren);
                } else if (strcmp(comanda_exec->comanda, "MOVE_RIGHT") == 0) {
                    moveRight(tren);
                } else if (strcmp(comanda_exec->comanda, "CLEAR_CELL") == 0) {
                    clearCell(tren);
                } else if (strcmp(comanda_exec->comanda, "CLEAR_ALL") == 0) {
                    clearAll(tren);
                } else if (strcmp(comanda_exec->comanda, "SEARCH") == 0) {
                    search(tren, comanda_exec->argument, g);
                } else if (strcmp(comanda_exec->comanda, "SEARCH_RIGHT") == 0) {
                    searchRight(tren, comanda_exec->argument, g);
                } else if (strcmp(comanda_exec->comanda, "SEARCH_LEFT") == 0) {
                    searchLeft(tren, comanda_exec->argument, g);
                }
            } else {
                printf("NU EXISTA COMENZI DE EXECUTAT\n");
            }
            // eliberam memoria comenzii executate
            free(comanda_exec);
        } else if (strcmp(comanda, "SWITCH") == 0) {
            switchq(q);
        } else if (strcmp(comanda, "WRITE") == 0) {
            // in cazul in care comanda are si un argument
            // vom citi si argumentul
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        } else if (strcmp(comanda, "SHOW") == 0) {
            show(tren, g);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            showCurrent(tren, g);
        } else if (strcmp(comanda, "INSERT_RIGHT") == 0) {
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        } else if (strcmp(comanda, "INSERT_LEFT") == 0) {
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        } else if (strcmp(comanda, "MOVE_LEFT") == 0) {
            pushq(q, comanda, "NULL");
        } else if (strcmp(comanda, "MOVE_RIGHT") == 0) {
            pushq(q, comanda, "NULL");
        } else if (strcmp(comanda, "CLEAR_CELL") == 0) {
            pushq(q, comanda, "NULL");
        } else if (strcmp(comanda, "CLEAR_ALL") == 0) {
            pushq(q, comanda, "NULL");
        } else if (strcmp(comanda, "SEARCH") == 0) {
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        } else if (strcmp(comanda, "SEARCH_RIGHT") == 0) {
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        } else if (strcmp(comanda, "SEARCH_LEFT") == 0) {
            fscanf(f, "%s", argument);
            pushq(q, comanda, argument);
        }

        nr_comenzi--;
    }

    // inchidem fisierele
    fclose(f);
    fclose(g);

    // eliberam memoria
    clearAll(tren);
    free(tren->locomotiva);
    free(tren->mecanic);
    free(tren);

    // eliberam memoria in cazul in care raman comenzi neexecutate
    if (q->capacitate > 0) {
        nodComanda *comanda_exec = popq(q);
        free(comanda_exec);
    }

    free(q);

    return 0;
}