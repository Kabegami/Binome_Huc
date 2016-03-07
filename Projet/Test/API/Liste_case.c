
#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"

 /* Initialise une liste vide */

void init_liste(Liste *L){
  *(L)=NULL;
}

/* Ajoute un element en tete de liste */
int ajoute_en_tete(Liste *L, int i, int j){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste *));
  if (elnt==NULL) 
    return 0;
  elnt->suiv=*L;
  elnt->i=i;
  elnt->j=j;
  (*L)=elnt;
}

/* teste si une liste est vide */
int test_liste_vide(Liste *L){
  return (*L)==NULL;
}

/* Supprime l element de tete et retourne les valeurs en tete */
/* Attention: il faut que la liste soit non vide */
void enleve_en_tete(Liste *L, int *i, int *j){
  Elnt_liste *temp;
  *i=(*L)->i;
  *j=(*L)->j;
  temp=*L;
  *L=(*L)->suiv;
  free(temp);
}

/* Detruit tous les elements de la liste */
void detruit_liste(Liste *L){
 Elnt_liste *cour,*temp;

  cour=(*L);
  while (cour!=NULL){
    temp=cour;
    cour=cour->suiv;
    free(temp);
  }

  *L=NULL;
}

void affiche_liste(Liste *L, int **M){
  Elnt_liste *actu;
  actu = *L;
  while (actu != NULL) {
    printf("(%d, %d)",actu->i, actu->j);
    actu = actu->suiv;
  }
  printf("\n");
}

/* retourne un boolean si l element est dans la liste ou non */
int est_dans_liste(Liste *L, int i,int j)
{
  Elnt_liste *actu;
  actu = *L;
  while (actu != NULL){
    if (actu->i == i && actu->j == j)
      return 1;
  }
  return 0;
}

void suppression_el(Liste (*L), int i,int j)
{
  Elnt_liste *temp;
  /* premier elem */
  if ((*L)->i == i && (*L)->j == i){
    temp = (*L);
    free((*L));
    (*L) = temp->suiv;
  }
  while((*L)->suiv->suiv != NULL  &&(*L)->suiv != NULL && (*L)->suiv->i != i || (*L)->suiv->j != j){
    (*L) = (*L)->suiv;
  }
  /* dernier elem */
  if ((*L)->suiv->suiv == NULL && (*L)->suiv->suiv->i == i && (*L)->suiv->suiv->j == j)
    {
      free((*L)->suiv->suiv);
      (*L)->suiv->suiv = NULL;
    }
  /* cas general */
  if((*L)->suiv->i == i && (*L)->suiv->j == j)
    {
      temp = (*L)->suiv;
      free((*L)->suiv);
      (*L)->suiv = temp->suiv;
    }
}
