#include <alloca.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura unei carti din biblioteca
// alocarea (la titlu si autor) este mai mare decat in enunt pentru ca exista
// teste care depasesc limitele furnizate
typedef struct {
  int id, an;
  char titlu[61], autor[41];
  char *descriere;
} Carte;

// functie care verifica daca un sir de caractere este numar
int is_num(char *element) {
  int i;
  for (i = 0; element[i] != '\0'; i++) {
    if (isdigit(element[i]) == 0)
      return 0;
  }
  return 1;
}

// functie care returneaza sirul dat cu litere mici
char *lowercase(char arg[]) {
  int i;
  char *aux = (char *)malloc((strlen(arg) + 1) * sizeof(char));

  for (i = 0; arg[i] != '\0'; i++) {
    if (arg[i] != ' ') {
      aux[i] = tolower(arg[i]);
    } else {
      aux[i] = arg[i];
    }
  }
  aux[i] = '\0';
  return aux;
}

// functie de swap intre 2 variabile
void swap_val(int *val1, int *val2) {
  int aux = *val1;
  *val1 = *val2;
  *val2 = aux;
}

// functie de sortare pentru vectorul de id-uri
void sortare(int *v_id, int n) {
  // se foloseste algoritmul bubble sort
  int i, j, swap;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      swap = 0;
      if (v_id[j] > v_id[j + 1]) {
        swap_val(&v_id[j], &v_id[j + 1]);
        swap = 1;
      }
      if (swap == 0)
        break;
    }
  }
}

// functia add_book pe care o folosim atat la citirea initala cat si la
// intalnirea comenzii ADD_BOOK
void add_book(int index, Carte(**carti)) {
  // citim id-ul
  scanf("%d\n", &(*carti)[index].id);
  fflush(stdin);

  // citim titlul
  fgets((*carti)[index].titlu, 61, stdin);
  fflush(stdin);
  // eliminam '\n' de la finalul sirului
  if ((*carti)[index].titlu[strlen((*carti)[index].titlu) - 1] == '\n') {
    (*carti)[index].titlu[strlen((*carti)[index].titlu) - 1] = '\0';
  }

  // citim autorul
  fgets((*carti)[index].autor, 41, stdin);
  fflush(stdin);
  if ((*carti)[index].autor[strlen((*carti)[index].autor) - 1] == '\n') {
    (*carti)[index].autor[strlen((*carti)[index].autor) - 1] = '\0';
  }

  // citim anul
  scanf("%d\n", &(*carti)[index].an);
  fflush(stdin);

  // alocam dinamic 500 sirului de caractere descriere
  (*carti)[index].descriere = (char *)malloc(501 * sizeof(char));
  // citim descrierea
  fgets((*carti)[index].descriere, 501, stdin);
  fflush(stdin);
  // eliminam '\n' de la finalul descrierii
  if ((*carti)[index].descriere[strlen((*carti)[index].descriere) - 1] == '\n') {
    (*carti)[index].descriere[strlen((*carti)[index].descriere) - 1] = '\0';
  }
  // realocam memoria pentru a salva spatiu
  (*carti)[index].descriere =
      (char *)realloc((*carti)[index].descriere,
                      (strlen((*carti)[index].descriere) + 1) * sizeof(char));
}

// functie de afisare a unei carti
void afisare_carte(int index, Carte *carti) {
  printf("%d\n", carti[index].id);
  fflush(stdout);
  puts(carti[index].titlu);
  fflush(stdout);
  puts(carti[index].autor);
  fflush(stdout);
  printf("%d\n", carti[index].an);
  fflush(stdout);
  puts(carti[index].descriere);
  fflush(stdout);
}

// functie de afisare a intregii biblioteci
void afisare_biblioteca(int numar_carti, Carte *carti) {
  int i;
  printf("%d\n", numar_carti);
  for (i = 0; i < numar_carti; i++) {
    // apelam functia de afisare a cartii cu indexul i
    afisare_carte(i, carti);
  }
}

// functia de search in cazul in care stringul este numar
int search_year(int numar_carti, char *element, Carte *carti, int *v_id) {
  int an = atoi(element), i, poz = 0;

  for (i = 0; i < numar_carti; i++) {
    if (carti[i].an == an) {
      // adaugam id-urile la vector
      v_id[poz++] = carti[i].id;
    }
  }
  // returnam cate carti am gasit
  return poz;
}

// functia de search pentru titlu si autor
int search_string(int numar_carti, char *element, Carte *carti, int *v_id) {
  int i, poz = 0;
  // folosim functia lowercase sa verificam daca titlu sau autor == element
  // (case insensitive)
  for (i = 0; i < numar_carti; i++) {
    if (strcmp(lowercase(element), lowercase(carti[i].titlu)) == 0 ||
        strcmp(lowercase(element), lowercase(carti[i].autor)) == 0) {
      // adaugam id-urile la vector
      v_id[poz++] = carti[i].id;
    }
  }
  // returnam cate carti am gasit
  return poz;
}

// afisam cartile din vectorul v_id rezultat dupa SEARCH
void afisare_search(int *v_id, Carte *carti, int n, int numar_carti) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < numar_carti; j++) {
      if (v_id[i] == carti[j].id) {
        afisare_carte(j, carti);
        printf("\n");
      }
    }
  }
}

// functia de replace
void replace_word(int numar_carti, char *word1, char *word2, Carte(**carti)) {
  int i;
  char aux[501], aux2[501], *p;

  for (i = 0; i < numar_carti; i++) {
    // realocam memoria pt a acomoda cuvantul nou
    // folosim auxiliari pt a desface propozitia si a inlocui cuvantul
    (*carti)[i].descriere =
        (char *)realloc((*carti)[i].descriere, 501 * sizeof(char));
    // copiem descrierea in aux pentru prelucrare
    strcpy(aux, (*carti)[i].descriere);
    // folosim aux2 pentru a construi noul sir
    strcpy(aux2, "");

    // desfacem sirul aux in cuvinte
    p = strtok(aux, " ");
    while (p) {
      // inlocuim cuvantul word1 cu word2 in sirul aux2
      if (strcmp(p, word1) == 0) {
        strcat(aux2, word2);
        strcat(aux2, " ");
      } else {
        strcat(aux2, p);
        strcat(aux2, " ");
      }
      // trecem la urmatorul cuvant
      p = strtok(NULL, " ");
    }
    // scapam de spatiul adaugat la finalul sirului
    aux2[strlen(aux2) - 1] = '\0';
    // copiem si realocam memoria pentru descriere
    strcpy((*carti)[i].descriere, aux2);
    (*carti)[i].descriere =
        (char *)realloc((*carti)[i].descriere,
                        (strlen((*carti)[i].descriere) + 1) * sizeof(char));
  }
}

// functia de encode
void encode(int index, Carte **carti) {
  // folosim num pentru a stoca numarul de aparitii ca sir
  // folosim aux pentru a construi descrierea encodata
  // folosim rez pentru a inversa sirul aux
  char num[501], aux[501], rez[501], copie;
  strcpy(aux, "");

  int len = strlen((*carti)[index].descriere), i, j, k = 0, cnt = 1, len_num, l;
  for (i = 0; i < len; i++) {
    // daca nu este cifra sau spatiu numaram cate aparitii consecutive are
    // in cuvant
    copie = (*carti)[index].descriere[i];
    if ((copie >= 'A' && copie <= 'Z') || (copie >= 'a' && copie <= 'z')) {
      cnt = 1;
      j = i + 1;
      // parcurgem aparitiile pana dam de un caracter diferit
      while ((*carti)[index].descriere[j] == (*carti)[index].descriere[i]) {
        cnt++;
        j++;
      }
      i = j - 1;
      // adaugam caracterul in aux
      aux[k++] = (*carti)[index].descriere[i];
      // transformam (numar de aparitii -> baza 16 -> sir)
      sprintf(num, "%X", cnt);
      // adaugam sirul cu numarul de aparitii al caracterului in auxiliar
      len_num = strlen(num);
      for (l = 0; l < len_num; l++) {
        aux[k++] = num[l];
      }
    } else {
      // daca e spatiu sau cifra se adauga la auxiliar
      aux[k++] = (*carti)[index].descriere[i];
    }
  }
  // terminam sirul auxiliar dupa encodarea initiala
  aux[k] = '\0';
  // inversarea auxiliarului in sirul rez
  for (l = 0; l < (int)strlen(aux); l++) {
    rez[l] = aux[k - l - 1];
  }
  rez[strlen(aux)] = '\0';
  // realocarea memoriei pentru a pune noua descriere
  (*carti)[index].descriere = (char *)realloc((*carti)[index].descriere,
                                              (strlen(aux) + 1) * sizeof(char));
  strcpy((*carti)[index].descriere, rez);
}

int main() {
  // variabile necesare
  int numar_carti, numar_comenzi, i, id, carte, *v_id, len_id;
  // siruri de caractere folosite la citirea comenzilor
  char comanda[20], word1[100], word2[100], element[100];

  // folosim fflush dupa fiecare citire pentru a elibera bufferul
  scanf("%d\n", &numar_carti);
  fflush(stdin);
  // alocare dinamica a vectorului de carti
  Carte *carti = (Carte *)malloc((numar_carti) * sizeof(Carte));

  // citirea cartilor folosind functia add_book
  for (i = 0; i < numar_carti; i++) {
    add_book(i, &carti);
  }

  // citirea comenzilor
  scanf("%d\n", &numar_comenzi);
  fflush(stdin);
  for (i = 0; i < numar_comenzi; i++) {
    scanf("%s ", comanda);
    fflush(stdin);
    if (strcmp(comanda, "SEARCH") == 0) {
      // citim argumentul comenzii
      fgets(element, sizeof(element), stdin);
      fflush(stdin);
      if (element[strlen(element) - 1] == '\n') {
        element[strlen(element) - 1] = '\0';
      }
      // alocam dinamic un vector de id-uri
      v_id = (int *)malloc((numar_carti + 1) * sizeof(int));
      if (is_num(element) == 1) {
        // daca este numar apelam functia de search dupa an care
        // adauga in vector id-urile cartilor gasite si returneaza numarul de
        // carti gasite
        len_id = search_year(numar_carti, element, carti, v_id);
        v_id = (int *)realloc(v_id, (len_id + 1) * sizeof(int));
      } else {
        // daca este sir apelam functia de search dupa titlu sau autor
        len_id = search_string(numar_carti, element, carti, v_id);
        v_id = (int *)realloc(v_id, (len_id + 1) * sizeof(int));
      }
      if (len_id == 0) {
        printf("NOT FOUND\n\n");
      } else {
        sortare(v_id, len_id);
        afisare_search(v_id, carti, len_id, numar_carti);
        free(v_id);
      }
    } else if (strcmp(comanda, "REPLACE") == 0) {
      scanf("%s", word1);
      fflush(stdin);
      scanf("%s", word2);
      fflush(stdin);
      // inlocuim cuvintele din comanda
      replace_word(numar_carti, word1, word2, &carti);
    } else if (strcmp(comanda, "ENCODE") == 0) {
      scanf("%d", &id);
      fflush(stdin);
      // verificam daca exista o carte cu id-ul din comanda si o encodam
      for (carte = 0; carte < numar_carti; carte++) {
        if (carti[carte].id == id)
          encode(carte, &carti);
      }
    } else if (strcmp(comanda, "ADD_BOOK") == 0) {
      numar_carti++;
      // realocarea memoriei pentru a adauga o noua carte
      carti = (Carte *)realloc(carti, (numar_carti) * sizeof(Carte));
      add_book(numar_carti - 1, &carti);
    }
  }

  // afisarea bibliotecii dupa executarea comenzilor
  afisare_biblioteca(numar_carti, carti);
  free(carti);
  // eliberarea memoriei alocate

  return 0;
}
