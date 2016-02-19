#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _LISTEH_
#define _LISTEH_
#include "livre.h"

 struct cell{
  int clef;
  s_livre *data;
  struct cell *suivant;
};

typedef struct cell cell_t;

cell_t init();

cell_t* creer_cellule_l(s_livre *livre);

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void inserer_debut_l(cell_t **b, s_livre *livre);

void afficher_prem_livre_l(cell_t *l);

void afficher_livre_l(cell_t *c);

void afficher_liste_l(cell_t *l);

cell_t* recherche_num_l(cell_t *b, int numero);

cell_t* recherche_titre_l(cell_t *b, char *t);

void suppression_l(cell_t **liste, char *titre,char *auteur);

int recherche_nb_titre_l(cell_t *b, char *t,char *auteur);

void recherche_doublon_l(cell_t *biblio,cell_t **liste_doublon);

void recherche_auteur_l(cell_t **liste_auteur,cell_t *b, char *auteur);

#endif
