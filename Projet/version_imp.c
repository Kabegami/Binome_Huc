#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "version_imp.h"

/* Dans cette fonction, on possede deux liste : L contenant les cases composant la zone et pile qui possede les cases adjacente aux cases entree en zone et ce termine quand le premier element de la pile est egal au premier element de L */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  Liste *pile = (Liste *)malloc(sizeof(Liste));
  int trash1,trash2;
  init_liste(pile);
  ajoute_en_tete(pile,i,j);
  //affiche_liste(pile,M);
  M[i][j] = -1;
  (*taille) = 0;
  do {
    ajoute_en_tete(L,(*pile)->i,(*pile)->j);
    (*taille)++;
    enleve_en_tete(pile,&trash1,&trash2);
    /* case de droite */
    if((*L)->i != (dim-1) && M[(*L)->i+1][(*L)->j] == couleur)
    {
      M[(*L)->i+1][(*L)->j] = -1;
      ajoute_en_tete(pile,(*L)->i+1,(*L)->j);
    }
    /* case du bas */
    if ((*L)->j != (dim-1) && M[(*L)->i][(*L)->j+1] == couleur)
      {
	M[(*L)->i][(*L)->j+1] = -1;
	ajoute_en_tete(pile,(*L)->i,(*L)->j+1);
      }
    
    /* case de gauche */
    if ((*L)->i != 0 && M[(*L)->i-1][(*L)->j] == couleur)
      {
	M[(*L)->i-1][(*L)->j] = -1;
	ajoute_en_tete(pile,(*L)->i-1,(*L)->j);
      }

    /* case du haut */
    if((*L)->j != 0 && M[(*L)->i][(*L)->j-1] == couleur)
      {
	M[(*L)->i][(*L)->j-1] = -1;
	ajoute_en_tete(pile,(*L)->i,(*L)->j-1);
      }
  }
  while(!test_liste_vide(pile));
}

int sequence_aleatoire_imp(int **M, Grille *G, int dim, int aff){
  /* initialisation du tableau de couleurs dans la grille */
  int *tab = initialise_tab_couleur(G->nbcl);
  nb_couleur_initiales(&tab,M,G->dim);
  //afficher_tab(tab,G->nbcl);
  int nbCoups = 0;
  srand(time(NULL));
  
  /* On definit Zsg, la zone contenant la case situee en haut a gauche */
  Liste L;
  init_liste(&L);
  int taille = 0;
  int new_couleur;
  int couleur = M[0][0];
  int nbcl = cpt_couleur(tab,G->nbcl);
  trouve_zone_imp(M, dim, 0, 0, &taille, &L);
  printf("Couleur initiale : %d \n",couleur);

  /* selectionne une couleur tant que la grille contient plus d'une couleur  */
  do{
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
      trouve_zone_imp(M,dim,0,0,&taille,&L);
      peint(G,couleur,M,&L);
      nbcl = cpt_couleur(tab,G->nbcl);
      nbCoups++;

      if(aff == 1){
	//Grille_attente_touche();
	Grille_redessine_Grille();
      }
      if(aff == 2){
	affiche_liste(&L);
	Grille_attente_touche();
	Grille_redessine_Grille();
      }
    }
  }while(nbcl > 1);

  printf("Couleur finale : %d\n", couleur);
  // printf("nbCoups = %d\n", nbCoups);
  return nbCoups;
}
