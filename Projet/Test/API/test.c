#include <stdio.h>
#include <stdlib.h>
#include "test.h"

/* fonction recursive, qui definit la zone de la couleur de la case i,j en parametre qui utilise met la couleur a -1, dans les cases deja visite pour eviter une boucle infinie et qui remet la bonne couleur a la fin */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  Elnt_liste *actu;
  init_liste(L);
  M[i][j] = -1;
  ajoute_en_tete(L,i,j);
  if(dim != i && M[i+1][j] == couleur)
    {
      trouve_zone_rec(M,dim,i+1,j,taille,L);
    }
  if(j != 0 && M[i][j-1] == couleur)
    {
      trouve_zone_rec(M,dim,i,j-1,taille,L);
    }
   if (i != 0 && M[i-1][j] == couleur)
    {
      trouve_zone_rec(M,dim,i-1,j,taille,L);
    }
   if (j != dim && M[i][j+1] == couleur)
     {
       trouve_zone_rec(M,dim,i,j+1,taille,L);
     }
   actu = *L;
   while (actu != NULL)
     {
       M[actu->i][actu->j] = couleur;
       actu = actu->suiv;
     }
}



