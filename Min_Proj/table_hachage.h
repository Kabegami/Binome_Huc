#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <math.h>

struct t_hg {
  int nbElem;
  int taille;
  cell_t **T; /* table de hachage avec resolution des collisions par chainage */
};

typedef struct t_hg tableHachage;


tableHachage* initTableHachage(int n);

int fonctionClef(char *nom);

int fonctionHachage(int clef, int m);

void insertion_table(tableHachage *t, s_livre *livre);

void afficher_table(tableHachage t);
