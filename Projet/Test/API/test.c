#include <stdio.h>
#include <stdlib.h>
#include "test.h"

/* fonction recursive, qui definit la zone de la couleur de la case i,j en parametre qui  met la couleur a -1 dans les cases deja visitees pour eviter une boucle infinie et qui remet la bonne couleur a la fin */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  //printf("couleur = %d\n", M[i][j]);
  //printf("%d\n", M[i][j]);
  //printf("%d\n", M[i+1][j]);
  Elnt_liste *actu;
  ajoute_en_tete(L,i,j);
  (*taille)++;

  while(M[i][j] == couleur){
    M[i][j] = -1;

  /* case de droite */
  if(i != (dim-1) && M[i+1][j] == couleur)
    {
      printf("droite, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i+1,j,taille,L);
    }

  /* case du bas */
  if (j != (dim-1) && M[i][j+1] == couleur)
    {
      printf("bas, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i,j+1,taille,L);
    }

  /* case de gauche */
  if (i != 0 && M[i-1][j] == couleur)
    {
      printf("gauche, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i-1,j,taille,L);
    }

  /* case du haut */
  if(j != 0 && M[i][j-1] == couleur)
    {
      printf("haut, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i,j-1,taille,L);
    }
  }
}

/* on stoque la couleur initiale avant de lancer notre fonction trouve_zone_rec puis apres avoir optenu la zone on la recolorise a l aide de cette fonction */
void peint(int couleur, int **M, Liste *L)
{
  Elnt_liste *actu;
  actu = *L;
  while(actu != NULL){
    M[actu->i][actu->j] = couleur;
    actu = actu->suiv;
  }
}

/* joue avec une couleur aleatoire en appellant la fonction trouve_zone_rec et retourne le nombre de cou^necessaire pour gagner
aff est un bollean indiquant si il faut reafficher la grille ou non
nbcouleur est le nombre de changement de couleur et notre valeur de retour
*/
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
  /* tant que le terrain n est pas compose d une unique couleur */
  while(dim != G->dim){
  int i = (int)random()*G->dim;
  int j = (int)random()*G->dim;
  Liste *L;
  init_liste(L);
  trouve_zone_rec(M,0,i,j,&dim,L);
  }
  return nbcl;
}
