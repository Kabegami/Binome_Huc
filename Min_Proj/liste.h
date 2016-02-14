#include <stdio.h>
#include <stdlib.h>
#include "livre.h"

 struct cell{
  int clef;
  s_livre *data;
  struct cell *suivant;
};

typedef struct cell cell_t;

cell_t init();

cell_t creer_cellule_l(s_livre *livre);

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void inserer_debut_l(cell_t *b, s_livre *livre);

void afficher_prem_livre_l(cell_t *l);

void afficher_livre_l(cell_t c);

void afficher_liste_l(cell_t *l);

