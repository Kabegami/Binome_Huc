#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Liste_case.h"


void peint(Grille *G,int couleur, int **M, Liste *L);

void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L);

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

int sequence_aleatoire_rec2(int **M, Grille *G, int dim, int aff);

int* initialise_tab_couleur(int nb_couleur);

int cpt_couleur(int *tab, int nb_couleur);

void afficher_tab(int *tab, int taille);

void nb_couleur_initiales(int **tab, int **M, int dim);
