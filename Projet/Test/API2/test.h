#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Liste_case.h"


/* fonction recursive, qui definit la zone de la couleur de la case i,j en parametre qui utilise met la couleur a -1, dans les cases deja visite pour eviter une boucle infinie et qui remet la bonne couleur a la fin */
void peint(Grille *G,int couleur, int **M, Liste *L);

void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L);

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

int sequence_aleatoire_rec2(int **M, Grille *G, int dim, int aff);

int* initialise_tab_couleur(int nb_couleur);

int cpt_couleur(int *tab, int nb_couleur);

void afficher_tab(int *tab, int taille);

void nb_couleur_initiales(int **tab, int **M, int dim);
