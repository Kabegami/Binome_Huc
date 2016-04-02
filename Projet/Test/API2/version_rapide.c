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
  //if (zone->App[i][j] < 0)
  //  return 1;
  couleur = M[i][j];
  ajoute_en_tete(&(zone->Lzsg),i,j);
  zone->App[i][j] = -1;
  // suppression_el(&(zone->B[couleur]),i,j);
  return 1;
}

int ajoute_bordure(int **M, S_Zsg *zone, int i, int j)
{
  int couleur;
  couleur = M[i][j];
  //if (zone->App[i][j] != couleur)
  //  return 1;
  ajoute_en_tete(&(zone->B[couleur]),i,j);
  zone->App[i][j] = couleur;
  //  suppression_el(&(zone->Lzsg),i,j);
  return 1;
}

int appartient_zsg(int **M, S_Zsg *zone, int i, int j)
{
  return (zone->App[i][j] == -1);
}

int appartient_bordure(int **M, S_Zsg *zone, int i, int j)
{
  return (zone->App[i][j] == M[i][j]);
}

int agrandit_zsg(int **M, S_Zsg *zone, int cl, int k, int l)
{

  Liste *pile = (Liste *)malloc(sizeof(Liste));
  Liste *bordure = (Liste *)malloc(sizeof(Liste));
  int trash1,trash2;
  init_liste(pile);
  init_liste(bordure);
  ajoute_en_tete(pile,k,l);
  zone->App[k][l] = -1;
  int taille = 0;

  taille++;
  ajoute_zsg(M, zone, k, l);
  printf("(%d, %d) ajouté à zone\n", k, l);
  
  do{
    k = (zone->Lzsg)->i;
    l = (zone->Lzsg)->j;
    enleve_en_tete(pile,&trash1,&trash2);

    /* case de droite */
    if(k != (zone->dim-1) && (zone->App[k+1][l] != -1)){
      printf("1er if\n");
      if(M[k+1][l] == cl && !(appartient_zsg(M, zone, k+1, l))){
	printf("(%d, %d) ajouté à zone\n", k+1, l);
	ajoute_en_tete(pile, k+1, l);
	ajoute_zsg(M, zone, k+1, l);
	taille++;
      }
      else{
	if(M[k+1][l] != cl && !(appartient_bordure(M, zone, k+1, l))){
	  if(ajoute_bordure(M, zone, k+1, l))
	    printf("(%d, %d) ajouté à bordure\n", k+1, l);
	}
      }
    }

    /* case du bas */
    
    if(l != (zone->dim-1) && (zone->App[k][l+1] != -1)){
      printf("2eme if\n");
      if(M[k][l+1] == cl && !(appartient_zsg(M, zone, k, l+1))){
	printf("(%d, %d) ajouté à zone\n", k, l+1);
	ajoute_en_tete(pile, k, l+1);
	ajoute_zsg(M, zone, k, l+1);
	taille++;
      }
      else{
	if(M[k][l+1] != cl && !(appartient_bordure(M, zone, k, l+1))){
	  // ajoute_en_tete(bordure, k, l+1);
	  if(ajoute_bordure(M, zone, k, l+1))
	    printf("(%d, %d) ajouté à bordure\n", k, l+1);
	}
      }
    }
    
    /* case de gauche */
    if(k != 0 && (zone->App[k-1][l] != -1)){
      printf("3eme if\n");
      if(M[k-1][l] == cl && !(appartient_zsg(M, zone, k-1, l))){
	printf("(%d, %d) ajouté à zone\n", k-1, l);
	ajoute_en_tete(pile, k-1, l);
	ajoute_zsg(M, zone, k-1, l);
	taille++;
      }
      else{
	if(M[k-1][l] != cl && !(appartient_bordure(M, zone, k-1, l))){
	  printf("(%d, %d) ajouté à bordure\n", k-1, l);
	  //ajoute_en_tete(bordure, k-1, l);
	  ajoute_bordure(M, zone, k-1, l);
	}
      }
    }

    /* case du haut */
    if(l != 0 && (zone->App[k][l-1] != -1)){
      printf("4eme if\n");
      if(M[k][l-1] == cl && !(appartient_zsg(M, zone, k, l-1))){
	printf("(%d, %d) ajouté à zone\n", k, l-1);
	ajoute_en_tete(pile, k, l-1);
	ajoute_zsg(M, zone, k, l-1);
	taille++;
      }
      else{
	if(M[k][l+1] != cl && !(appartient_bordure(M, zone, k, l-1))){
	  printf("(%d, %d) ajouté à bordure\n", k, l-1);
	  //ajoute_en_tete(bordure, k, l-1);
	  ajoute_bordure(M, zone, k, l-1);
	}
      }
    }
    
  }while(!test_liste_vide(pile));
  return taille;
}


int sequence_aleatoire_rapide(int **M, Grille *G, int aff)
{
  /* initialisation de Zsg */
  Liste Lzsg;
  init_liste(&Lzsg);
  Liste *B = (Liste*)malloc((G->nbcl)*sizeof(Liste));
  int **App = (int**)malloc((G->dim)*sizeof(int*));
  int i, j;
  for (i = 0; i < G->dim; i++){
    App[i] = malloc((G->dim)*sizeof(int));
  }
  for(i = 0; i < G->dim; i++){
    for(j = 0; j < G->dim; j++)
      App[i][j] = -2; 
  }

  S_Zsg zone = init_zsg(G->dim, G->nbcl, Lzsg, B, App);
  int couleur = M[0][0];
  printf("couleur initiale : %d\n", couleur);

  int *tab = initialise_tab_couleur(G->nbcl);
  nb_couleur_initiales(&tab,M,G->dim);
  //afficher_tab(tab,G->nbcl);
  int new_couleur;
  int nbCoups = 0;
  int nbcl = G->nbcl;
  
  agrandit_zsg(M, &zone, couleur, 0, 0);
  printf("appel de aggrandit_zsg fini \n");
  affiche_liste(&(zone.Lzsg), M);
  affiche_liste(&(zone.B[2]), M);
  printf("----------------------------- \n");
  if(zone.B[0] != NULL){
    printf("(%d, %d)\n", B[0]->i, B[0]->j);
    affiche_liste(&(zone.B[0]), M);
  }
  if(&(zone.B[1]) != NULL){
    printf("B[1] non nul\n");
    affiche_liste(&(zone.B[1]), M);
  }
  

  /*do{
    do{
    new_couleur = (int)(rand()%(G->nbcl));
    }
    while(tab[new_couleur] == 0);

    if(new_couleur != couleur){
      //tab[couleur] -= taille;
      couleur = new_couleur;
      // tab[couleur] += taille;
      peint(G,couleur,M,&(zone.Lzsg));



      nbcl = cpt_couleur(tab,G->nbcl);
      nbCoups++;
    }
    if(aff == 1){
      // Grille_attente_touche();
      Grille_redessine_Grille();
    }

    }while(nbcl != 1);*/
  
}
