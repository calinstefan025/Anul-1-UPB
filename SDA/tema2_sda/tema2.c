// AVRAMONIU Calin-Stefan - 312CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    // string folosit doar la cerinta 4
    char c4_val[100];
    // caracter folosit la cerintele 1,2,3
    char val;
    struct node *children[27];
} Node, *Tree;

void add_sufix(Tree parinte, char *sufix) {
    int i;
    if (sufix[0] == '\0') {
        return;
    }
    // vedem pozitia in alfabet a literei de pe prima pozitie
    int poz = sufix[0] - 'a' + 1;
    // in caz ca dam de caracterul '$' il punem pe pozitia 0
    if (poz < 0) poz = 0;
    // nu exista sufix in arbore care sa inceapa cu prima litera din sufix
    if (parinte->children[poz] == NULL) {
        Node *nod_nou = (Node *)malloc(sizeof(Node));
        nod_nou->val = sufix[0];
        for (i = 0; i < 27; i++) {
            nod_nou->children[i] = NULL;
        }
        parinte->children[poz] = nod_nou;
        parinte = nod_nou;
        add_sufix(parinte, sufix + 1);
        return;
    } else {
        // daca exista suprapunere intre arbore si sufix ne deplasam
        // pana nu mai exista aceasta suprapunere si adaugam acolo
        // partea sufixului care nu se suprapune
        add_sufix(parinte->children[poz], sufix + 1);
        return;
    }
}

void construire_arbore(Tree tree, Node *root, FILE *f, int n, char *cuvant,
                       char mat_suf[100][100]) {
    int i, j, lungime;
    for (i = 0; i < n; i++) {
        fscanf(f, "%s", cuvant);
        strcat(cuvant, "$");
        lungime = strlen(cuvant);

        // construim matricea de sufixe
        for (j = 0; j < lungime; j++) {
            strcpy(mat_suf[j], cuvant + lungime - j - 1);
        }

        // adaugam sufixele in arbore
        for (j = 0; j < lungime; j++) {
            add_sufix(tree, mat_suf[j]);
            tree = root;
        }
    }
}

void bfs(Tree root, FILE *g, int cerinta) {
    if (root == NULL) {
        return;
    }
    // simulam coada cu un vector de noduri
    Node *q[1000];
    int first = 0, last = 0, ultim_nod_pe_nivel, i;
    for (i = 0; i < 27; i++) {
        // adaugam in coada toti fiii valizi
        if (root->children[i] != NULL) {
            q[last++] = root->children[i];
        }
    }
    ultim_nod_pe_nivel = last;
    // cat timp mai avem noduri in coada
    while (first < last) {
        // pop la primul nod
        Node *nod_curent = q[first++];
        if (cerinta == 1) {
            // afisam valoarea nodului
            fprintf(g, "%c ", nod_curent->val);
        } else {
            // afisam stringul c4_val
            fprintf(g, "%s ", nod_curent->c4_val);
        }
        // adaugam in coada toti fiii nodului popat
        for (i = 0; i < 27; i++) {
            if (nod_curent->children[i] != NULL) {
                q[last++] = nod_curent->children[i];
            }
        }
        // daca am ajuns la finalul nivelului afisam un \n
        if (first == ultim_nod_pe_nivel) {
            fprintf(g, "\n");
            ultim_nod_pe_nivel = last;
        }
    }
}

void verif_statistici_dfs(Tree root, FILE *g, int *nr_frunze, int K,
                          int *nr_suf_k, int *nr_max_desc, int lungime_sufix) {
    int descendenti = 0, i;

    if (root->val == '$') {
        // daca se intalneste $ crestem nr de frunze
        // doar $ este frunza
        (*nr_frunze)++;
        // verificam lungimea sufixului cu $
        if (lungime_sufix == K + 1) {
            (*nr_suf_k)++;
        }
    }

    for (i = 0; i < 27; i++) {
        if (root->children[i] != NULL) {
            descendenti++;
            lungime_sufix++;
            // parcurgem in adancime si marim lungimea sufixului
            verif_statistici_dfs(root->children[i], g, nr_frunze, K, nr_suf_k,
                                 nr_max_desc, lungime_sufix);
            lungime_sufix--;
            // updatam numarul maxim de descendenti directi
            if (descendenti > *nr_max_desc) {
                *nr_max_desc = descendenti;
            }
        }
    }
}

int cautare_sufix_dfs(Tree root, char *cuvant) {
    int i;
    // daca se ajunge la finalul cuvantului
    // inseamna ca sufixul se suprapune cu arborele
    // deci a fost gasit
    if (cuvant[0] == '\0') {
        return 1;
    }
    // parcurgem in adancime arborele daca gasim un fiu valid
    for (i = 0; i < 27; i++) {
        if (root->children[i] != NULL) {
            // verificam daca fiul curent are valoarea primului char din cuvant
            if (root->children[i]->val == cuvant[0]) {
                // copilul devine parinte si continuam cautarea
                // pointerul cuvantului va pointa la urmatorul char
                return cautare_sufix_dfs(root->children[i], cuvant + 1);
            }
        }
    }

    return 0;
}

void c4_merge(Tree root) {
    int fii = 0, poz = 0, i, j;

    // cand dam de o frunza ne oprim
    if (root->val == '$') {
        return;
    }

    // mergem in adancime pana la penultimul nivel
    for (i = 0; i < 27; i++) {
        if (root->children[i] != NULL) {
            c4_merge(root->children[i]);
        }
    }

    // numaram fiii nodului curent
    // salvam pozitia fiului in caz ca este unul singur
    for (i = 0; i < 27; i++) {
        if (root->children[i] != NULL) {
            fii++;
            poz = i;
        }
    }

    // daca e un singur fiu dam merge la noduri
    if (fii == 1) {
        if (root->children[poz]->val != '$') {
            strcat(root->c4_val, root->children[poz]->c4_val);
        }

        for (j = 0; j < 27; j++) {
            if (root->children[poz]->children[j] != NULL) {
                root->children[poz] = root->children[poz]->children[j];
                // eliminam copilul
                root->children[poz]->children[j] = NULL;
            }
        }
    }
}

// copiaza charul din nod in stringul c4_val
// are rolul de a pregati arborele pt cerinta 4
void completare_string_c4(Tree root) {
    int i;
    for (i = 0; i < 27; i++) {
        if (root->children[i] != NULL) {
            root->children[i]->c4_val[0] = root->children[i]->val;
            completare_string_c4(root->children[i]);
        }
    }
}

// functie de eliberare a memoriei in arbore
void freeTree(Tree tree) {
    int i;
    if (tree == NULL) {
        return;
    }
    for (i = 0; i < 27; i++) {
        if (tree->children[i] != NULL) {
            freeTree(tree->children[i]);
        }
    }
    free(tree);
}

int main(int argc, char *argv[]) {
    // scapam de warning pt unused variable
    (void)argc;

    int K, n, m, cerinta, i, nr_frunze = 0, nr_suf_k = 0, nr_max_desc = 0,
                             lungime_sufix = 0;
    // prelucrare argumente
    char c1234[4], fisier_in[100], fisier_out[100], cuvant[100],
        mat_suf[100][100];
    strcpy(c1234, argv[1]);

    // transformam cerinta din string in int
    // si initializam argumentele corespunzator cerintei

    if (c1234[strlen(c1234) - 1] == '2') {
        K = atoi(argv[2]);
        strcpy(fisier_in, argv[3]);
        strcpy(fisier_out, argv[4]);
    } else {
        strcpy(fisier_in, argv[2]);
        strcpy(fisier_out, argv[3]);
    }
    cerinta = c1234[strlen(c1234) - 1] - '0';

    // deschidere fisiere
    FILE *f = fopen(fisier_in, "r");
    FILE *g = fopen(fisier_out, "w");
    if (f == NULL || g == NULL) {
        printf("Eroare la deschiderea fisierelor\n");
        return 0;
    }

    // initializare arbore
    Node *root = (Node *)malloc(sizeof(Node));
    for (i = 0; i < 27; i++) {
        root->children[i] = NULL;
    }
    Tree tree = root;

    // citire si prelucrare date
    if (cerinta == 1) {
        fscanf(f, "%d", &n);
        construire_arbore(tree, root, f, n, cuvant, mat_suf);

        bfs(root, g, cerinta);
    } else if (cerinta == 2) {
        fscanf(f, "%d", &n);
        construire_arbore(tree, root, f, n, cuvant, mat_suf);

        verif_statistici_dfs(root, g, &nr_frunze, K, &nr_suf_k, &nr_max_desc,
                             lungime_sufix);
        fprintf(g, "%d\n", nr_frunze);
        fprintf(g, "%d\n", nr_suf_k);
        fprintf(g, "%d\n", nr_max_desc);
    } else if (cerinta == 3) {
        fscanf(f, "%d", &n);
        fscanf(f, "%d", &m);
        construire_arbore(tree, root, f, n, cuvant, mat_suf);
        for (i = 0; i < m; i++) {
            // cuvant este sufixul cautat in arbore
            fscanf(f, "%s", cuvant);
            strcat(cuvant, "$");

            // cautam sufixul in arbore
            if (cautare_sufix_dfs(root, cuvant)) {
                fprintf(g, "%d\n", 1);
            } else {
                fprintf(g, "%d\n", 0);
            }
        }

    } else if (cerinta == 4) {
        fscanf(f, "%d", &n);
        construire_arbore(tree, root, f, n, cuvant, mat_suf);
        completare_string_c4(root);
        c4_merge(root);
        bfs(root, g, cerinta);
    }

    // inchidere fisiere
    fclose(f);
    fclose(g);

    // eliberare memorie
    freeTree(tree);
    return 0;
}