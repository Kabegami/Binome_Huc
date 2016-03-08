#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "version_rapide.h"

S_Zsg init_zsg(int dim, int nbcl, Liste Lzsg, Liste *B, int **App)
{
  S_Zsg zone;
  zone.dim = dim;
  zone.nbcl = nbcl;
  zone.Lzsg = Lzsg;
  zone.B = B;
  zone.App = App;
  return zone;
}

/* ajoute la case M[i][j] dans la zone et retourne 0 si la case n est pas en bordure */
int ajoute_zsg(int **M, S_Zsg *zone, int i, int j)
{
  int couleur;
  if (zone->App[i][j] < 0)
    return 1;
  couleur = M[i][j];
  ajoute_en_tete(&(zone->Lzsg),i,j);
  suppression_el(&(zone->B[couleur]),i,j);
  return 0;
}

int ajoute_bordure(int **M, S_Zsg *zone, int i, int j)
{
  int couleur;
  couleur = M[i][j];
  if (zone->App[i][j] != couleur)
    return 1;
  ajoute_en_tete(&(zone->B[couleur]),i,j);
  suppression_el(&(zone->Lzsg),i,j);
  return 0;
}

int appartient_zsg(int **M, S_Zsg *zone, int i, int j)
{
  return (est_dans_liste(&(zone->Lzsg),i,j));
}

int appartient_bordure(int **M, S_Zsg *zone, int i, int j)
{
  return (est_dans_liste(&(zone->B[M[i][j]]),i,j));
}

int agrandit_zsg(int **M,Grille *G, S_Zsg *zone, int cl, int k, int l)
{
  int couleur = M[k][l];
  int cl_zone = M[0][0];
  int taille;
  Liste *pile = (Liste *)malloc(sizeof(Liste));
  Liste *zonekl = (Liste *)malloc(sizeof(Liste));
  int trash1,trash2;
  init_liste(pile);
  init_liste(zonekl);
  ajoute_en_tete(pile,k,l);
  //affiche_liste(pile,M);
  M[k][l] = -1;
  taille = 0;
  do {
    printf("Debut du while \n");
    ajoute_en_tete(zonekl,(*pile)->i,(*pile)->j);
    taille++;
    enleve_en_tete(pile,&trash1,&trash2);
    printf("Debut des if \n");
    /* case de droite */
    if((*zonekl)->i != (zone->dim-1) && M[(*zonekl)->i+1][(*zonekl)->j] == couleur)
    {
      M[(*zonekl)->i+1][(*zonekl)->j] = -1;
      ajoute_en_tete(pile,(*zonekl)->i+1,(*zonekl)->j);
      taille++;
    }
    else
      {
	printf("1 er if passe \n");
	if((*zonekl)->i != (zone->dim-1) && M[(*zonekl)->i+1][(*zonekl)->j] == cl_zone){
	  ajoute_en_tete(&(zone->Lzsg),(*zonekl)->i+1,(*zonekl)->j);
	  taille++;
	}
	else
	  {
	    printf("ajoute a la bordure \n");
	    ajoute_en_tete(&(zone->B[M[(*zonekl)->i+1][(*zonekl)->j]]),(*zonekl)->i+1,(*zonekl)->j);
	  }
      }

    printf("2 em if \n");
    /* case du bas */
    if((*zonekl)->j != (zone->dim-1) && M[(*zonekl)->i][(*zonekl)->j+1] == couleur)
    {
      M[(*zonekl)->i][(*zonekl)->j+1] = -1;
      ajoute_en_tete(pile,(*zonekl)->i,(*zonekl)->j+1);
      taille++;
    }
    else
      {
	if((*zonekl)->i != (zone->dim-1) && M[(*zonekl)->i][(*zonekl)->j+1] == cl_zone){
	  ajoute_en_tete(&(zone->Lzsg),(*zonekl)->i,(*zonekl)->j+1);
	  taille++;
	}
	else
	  {
	    ajoute_en_tete(&(zone->B[M[(*zonekl)->i][(*zonekl)->j+1]]),(*zonekl)->i,(*zonekl)->j+1);
	  }
      }    

    printf("3 eme if \n");
    /* case de gauche */
    if((*zonekl)->i != 0 && M[(*zonekl)->i-1][(*zonekl)->j] == couleur)
    {
      M[(*zonekl)->i-1][(*zonekl)->j] = -1;
      ajoute_en_tete(pile,(*zonekl)->i-1,(*zonekl)->j);
      taille++;
    }
    else
      {
	printf("meme couleur \n");
	if((*zonekl)->i != 0 && M[(*zonekl)->i-1][(*zonekl)->j] == cl_zone){
	  ajoute_en_tete(&(zone->Lzsg),(*zonekl)->i-1,(*zonekl)->j);
	  taille++;
	}
	else
	  {
	    if((*zonekl)->i != 0){
	    printf("%d %d \n",(*zonekl)->i-1,(*zonekl)->j);
	    printf("bordure \n");
	    ajoute_en_tete(&(zone->B[M[(*zonekl)->i-1][(*zonekl)->j]]),(*zonekl)->i-1,(*zonekl)->j);
	    }
	  }
      }
    
    /* case du haut */
    printf("4 eme if \n");
    if((*zonekl)->j != 0 && M[(*zonekl)->i][(*zonekl)->j-1] == couleur)
    {
      M[(*zonekl)->i][(*zonekl)->j-1] = -1;
      ajoute_en_tete(pile,(*zonekl)->i,(*zonekl)->j-1);
      taille++;
    }
    else
      {
	if((*zonekl)->i != 0 && M[(*zonekl)->i][(*zonekl)->j-1] == cl_zone){
	  ajoute_en_tete(&(zone->Lzsg),(*zonekl)->i,(*zonekl)->j-1);
	  taille++;
	}
	else
	  {
	    ajoute_en_tete(&(zone->B[M[(*zonekl)->i][(*zonekl)->j-1]]),(*zonekl)->i,(*zonekl)->j-1);
	  }
      }  
  }
  while(!test_liste_vide(pile));
  peint(G,cl_zone,M,zonekl);
  /* il faut ajouter tous les element de zonekl dans zone->Lzsg */
  while(!test_liste_vide(zonekl)){
  ajoute_en_tete(&(zone->Lzsg),(*zonekl)->i,(*zonekl)->j);
  enleve_en_tete(zonekl,&trash1,&trash2);
  }
  return taille;
}

int sequence_aleatoire_rapide(int **M, Grille *G, int aff)
{
  Liste Lzsg;
  init_liste(&Lzsg);
  Liste *B = (Liste*)malloc((G->nbcl)*sizeof(Liste));
  int **App = (int**)malloc((G->dim)*sizeof(int*));
  int i;
  for (i = 0; i < G->dim; i++){
    App[i] = malloc((G->dim)*sizeof(int));
  }

  printf("toto \n");
  S_Zsg zone = init_zsg(G->dim, G->nbcl, Lzsg, B, App);
  int couleur = M[0][0];

  printf("agrandit_zsg : \n");
  agrandit_zsg(M,G, &zone, couleur, 0, 0);
  printf("zone initiale :  \n");
  affiche_liste(&(zone.Lzsg), M);
  printf("-------------------------- \n");
  printf("bordure initiale : \n");
  affiche_liste(zone.B, M);
}
