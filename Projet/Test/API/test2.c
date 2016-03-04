#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test2.h"


/* Dans cette fonction, on possede deux liste : L contenant les cases composant la zone et pile qui possede les cases adjacente aux cases entree en zone et ce termine quand le premier element de la pile est egal au premier element de L */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  Elnt_liste *pile;
  ajoute_en_tete(L,i,j);
  (*taille)++;
  do {
    M[pile->i][pile->j] = -1;
    ajoute_en_tete(L,pile->i,pile->j);
    /* case de droite */
    if(i != (dim-1) && M[(L->i)+1][L->j] == couleur)
    {
      M[pile->i][pile->j] = -1;
      ajoute_en_tete(pile,i+1,j);
    }
    /* case du bas */
    if (j != (dim-1) && M[L->i][L->j+1] == couleur)
      {
	M[pile->i][pile->j] = -1;
	ajoute_en_tete(pile,i,j+1);
      }
    
    /* case de gauche */
    if (i != 0 && M[L->i-1][L->j] == couleur)
      {
	M[pile->i][pile->j] = -1;
	ajoute_en_tete(pile,i-1,j);
      }

    /* case du haut */
    if(j != 0 && M[L->i][L->j-1] == couleur)
      {
	M[pile->i][pile->j] = -1;
	ajoute_en_tete(pile,i,j-1);
      }
  }
  while (L->i != pile->i && L->j != pile->j);
}
