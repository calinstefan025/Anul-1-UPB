#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura unui jucator castigator
struct Winner {
  int index, scor;
};

// functie care colorează o anumită celulă de pe card dacă aceasta contine
// valoarea indicata
void colorare(int valoare, int numar_jucatori, int color[][5][5]) {
  int jucator, i, j;
  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 5; j++) {
        if (color[jucator][i][j] == valoare) {
          // coloram elementul cu -1
          color[jucator][i][j] = -1;
        }
      }
    }
  }
}

// functie care face schimb intre valorile a doua variabile
void swap_val(int *val1, int *val2) {
  int aux = *val1;
  *val1 = *val2;
  *val2 = aux;
}

//  functie care sortează crescător numerele de pe coloana introdusa
void sort_cresc(int col, int numar_jucatori, int bingo[][5][5],
                int color[][5][5]) {
  int jucator, i, j, swap;

  // se va folosi algoritmul bubble sort
  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    for (i = 0; i < 4; i++) {
      swap = 0;
      for (j = 0; j < 4 - i; j++) {
        if (bingo[jucator][j][col] > bingo[jucator][j + 1][col]) {
          // facem schimbarile atat in cardul jucatorului cat si in
          // copia colorata
          swap_val(&bingo[jucator][j][col], &bingo[jucator][j + 1][col]);
          swap_val(&color[jucator][j][col], &color[jucator][j + 1][col]);
          swap = 1;
        }
      }
      if (swap == 0)
        break;
    }
  }
}

//  functie care sortează descrescător numerele de pe coloana introdusa
void sort_desc(int col, int numar_jucatori, int bingo[][5][5],
               int color[][5][5]) {
  int jucator, i, j, swap;

  // se va folosi algoritmul bubble sort
  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    for (i = 0; i < 4; i++) {
      swap = 0;
      for (j = 0; j < 4 - i; j++) {
        if (bingo[jucator][j][col] < bingo[jucator][j + 1][col]) {
          // facem schimbarile atat in cardul jucatorului cat si in
          // copia colorata
          swap_val(&bingo[jucator][j][col], &bingo[jucator][j + 1][col]);
          swap_val(&color[jucator][j][col], &color[jucator][j + 1][col]);
          swap = 1;
        }
      }
      if (swap == 0)
        break;
    }
  }
}

// functie care interschimba coloanele col1 si col2
void swap_col(int col1, int col2, int numar_jucatori, int bingo[][5][5],
              int color[][5][5]) {
  int jucator, i;

  // interschimbam coloanele doar daca difera indexurile acestora
  if (col1 != col2) {
    for (jucator = 0; jucator < numar_jucatori; jucator++) {
      for (i = 0; i < 5; i++) {
        // facem schimbarile atat in cardul jucatorului cat si in copia
        // colorata
        swap_val(&bingo[jucator][i][col1], &bingo[jucator][i][col2]);
        swap_val(&color[jucator][i][col1], &color[jucator][i][col2]);
      }
    }
  }
}

// fucntie care shifteaza coloana X cu Y pozitii
void shift_col(int col, int nr_shiftari, int numar_jucatori, int bingo[][5][5],
               int color[][5][5]) {
  int jucator, i, k, ult_el1, ult_el2;

  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    // folosim %5 la numarul de shiftari pentru a reduce pasii inutili
    for (k = 0; k < nr_shiftari % 5; k++) {
      // pastram ultimele elemente din matrici inainte de shiftare
      ult_el1 = bingo[jucator][4][col];
      ult_el2 = color[jucator][4][col];
      // un ciclu de shiftare
      for (i = 4; i >= 1; i--) {
        // interschimbam atat in card cat si in copia colorata
        swap_val(&bingo[jucator][i][col], &bingo[jucator][i - 1][col]);
        swap_val(&color[jucator][i][col], &color[jucator][i - 1][col]);
      }
      // copiem in primul element pe ultimul salvat anterior
      bingo[jucator][0][col] = ult_el1;
      color[jucator][0][col] = ult_el2;
    }
  }
}

// functie care afiseaza cardul unui jucator
void show_card(int jucator, int color[][5][5]) {
  int i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      // inlocuim -1 cu # la afisarea copiei colorate
      if (color[jucator][i][j] != -1) {
        printf("%d ", color[jucator][i][j]);
      } else {
        printf("# ");
      }
    }
    printf("\n");
  }
}

// facem multiple functii de verificare pentru linii , coloane si diagonale care
// returneaza scorul unui jucator
int verif_lin(int index_jucator, int color[][5][5]) {
  int scor = 0, counter_colorari = 0, i, j;
  // verificam cate linii sunt colorate complet
  for (i = 0; i < 5; i++) {
    counter_colorari = 0;
    for (j = 0; j < 5; j++) {
      if (color[index_jucator][i][j] == -1)
        counter_colorari++;
    }
    // daca sunt colorate 5 elemente pe linie se mareste scorul cu 10
    if (counter_colorari == 5)
      scor += 10;
  }
  return scor;
}

int verif_col(int index_jucator, int color[][5][5]) {
  int scor = 0, counter_colorari = 0, i, j;
  // verificam cate coloane sunt colorate complet
  for (i = 0; i < 5; i++) {
    counter_colorari = 0;
    for (j = 0; j < 5; j++) {
      if (color[index_jucator][j][i] == -1)
        counter_colorari++;
    }
    // daca sunt colorate 5 elemente pe coloana se mareste scorul cu 10
    if (counter_colorari == 5)
      scor += 10;
  }
  return scor;
}

int verif_diag(int index_jucator, int color[][5][5]) {
  int scor = 0, counter_colorari = 0, i;
  // verificam diagonala principala
  for (i = 0; i < 5; i++) {
    if (color[index_jucator][i][i] == -1)
      counter_colorari++;
  }
  if (counter_colorari == 5)
    scor += 10;

  // verificam diagonala secundara
  counter_colorari = 0;
  for (i = 0; i < 5; i++) {
    if (color[index_jucator][i][4 - i] == -1)
      counter_colorari++;
  }
  if (counter_colorari == 5)
    scor += 10;

  return scor;
}

// functie care verifică dacă un card contine o combinatie finală
struct Winner verificare(int numar_jucatori, int color[][5][5]) {
  // j_win = indexul jucatorului castigator
  int jucator, scor = 0, scor_max, j_win;
  struct Winner output;

  // outputul standard in cazul in care nu se gaseste castigator
  output.index = -1;
  output.scor = 0;

  // verificare indeplinire conditii pentru fiecare jucator
  scor_max = 0;
  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    scor = 0;

    // verificam liniile , coloanele si diagonalele
    scor += verif_lin(jucator, color);
    scor += verif_col(jucator, color);
    scor += verif_diag(jucator, color);

    // se gaseste un castigator
    if (scor != 0) {
      // alegem jucatorul castigator cu scorul maxim
      if (scor > scor_max) {
        scor_max = scor;
        j_win = jucator;
      }
    }
  }

  // daca exista castigator acesta devine outputul functiei
  if (scor_max != 0) {
    output.index = j_win;
    output.scor = scor_max;
  }

  return output;
}

int main() {
  // matricea bingo si matricea secundara unde reprezentam '# = -1'
  int bingo[1001][5][5], color[1001][5][5];
  // variabile necesare
  int jucator, i, j, k, numar_bile, numar_jucatori, valoare, index_col,
      index_col2, numar_shiftari, index_juc;
  // intrarile bilelor de sub forma unei comenzi
  char comanda[100], *p;
  // primul jucator castigator
  struct Winner winner;
  // initializam castigatorul cu -1, iar cand intalnim -1 executam comanda
  // pentru ca nu exista castigator
  winner.index = -1;
  winner.scor = 0;

  scanf("%d", &numar_jucatori);

  // initializarea matricelor si colorarea centrului
  for (jucator = 0; jucator < numar_jucatori; jucator++) {
    // pentru fiecare jucator se citeste o matrice bingo
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 5; j++) {
        scanf("%d", &bingo[jucator][i][j]);
        color[jucator][i][j] = bingo[jucator][i][j];
      }
    }
    color[jucator][2][2] = -1;
  }

  scanf("%d", &numar_bile);

  // citire bile sub forma unei comenzi si executarea comenzii la citire
  for (k = 0; k < numar_bile; k++) {
    scanf("%s", comanda);

    // se atribuie comanda iar apoi se proceseaza valorile
    p = strtok(comanda, "-\n");

    if (strcmp(p, "B") == 0) {
      index_col = 0;
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      valoare = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        colorare(valoare, numar_jucatori, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "I") == 0) {
      index_col = 1;
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      valoare = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        colorare(valoare, numar_jucatori, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "N") == 0) {
      index_col = 2;
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      valoare = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        colorare(valoare, numar_jucatori, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "G") == 0) {
      index_col = 3;
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      valoare = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        colorare(valoare, numar_jucatori, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "O") == 0) {
      index_col = 4;
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      valoare = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        colorare(valoare, numar_jucatori, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "ASC") == 0) {
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_col = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        sort_cresc(index_col, numar_jucatori, bingo, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "DSC") == 0) {
      // aflam valoarea asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_col = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        sort_desc(index_col, numar_jucatori, bingo, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "SHIFT") == 0) {
      // aflam prima valoare asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_col = atoi(p);
      // aflam a doua valoare asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      numar_shiftari = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        shift_col(index_col, numar_shiftari, numar_jucatori, bingo, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "SWAP") == 0) {
      // aflam prima valoare asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_col = atoi(p);
      // aflam a doua valoare asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_col2 = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        swap_col(index_col, index_col2, numar_jucatori, bingo, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }

    } else if (strcmp(p, "SHOW") == 0) {
      // aflam prima valoare asociata comenzii
      p = strtok(NULL, "-\n");
      // transformam sirul in int
      index_juc = atoi(p);
      // daca nu exista castigator executam comanda si verificam
      if (winner.index == -1) {
        show_card(index_juc, color);
        winner.index = verificare(numar_jucatori, color).index;
        winner.scor = verificare(numar_jucatori, color).scor;
      }
    }
  }

  // daca indexul winner este -1 inseamna ca niciun card nu este castigator
  if (winner.index == -1) {
    printf("NO WINNER\n");
  } else {
    printf("%d\n", winner.index);
    show_card(winner.index, color);
    printf("%d\n", winner.scor);
  }

  return 0;
}
