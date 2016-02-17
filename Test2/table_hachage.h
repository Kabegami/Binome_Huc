#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entree_sortie.h"
#ifndef _table_hachageh_
#define _table_hachageh_
#include "liste.h"


struct t_hg {
  int nbElem;
  int taille;
  cell_t **T; /* table de hachage avec resolution des collisions par chainage */
};

typedef struct t_hg tableHachage;

tableHachage initTableHachage(int n);

int fonctionClef(char *nom);

int fonctionHachage(int clef, int m);

void lecture_hachage(tableHachage *t, int n);

void afficher_table(tableHachage t);

cell_t* recherche_doublon_t(tableHachage t);

void suppression_t(tableHachage *t,s_livre *livre);

cell_t* livre_meme_auteur_t(tableHachage t, char *auteur);

cell_t* recherche_num_t(tableHachage t, int numero);

cell_t* recherche_titre_t(tableHachage t, char *titre);

void insertion_table(tableHachage *t, s_livre *livre);

cell_t ** copy_T(tableHachage t, int taille);

void augmenter_taille(tableHachage *t);

#endif
