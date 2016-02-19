#include "table_hachage.h"
#include <strings.h>

cell_t init()
{
  cell_t c;
  c.clef = 0;
  c.data = NULL;
  c.suivant = NULL;
  return c;
}


cell_t* creer_cellule_l(s_livre *livre)
{
  cell_t *new = (cell_t *)malloc(sizeof(cell_t));
  new->data = livre;
  new->suivant = NULL;
  new->clef = fonctionClef(livre->auteur);
  return new;
}

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void inserer_debut_l(cell_t **b, s_livre *livre)
{     
  cell_t *new = creer_cellule_l(livre);
  new->suivant = *b;
  *b = new;
}

void suppression_l(cell_t **liste, char *ti, char *a)
{
  cell_t *actu;
  cell_t *cell;
  actu = *liste;
  /* cas particulier premier elem de la liste */
   if ((strcmp(actu->data->titre,ti) + strcasecmp(actu->data->auteur,a)) == 0){
       *liste = actu->suivant;
       free(actu);
  }
  else{
    /* cherche la première occurence du couple (titre,auteur) */
    while( ((strcmp(actu->data->titre,ti) + strcasecmp(actu->data->auteur,a)) != 0) && actu->suivant != NULL && actu->suivant->suivant != NULL){
      actu = actu->suivant;
    }
     if (actu->suivant != NULL) {
       /* si on est entre 2 case */
       if ((strcmp(actu->data->titre,ti) + strcasecmp(actu->data->auteur,a)) == 0){
	 cell = actu->suivant;
	 actu->suivant = cell->suivant;
	 free(cell);
       }
    /* si on est l'avant dernière case */
       if(actu->suivant->suivant == NULL){
	 if ((strcmp(actu->suivant->data->titre,ti) + strcasecmp(actu->suivant->data->auteur,a)) == 0){
	   free(actu->suivant);
	   actu->suivant = NULL;
	 }
       }
     }
  }
}
cell_t* recherche_num_l(cell_t *b, int numero)
{
  cell_t * actu;
  actu = b;
  while(actu != NULL){
    if (actu->data->num == numero)
      return actu;
    actu = actu->suivant;
  }
  return NULL;
}

void recherche_auteur_l(cell_t **liste_auteur,cell_t *b, char *a)
{
  cell_t *actu;
  actu = b;
  if (actu != NULL){
  while(actu  != NULL){
    if(strcasecmp(actu->data->auteur,a) == 0){
      inserer_debut_l(liste_auteur,actu->data);
    }
      actu = actu->suivant;
  }
  }
}

int recherche_nb_titre_l(cell_t *b, char *t,char *auteur)
{
  int cpt = 0;
  cell_t *actu;
  actu = b;
  while(actu != NULL){
    if (strcmp(actu->data->titre,t) == 0 && strcasecmp(actu->data->auteur,auteur) == 0)
      cpt++;
    actu = actu->suivant;
  }
  return cpt;
}

void recherche_doublon_l(cell_t *biblio,cell_t **liste_doublon)
{
  cell_t *actu;
  actu = biblio;
  while(actu != NULL){
    if (recherche_nb_titre_l(biblio,actu->data->titre,actu->data->auteur) > 1)
      inserer_debut_l(liste_doublon,actu->data);
    actu = actu->suivant;
  }
}

void suppression_liste_totale(cell_t **liste)
{
  cell_t *actu = *liste;
  while (liste != NULL)
    {
      suppression_l(liste,actu->data->titre, actu->data->auteur);
    }
}

cell_t* recherche_titre_l(cell_t *b, char *t)
{
  cell_t * actu;
  actu = b;
  while(actu != NULL){
    if (strcasecmp(actu->data->titre,t) == 0)
      return actu;
    actu = actu->suivant;
  }
  return NULL;
}

void afficher_prem_livre_l(cell_t *l)
{
  if (l == NULL)
    printf("La bibliothèque est vide \n");
  else{
    printf("Titre : %s \n",(l->data)->titre);
    printf("Auteur : %s \n",(l->data)->auteur);
    printf("Numero : %d \n",(l->data)->num);
  }
}

void afficher_livre_l(cell_t *c)
{
    printf("Titre : %s \n",(c->data)->titre);
    printf("Auteur : %s \n",(c->data)->auteur);
    printf("Numero : %d \n",(c->data)->num);
}

void afficher_liste_l(cell_t *l)
{
  cell_t *actu;
  actu = l;
  while (actu != NULL){
    afficher_livre_l(actu);
    actu = actu->suivant;
  }
}
