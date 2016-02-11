#include <stdio.h>
#include <stdlib.h>
#include "livre.h"

typedef struct cellule{
  s_livre livre;
  struct cellule *suivant;
  struct cellule *prec;
}Cellule;

typedef struct {
  struct cellule *debut;
  struct cellule *fin;
}Liste;

void init_liste(Liste *b){
  b->debut = NULL;
  b->fin = NULL;
}

int est_vide(Liste b)
{
  if (b.debut == NULL || b.fin == NULL)
    return 1;
  else
    return 0;
}


Cellule* creer_cellule(s_livre livre)
{
  Cellule *new = (Cellule *)malloc(sizeof(Cellule));
  new->livre = livre;
  new->suivant = NULL;
  new->prec = NULL;
  return new;
}

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void inserer_debut(Liste *b, s_livre livre)
{     
  Cellule *new = creer_cellule(livre);
  new->suivant = b->debut;
  if (b->debut != NULL)
    b->debut->prec = new;
  else
    b->fin = new;
  b->debut = new;
}

void afficher_prem_livre(Liste biblio)
{
  if (est_vide(biblio))
    printf("La bibliothèque est vide \n");
  else{
    printf("titre = %s \n",(biblio.debut->livre).titre);
    printf("auteur = %s \n",(biblio.debut->livre).auteur);
    printf("numero = %d \n",(biblio.debut->livre).num);
  }
}

void afficher_livre(Cellule c)
{
    printf("titre = %s \n",(c.livre).titre);
    printf("auteur = %s \n",(c.livre).auteur);
    printf("numero = %d \n",(c.livre).num);
}

void afficher_biblio(Liste biblio)
{
  Cellule *actu;
  actu = biblio.debut;
  while (actu != NULL){
    afficher_livre(*actu);
    actu = actu->suivant;
  }
}

Cellule* rechercher_numero(Liste b, int n)
{
  Cellule *cour = b.debut;
  while(cour != NULL){
    if(cour->livre.num == n){
      return cour;
    }
    cour = cour->suivant;
  }
  return NULL;
}

Cellule* rechercher_titre(Liste b, char *titre)
{
  Cellule *cour = b.debut;
  while(cour != NULL){
    if(cour->livre.titre == titre){
      return cour;
    }
    cour = cour->suivant;
  }
  return NULL;
}

int rechercher_nombre_titre(Liste b, char *titre)
{
  int cpt = 0;
  Cellule *cour = b.debut;
  while (cour != NULL){
    if (cour->livre.titre == titre){
      cpt ++;
    }
    cour = cour->suivant;
  }
  return cpt;
}

Liste rechercher_livres_auteur(Liste b, char *auteur)
{
  Liste livres_auteur;
  Cellule *cour = b.debut;
  init_liste(&livres_auteur);
  while(cour != NULL){
    if(cour->livre.auteur == auteur){
      /* On remarque que l'ordre des livres dans la liste est inversé par,rapport à la bibliotheque initiale*/
      inserer_debut(&livres_auteur,cour->livre);
    }
    cour = cour->suivant;
  }
  return livres_auteur;
}

void insertion_avant(Liste *b, s_livre l, char *titre)
{
  Cellule *new = creer_cellule(l);
  Cellule *c =  rechercher_titre(*b,titre);
  if (c != NULL){
    if(c->prec == NULL)
      b->debut = new;
    else{
      c->prec->suivant = new;
      new->prec = c->prec;
    }
    new->suivant = c;
    c->prec = new;
  }
}

void suppression(Liste *b, char *titre)
{
  Cellule *sup = rechercher_titre(*b, titre);
  if(sup != NULL){
    if(sup->prec == NULL)
      b->debut = sup->suivant;
    else
      sup->prec->suivant = sup->suivant;
    if(sup->suivant == NULL)
      b->fin = sup->prec;
    else
      sup->suivant->prec = sup->prec;
    free(sup);
  }
}

Liste doublon(Liste b)
{
  int cpt;
  Liste doublon;
  init_liste(&doublon);
  Cellule *cour = b.debut;
  while(cour != NULL){ 
    cpt = rechercher_nombre_titre(b,cour->livre.titre);
    if (cpt > 1){
      inserer_debut(&doublon,cour->livre);
    }
    cour = cour->suivant;
  }
  return doublon;
}

/*
int main(){
  s_livre l = init_livre("Toto a la plage","Raoul",1);
  s_livre l2 = init_livre("Billy travaille dans l'administration françaaaaaaaise","Raoul",2);
  s_livre l3 = init_livre("Toto a la plage","Raoul",3);
  Liste livres_auteur;
  Liste d;
  Cellule *c;
  Liste b;
  init_liste(&d);
  init_liste(&b);
  inserer_debut(&b,l);
  inserer_debut(&b,l2);
  c = rechercher_numero(b,1);
  livres_auteur = rechercher_livres_auteur(b,"Raoul");
  suppression(&b,"Toto a la plage");
  insertion_avant(&b, l, "Billy travaille dans l'administration françaaaaaaaise");
  inserer_debut(&b,l3);
  d = doublon(b);
  afficher_biblio(d);
  return 0;
}
*/
