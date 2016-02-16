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

cell_t* recherche_doublon(tableHachage t);

void suppression_t(tableHachage *t,s_livre *livre);

cell_t* livre_meme_auteur(tableHachage t, char *auteur);

cell_t* recherche_num(tableHachage t, int numero);

cell_t* recherche_titre(tableHachage t, char *titre);

