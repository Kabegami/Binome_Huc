#include <stdio.h>
#include <stdlib.h>
#include "livre.h"

typedef struct cellule{
  s_livre livre;
  struct cellule *suivant;
}Cellule;

/* Comme il s'agit d'une liste simple, notre objet stoquant notre bibliotèque est un pointeur de Cellule */

Cellule* CreerCellule(s_livre livre)
{
  Cellule *new = (Cellule *)malloc(sizeof(Cellule));
  new->livre = livre;
  new->suivant = NULL;
  return new;
}

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void Inserer(Cellule **biblio, s_livre livre)
{
  Cellule *new = CreerCellule(livre);
  new->suivant = *biblio;
  *biblio = new;
}

void afficher_prem_livre(Cellule *biblio)
{
  if (biblio == NULL)
    printf("La bibliotèque est vide \n");
  else{
    printf("titre = %s \n",(biblio->livre).titre);
    printf("auteur = %s \n",(biblio->livre).auteur);
    printf("numero = %d \n",(biblio->livre).num);
  }
}

int main(){
  s_livre l = init_livre("Toto a la plage","Raoul",1);
  Cellule *biblio = NULL;
  Inserer(&biblio,l);
  afficher_prem_livre(biblio);
  return 0;
}
