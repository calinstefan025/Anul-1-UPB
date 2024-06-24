// Avramoniu Calin-Stefan 312CC
#include "cerinta1.h"

int main(int argc, char *argv[]) {
    (void)argc;

    // aflam cerinta data ca argument
    int cerinta = argv[1][0] - '0';

    // initializare variabile
    int nr_rute, k, grad_uzura_acceptat, i, j, tronson, nr_tronsoane, id_maxim,
        id1, id2;
    char oras1[100], oras2[100];
    float uzura[1000], uzura_veche, uzura_veche_2;
    // vector care retine uzura maxima a segmentelor vecine unui oras
    float segment_maxim_vecin[1000];

    // deschidere fisiere
    FILE *f = fopen("tema3.in", "r");
    FILE *g = fopen("tema3.out", "w");
    if (f == NULL || g == NULL) {
        printf("Eroare la deschiderea fisierelor\n");
        return 0;
    }

    // lista de adiacenta
    Oras *lista_orase[1000];
    // matrice de stringuri care retine numele oraselor
    char nume_orase[1000][100];

    // initializare lista de orase
    for (i = 0; i < 1000; i++) {
        lista_orase[i] = NULL;
    }

    if (cerinta == 1) {
        fscanf(f, "%d", &nr_rute);
        fscanf(f, "%d", &k);
        fscanf(f, "%d", &grad_uzura_acceptat);

        id_maxim = 0;
        for (i = 0; i < nr_rute; i++) {
            // citim numele oraselor si daca nu au deja id
            // le adaugam in matricea de cuvinte
            fscanf(f, "%s", oras1);
            id1 = verif_exist(oras1, nume_orase, &id_maxim);
            fscanf(f, "%s", oras2);
            id2 = verif_exist(oras2, nume_orase, &id_maxim);

            // citim tronsoanele de la oras1 la oras2
            fscanf(f, "%d", &nr_tronsoane);
            for (j = 0; j < nr_tronsoane; j++) {
                fscanf(f, "%f", &uzura[j]);
            }

            // adaugam datele despre fiecare ruta in lista de adiacenta
            adauga_oras(&lista_orase[id1], id2, uzura, nr_tronsoane, i);
        }

        for (i = 0; i < k; i++) {
            // initializam vecorul cu 0
            for (j = 0; j < id_maxim; j++) {
                segment_maxim_vecin[j] = 0;
            }

            // pentru fiecare oras calculam uzura maxima a segmentelor vecine
            for (j = 0; j < id_maxim; j++) {
                Oras *oras_aux = lista_orase[j];
                while (oras_aux != NULL) {
                    segment_maxim_vecin[j] =
                        max(segment_maxim_vecin[j], oras_aux->uzura[0]);
                    segment_maxim_vecin[oras_aux->id] =
                        max(segment_maxim_vecin[oras_aux->id],
                            oras_aux->uzura[oras_aux->nr_tronsoane - 1]);
                    oras_aux = oras_aux->next;
                }
            }

            for (j = 0; j < id_maxim; j++) {
                Oras *oras_aux = lista_orase[j];
                while (oras_aux != NULL) {
                    // salvam uzura veche a primului tronson
                    uzura_veche = oras_aux->uzura[0];
                    uzura_veche_2 = 0;

                    // daca uzura primului tronson este 0
                    if (oras_aux->uzura[0] == 0) {
                        oras_aux->uzura[0] =
                            max(segment_maxim_vecin[j], oras_aux->uzura[1]) / 2;
                    } else {
                        oras_aux->uzura[0] = 2 * oras_aux->uzura[0];
                    }

                    // calculam uzura pentru fiecare tronson
                    for (tronson = 1; tronson <= oras_aux->nr_tronsoane - 2;
                         tronson++) {
                        uzura_veche_2 = oras_aux->uzura[tronson];
                        if (oras_aux->uzura[tronson] == 0) {
                            oras_aux->uzura[tronson] =
                                max(uzura_veche, oras_aux->uzura[tronson + 1]) /
                                2;
                        } else {
                            oras_aux->uzura[tronson] =
                                2 * oras_aux->uzura[tronson];
                        }
                        uzura_veche = uzura_veche_2;
                    }

                    // daca uzura ultimului tronson este 0
                    if (oras_aux->uzura[oras_aux->nr_tronsoane - 1] == 0) {
                        oras_aux->uzura[oras_aux->nr_tronsoane - 1] =
                            max(uzura_veche,
                                segment_maxim_vecin[oras_aux->id]) /
                            2;
                    } else if (oras_aux->nr_tronsoane != 1) {
                        oras_aux->uzura[oras_aux->nr_tronsoane - 1] =
                            2 * oras_aux->uzura[oras_aux->nr_tronsoane - 1];
                    }
                    oras_aux = oras_aux->next;
                }
            }
        }

        // facem uzurile mar mari decat 100 egale cu 100
        for (i = 0; i < id_maxim; i++) {
            Oras *oras_aux = lista_orase[i];
            while (oras_aux != NULL) {
                for (j = 0; j < oras_aux->nr_tronsoane; j++) {
                    if (oras_aux->uzura[j] > 100) {
                        oras_aux->uzura[j] = 100;
                    }
                }
                oras_aux = oras_aux->next;
            }
        }

        // calculam uzura medie a fiecarei rute
        calculare_uzura_medie(lista_orase, id_maxim);

        // afisam rutele
        afisare(id_maxim, lista_orase, nume_orase, nr_rute, grad_uzura_acceptat,
                g);
    }

    // eliberam memoria
    for (i = 0; i < 1000; i++) {
        Oras *oras_aux = lista_orase[i];
        while (oras_aux != NULL) {
            Oras *oras_aux2 = oras_aux;
            oras_aux = oras_aux->next;
            free(oras_aux2);
        }
    }

    // inchidere fisiere
    fclose(f);
    fclose(g);

    return 0;
}