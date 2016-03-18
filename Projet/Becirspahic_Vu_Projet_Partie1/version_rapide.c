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

/* ajoute la case M[i][j] dans la zone  */
int ajoute_zsg(int **M, S_Zsg *zone, int i, int j)
{
  int couleur;
  int t,t2;
  couleur = M[i][j];
  ajoute_en_tete(&(zone->Lzsg),i,j);
  zone->App[i][j] = -1;
  return 1;
}

int ajoute_bordure(int **M, S_Zsg *zone, int i, int j)
{
  int couleur;
  couleur = M[i][j];
  ajoute_en_tete(&(zone->B[couleur]),i,j);
  zone->App[i][j] = couleur;
  return 1;
}

void afficher_bordure(S_Zsg *zone)
{
  int i;
  for(i= 0; i < zone->dim;i++){
    if (zone->B[i] != NULL) {
    printf("bordure de la couleur %d :",i);
    affiche_liste(&(zone->B[i]));
    }
  }
}


/* Il s agit d un algorithme glouton qui renvoit les coordonnes de la premiere case de la bordure de la couleur qui contient le plus de cases */ 
void plus_grd_cl(S_Zsg zone, Grille *G ,int *i, int *j)
{
  int max = 0;
  int indice;
  int k;
  for(k = 0; k <G->nbcl ;k++){
    if (cpt_elem(&(zone.B[k])) > max){
      max = cpt_elem(&(zone.B[k]));
      indice = k;
    }
  }
  if (max != 0){
  *i = (zone.B[indice])->i;
  *j = (zone.B[indice])->j;
  }
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
  
  int taille = 0;
  int couleur;
  
  do{
    k = (*pile)->i;
    l = (*pile)->j;
    if (!(appartient_zsg(M, zone, k, l))){
	ajoute_zsg(M, zone, k, l);
	taille++;
      }
      enleve_en_tete(pile,&trash1,&trash2);
    
    /* case de droite */
    if(k != (zone->dim-1) && zone->App[k+1][l] != -1){
      if(zone->App[k+1][l] != -1 && M[k+1][l] == cl && !(appartient_zsg(M, zone, k+1, l))){
	//printf("(%d, %d) ajouté à zone\n", k+1, l);
	ajoute_en_tete(pile, k+1, l);
      }
    
      else{
	if(M[k+1][l] != cl && !(appartient_bordure(M, zone, k+1, l))){
	  ajoute_bordure(M, zone, k+1, l);
	  //printf("(%d, %d) ajouté à bordure\n", k+1, l);
	}
      }
    }
  

    /* case du bas */
    
    if(l != (zone->dim-1) && zone->App[k][l+1] != -1){
      if(zone->App[k][l+1] != -1 && M[k][l+1] == cl && !(appartient_zsg(M, zone, k, l+1))){
	//printf("(%d, %d) ajouté à zone\n", k, l+1);
	ajoute_en_tete(pile, k, l+1);
      }
    
      else{
	if(M[k][l+1] != cl && !(appartient_bordure(M, zone, k, l+1))){
	  ajoute_bordure(M, zone, k, l+1);
	  //printf("(%d, %d) ajouté à bordure\n", k, l+1);
	}
      }
    }
    
    /* case de gauche */
    if(k != 0 && zone->App[k-1][l] != -1){
      if(zone->App[k-1][l] != -1 && M[k-1][l] == cl && !(appartient_zsg(M, zone, k-1, l))){
	//printf("(%d, %d) ajouté à zone\n", k-1, l);
	ajoute_en_tete(pile, k-1, l);
      }
    
      else{
	if(M[k-1][l] != cl && !(appartient_bordure(M, zone, k-1, l))){
	  // ajoute_en_tete(bordure, k, l+1);
	  ajoute_bordure(M, zone, k-1, l);
	  // printf("(%d, %d) ajouté à bordure\n", k-1, l);
	}
      }
    }
    

    /* case du haut */
    if(l != 0 && zone->App[k][l-1] != -1){
      if(zone->App[k][l-1] != -1 && M[k][l-1] == cl && !(appartient_zsg(M, zone, k, l-1))){
	//printf("(%d, %d) ajouté à zone\n", k, l-1);
	ajoute_en_tete(pile, k, l-1);
      }
    
      else{
	if(M[k][l-1] != cl && !(appartient_bordure(M, zone, k, l-1))){
	  //printf("(%d, %d) ajouté à bordure\n", k, l-1);
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
  int k = 0;
  int l = 0;
  for (i = 0; i < G->dim; i++){
    App[i] = malloc((G->dim)*sizeof(int));
  }
  
  for(i = 0; i < G->dim; i++){
    for(j = 0; j < G->dim; j++)
      App[i][j] = -2; 
  }

  for (i = 0; i < G->nbcl; i++)
    init_liste(&B[i]);
  
  S_Zsg zone = init_zsg(G->dim, G->nbcl, Lzsg, B, App);
  int couleur = M[0][0];
  printf("couleur initiale : %d\n", couleur);

  int *tab = initialise_tab_couleur(G->nbcl);
  nb_couleur_initiales(&tab,M,G->dim);
  int new_couleur;
  int nbCoups = 0;
  int nbcl = G->nbcl;
  int taille;
  
  taille = agrandit_zsg(M, &zone, couleur, 0, 0);
  //printf("zone : ");
  // affiche_liste(&(zone.Lzsg));
  //afficher_bordure(&zone);
  //printf("Fin de la zone initiale \n");
  // printf("---------------------------------- \n");

  if(aff == 1){
    //Grille_attente_touche();
    Grille_redessine_Grille();
  }
  
  Elnt_liste *actu;

  do{
    plus_grd_cl(zone,G,&k,&l);
    couleur = M[k][l];
    actu = B[couleur];
    tab[M[0][0]] -= taille;
    tab[couleur] += taille;
    
    while(actu != NULL){
      //printf("%d, %d \n",actu->i,actu->j);
      taille += agrandit_zsg(M,&zone,couleur,actu->i,actu->j);
      actu = actu->suiv;
    }
    detruit_liste(&(zone.B[couleur]));

    peint(G,couleur,M,&(zone.Lzsg));
    nbcl = cpt_couleur(tab,G->nbcl);
    nbCoups++;
      
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    
  }while(nbcl > 1);
  
  printf("Couleur finale : %d\n", couleur);
  printf("nbCoups = %d\n", nbCoups);
  return nbCoups;
}
      
