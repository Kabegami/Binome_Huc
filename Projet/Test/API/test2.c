#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test2.h"
#include "test.h"

/* Dans cette fonction, on possede deux liste : L contenant les cases composant la zone et pile qui possede les cases adjacente aux cases entree en zone et ce termine quand le premier element de la pile est egal au premier element de L */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  Liste *pile;
  ajoute_en_tete(L,i,j);
  (*taille)++;
  do {
    M[(*pile)->i][(*pile)->j] = -1;
    ajoute_en_tete(L,(*pile)->i,(*pile)->j);
    /* case de droite */
    if(i != (dim-1) && M[((*L)->i)+1][(*L)->j] == couleur)
    {
      M[(*pile)->i][(*pile)->j] = -1;
      ajoute_en_tete(pile,i+1,j);
    }
    /* case du bas */
    if (j != (dim-1) && M[(*L)->i][(*L)->j+1] == couleur)
      {
	M[(*pile)->i][(*pile)->j] = -1;
	ajoute_en_tete(pile,i,j+1);
      }
    
    /* case de gauche */
    if (i != 0 && M[(*L)->i-1][(*L)->j] == couleur)
      {
	M[(*pile)->i][(*pile)->j] = -1;
	ajoute_en_tete(pile,i-1,j);
      }

    /* case du haut */
    if(j != 0 && M[(*L)->i][(*L)->j-1] == couleur)
      {
	M[(*pile)->i][(*pile)->j] = -1;
	ajoute_en_tete(pile,i,j-1);
      }
  }
  while ((*L)->i != (*pile)->i && (*L)->j !=(*pile)->j);
}

int sequence_aleatoire_imp(int **M, Grille *G, int dim, int aff){
  int *tab = initialise_tab_couleur(G->nbcl);
  nb_couleur_initiales(&tab,M,G->dim);
  afficher_tab(tab,G->nbcl);
  int nbCoups = 0;
  srand(time(NULL));
 /* On definit Zsg, la zone contenant la case situee en haut a gauche */
  Liste L;
  init_liste(&L);
  int taille = 0;
  int new_couleur;
  int couleur = M[0][0];
  int nbcl = G->nbcl;
  trouve_zone_imp(M, dim, 0, 0, &taille, &L);
  printf("Couleur initiale : %d \n",couleur);

  /* selectionne une couleur tant que la grille contient plus d'une couleur  */
  do{
    /* pb avec le rand car ce en changant la taille de nbcl, on n est pas sur que la couleur supprime du rand soit celle desire */
    do{
    new_couleur = (int)(rand()%(G->nbcl));
    }
    while(tab[new_couleur] == 0);

    /* si la couleur selectionnee est differente de la couleur de Zsg */
    if(new_couleur != couleur){
      tab[couleur] -= taille;
      couleur = new_couleur;
      tab[couleur] += taille;
      peint(G,couleur,M,&L);
      /* on peint toute les cases avec la nouvelle couleur, puis on effectue une nouvelle recherche afin de voir si notre zone possede de nouvelles cases */ 
      detruit_liste(&L);
      taille = 0;
      printf("Couleur Zsg : %d\n", couleur);
      // printf("Couleur initiale : %d \n", M[i][j]);
      trouve_zone_imp(M,dim,0,0,&taille,&L);
      peint(G,couleur,M,&L);
      // printf("Couleur finale : %d \n",M[i][j]);
      printf("taille = %d \n",taille);
      affiche_liste(&L,M);
      nbcl = cpt_couleur(tab,G->nbcl);
      nbCoups++;
      //nbcl--;
      /* Pour la decrementation, je propose de dire que notre fonction s arrete quand notre zone partant de 0,0 est de taille = dim*dim */
      printf("nbcl = %d\n", nbcl);
      if(aff == 1){
      Grille_attente_touche();
      Grille_redessine_Grille();
      }
    }
  }while(nbcl != 1);
  
  printf("nbCoups = %d\n", nbCoups);
  return nbCoups;
}
