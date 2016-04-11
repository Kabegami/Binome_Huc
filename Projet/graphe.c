#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

/* Fonction liste sommet
   ---------------------------------------------------------- */

void ajoute_liste_sommet(Cellule_som **liste,Sommet *s)
{
  Cellule_som *new;
  new = (Cellule_som *)malloc(sizeof(Cellule_som));
  new->sommet = s;
  new->suiv = *liste;
  *liste = new;
}

void detruire_liste_sommet(Cellule_som *liste)
{
  Cellule_som *actu;
  Cellule_som *temp;
  actu = liste;
  while(actu != NULL){
    temp = actu;
    actu = actu->suiv;
    printf("je supprime %d\n", temp->sommet->num);
    free(temp);
    }
  liste = NULL;
}

int recherche_sommet(Cellule_som *liste, Sommet s)
{
  Cellule_som *actu;
  actu = liste;
  while(actu != NULL){
    if (actu->sommet == &s)
      return 1;
    actu = actu->suiv;
  }
  return 0;
}

void affiche_voisin(Sommet *s)
{
  Cellule_som *actu = s->sommet_adj;
  printf("Voisins : ");
  while (actu != NULL){
    printf("%d ",actu->sommet->num);
    affiche_liste(&(actu->sommet->cases));
    actu = actu->suiv;
  }
  printf("\n");
}

void affiche_sommet(Cellule_som *liste)
{
  Cellule_som *actu = liste;
  while (actu != NULL){
    printf("Marque : %d\n",actu->sommet->marque);
    printf("Sommet %d : de couleur %d, taille : %d\n",actu->sommet->num, actu->sommet->cl,actu->sommet->nbcase_som);
    affiche_liste(&(actu->sommet->cases));
    if (actu->sommet->pere != NULL)
       printf("Pere : %d, ", actu->sommet->pere->num);
    printf("distance : %d\n",actu->sommet->distance);
    printf("\n");
    //affiche_voisin(actu->sommet);
    actu = actu->suiv;
  }
}

/* Fonction sommet
   --------------------------------------------*/

int adjacent(Sommet *s1, Sommet *s2)
{
  int i;
  for(i = 0; i < s1->nbcase_som;i++){
    if(recherche_sommet(s1->sommet_adj,*s2))
      return 1;
  }
  return 0;
}

void ajoute_voisin(Sommet *s1, Sommet *s2)
{
  // on verifie qu il n y a pas de doublon dans la liste
  if (!(adjacent(s1,s2)))
    ajoute_liste_sommet(&(s1->sommet_adj), s2);
  // on verifie qu il n y a pas de doublon dans la liste
  if (!(adjacent(s2,s1)))
    ajoute_liste_sommet(&(s2->sommet_adj), s1);
}


int est_arete(Sommet *s1, Sommet *s2)
{
  Cellule_som *actu = s1->sommet_adj;
  while (actu != NULL){
    if (actu->sommet == s2)
      return 1;
    actu=actu->suiv;
  }
  return 0;
}


Sommet* creer_sommet(int num, int cl,Liste l, int nbcase_som,int marque, Cellule_som *sommet_adj)
{
  Sommet *s = (Sommet *)malloc(sizeof(Sommet));
  s->num = num;
  s->cl = cl;
  s->cases = l;
  s->nbcase_som = nbcase_som;
  s->marque = marque;
  s->sommet_adj = sommet_adj;
  s->pere = NULL;
  s->distance = -1;
  return s;
}

void actualise_mat(Graphe_zone *Graphe, Sommet *s){
  Elnt_liste *actu = s->cases;
  while (actu != NULL){
    // printf("Sommet (%d , %d)",actu->i,actu->j);
    (Graphe->mat)[actu->i][actu->j] = s;
    actu = actu->suiv;
  }
  //printf("\n");
}

void creer_arete(Graphe_zone *Graphe, Grille *G)
{
  int i,j;
  Sommet *s;
  for(i = 0; i < G->dim;i++){
    for(j = 0; j < G->dim;j++){
      s = (Graphe->mat)[i][j];
      if(i != (G->dim) -1 && (s != ((Graphe->mat)[i+1][j]))){
	if(!(est_arete(s,(Graphe->mat)[i+1][j])))
	  ajoute_voisin(s,(Graphe->mat)[i+1][j]);
      }
      if(i != 0 && (s != ((Graphe->mat)[i-1][j]))){
	if(!(est_arete(s,(Graphe->mat)[i-1][j])))
	  ajoute_voisin(s,(Graphe->mat)[i-1][j]);
      }
      if(j != (G->dim) -1 && (s != ((Graphe->mat)[i][j+1]))){
	if(!(est_arete(s,(Graphe->mat)[i][j+1])))
	  ajoute_voisin(s,(Graphe->mat)[i][j+1]);
      }
      if(j != 0 && (s != ((Graphe->mat)[i][j-1]))){
	if(!(est_arete(s,(Graphe->mat)[i][j-1])))
	  ajoute_voisin(s,(Graphe->mat)[i][j-1]);
      }
    }
  }
}

void affiche_graphe(Grille *G, Graphe_bordure *bordure)
{
  int i;
  for (i = 0; i < G->nbcl; i++){
    printf("----------------------\n");
    printf("Bordure de couleur %d\n", i);
    printf("----------------------\n");
    affiche_sommet((bordure->liste)[i]);
    printf("Taille totale : %d\n\n", (bordure->taille)[i]);
  }
  printf("-----------------Zsg-----------------\n");
  affiche_sommet(bordure->zsg);
}

Graphe_zone* creer_graphe_zone(Grille *G, int **M)
{
  int i,j;
  int num = 0;

  int taille = 0;
  int couleur;

  Graphe_zone *Graphe;
  Graphe = (Graphe_zone*)malloc(sizeof(Graphe_zone*));
  Graphe->nbsom = 0;
  Graphe->som = NULL;
  Graphe->mat = (Sommet ***)malloc(G->dim*sizeof(Sommet *));
  for(i = 0; i < G->dim; i++){
    (Graphe->mat)[i] = (Sommet**)malloc(G->dim*sizeof(Sommet*));
    for(j = 0; j < G->dim; j++){
      (Graphe->mat)[i][j] = NULL;
    }
  }
  for(i = 0; i < G->dim; i++){
    for(j = 0; j < G->dim; j++){
      if ((Graphe->mat)[i][j] == NULL){
	Liste L;
	init_liste(&L);
	couleur = M[i][j];
	trouve_zone_rec(M,G->dim,i,j,&taille,&L);
	peint(G,couleur,M,&L);
	Graphe->nbsom++;
	Sommet *s = creer_sommet(num,M[i][j],L,taille,2,NULL);
	num++;
	//printf("sommet %d : ",s->num);
	//affiche_liste(&(s->cases));
	actualise_mat(Graphe,s);
	ajoute_liste_sommet(&(Graphe->som),s);
	//detruit_liste(&L);
	taille = 0;
      }
    }
  }
  creer_arete(Graphe,G);
  // affiche_sommet(Graphe->som);
  //printf("-------------\n");
  
  return Graphe;
}

void actualise_voisin(Graphe_bordure *bordure, Cellule_som *s)
{
  Cellule_som *actu = s->sommet->sommet_adj;
  while (actu != NULL){
    if (actu->sommet->marque == 2){
      //ajoute_liste_sommet(&(bordure->zsg->sommet->sommet_adj),actu->sommet);
      ajoute_liste_sommet(&((bordure->liste)[actu->sommet->cl]),actu->sommet);
      (bordure->taille)[actu->sommet->cl] += actu->sommet->nbcase_som;
      actu->sommet->marque = 1;
    }
    actu = actu->suiv; 
  }
}

Graphe_bordure* creer_bordure(Grille *G, Graphe_zone *Graphe, int tout)
{
  Graphe_bordure *bordure;
  bordure = (Graphe_bordure*)malloc(sizeof(Graphe_bordure*));
  bordure->taille = (int*)malloc(G->nbcl*sizeof(int));;
  bordure->liste = (Cellule_som**)malloc(G->nbcl*sizeof(Cellule_som*));

  /* !! initialisation du tableau de listes !! */
  int i;
  for (i = 0; i < G->nbcl; i++){
    (bordure->liste)[i] = NULL;
    (bordure->taille)[i] = 0;
  }

  // initialisation du tableau de sommets

  bordure->tab = (Sommet **)malloc(Graphe->nbsom*sizeof(Sommet *));
  Cellule_som *actu = Graphe->som;
  while (actu != NULL){
    (bordure->tab)[actu->sommet->num] = actu->sommet;
    actu = actu->suiv;
  }
  Sommet *zsg = (Graphe->mat)[0][0];
  ajoute_liste_sommet(&(bordure->zsg),zsg);
  zsg->marque = 0;

  /* on attribue les bordures de Zsg */

  /* pour le parcours en largeur, toutes les bordures */
  if (tout == 1){
    Cellule_som *actu = zsg->sommet_adj;
    while (actu != NULL){
      actualise_voisin(bordure,actu);
      actu = actu->suiv;
    }
  }
  else
    actualise_voisin(bordure,bordure->zsg);

  //affiche_graphe(G, bordure);
  return bordure;
}

void actualise_bordure(int cl, Graphe_zone *Graphe, Graphe_bordure *bordure)
{
  Cellule_som *actu = (bordure->liste)[cl];
  Cellule_som *tmp;
  (bordure->taille)[bordure->zsg->sommet->cl] = 0;
  (bordure->taille)[cl] = 0;
  (bordure->liste)[bordure->zsg->sommet->cl] = NULL;
 
  while (actu != NULL){
    actu->sommet->marque = 0;
    /* on ajoute les sommets dans la liste de la nouvelle couleur
       et on les supprime dans la liste de l'ancienne couleur*/
    ajoute_liste_sommet(&(bordure->zsg),actu->sommet);
    actualise_voisin(bordure, actu);
    (bordure->liste)[cl] = NULL;
    //tmp = actu;
    actu = actu->suiv;
    //free(tmp);
  }
  //(bordure->liste)[bordure->zsg->sommet->cl] = NULL;
}

void peint_zsg(Grille *G, int cl, Graphe_bordure *bordure)
{
  Cellule_som *actu = bordure->zsg;
  Elnt_liste *actu_liste;
  while (actu != NULL){
    actu->sommet->cl = cl;
    actu_liste = actu->sommet->cases;
    while(actu_liste != NULL){
      Grille_attribue_couleur_case(G,actu_liste->i,actu_liste->j,cl);
      actu_liste = actu_liste->suiv;
    }
    actu=actu->suiv;
  }
}

int max_couleur(Grille *G, Graphe_bordure *bordure){
  int max_cl = 0;
  int cour = 0;
  int i = 0;
  while (i < G->nbcl){
    if ((bordure->taille)[i] > cour){
      max_cl = i;
      cour = (bordure->taille)[i];
    } 
    i++;
  }
  return max_cl;
}

int bordure_vide(Grille *G, Graphe_bordure *bordure){
  int i;
  for (i = 0; i < G->nbcl; i++)
    if ((bordure->taille)[i] != 0){
      //affiche_sommet((bordure->liste)[i]);
      return 0;
    }	        
  return 1;
}

