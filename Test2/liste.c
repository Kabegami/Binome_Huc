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

void suppression_l(cell_t **liste, char *titre, char *auteur)
{
  cell_t *actu;
  cell_t *prec;
  actu = *liste;
  /* cas particulier premier elem de la liste */
  if (actu->data->titre == titre || actu->data->auteur == auteur){
    *liste = actu->suivant;
    free(actu);
  }
  else{
    /* cherche la première occurence du couple (titre,auteur) */
    while((actu->suivant->data->titre != titre ||actu->suivant->data->auteur != auteur) && actu->suivant != NULL ){
      actu = actu->suivant;
    }
  /* le if ne fait pas partie du while car sinon notre fonction supprimerait tous les ouvrages portant le titre donné et non pas un seul ouvrage */
    if ((actu->suivant)->data->titre == titre){
      prec = actu->suivant;
      actu->suivant = prec->suivant;
      free(prec);
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

void recherche_auteur_l(cell_t **liste_auteur,cell_t *b, char *auteur)
{
  cell_t *actu;
  actu = b;
  if (actu != NULL){
  while(actu->suivant != NULL){
    if(actu->data->auteur == auteur)
      inserer_debut_l(liste_auteur,actu->data);
    actu = actu->suivant;
  }
  if(actu->data->auteur == auteur)
      inserer_debut_l(liste_auteur,actu->data);
  }
}

int recherche_nb_titre_l(cell_t *b, char *t,char *auteur)
{
  int cpt = 0;
  cell_t *actu;
  actu = b;
  while(actu != NULL){
    if (actu->data->titre == t && actu->data->auteur == auteur)
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
