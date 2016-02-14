#include "table_hachage.h"

cell_t init(){
  cell_t c;
  c.clef = 0;
  c.data = NULL;
  c.suivant = NULL;
  return c;
}

cell_t creer_cellule_l(s_livre *livre)
{
  cell_t new;
  new.data = livre;
  new.suivant = NULL;
  new.clef = fonctionClef(livre->auteur);
  return new;
}

/* on veut modifier notre biblio, par consequent on entre un pointeur */
void inserer_debut_l(cell_t *b, s_livre *livre)
{     
  cell_t new = creer_cellule_l(livre);
  new.suivant = b;
  b = &new;
}

void afficher_prem_livre_l(cell_t *l)
{
  if (l == NULL)
    printf("La bibliothèque est vide \n");
  else{
    printf("titre = %s \n",(l->data)->titre);
    printf("auteur = %s \n",(l->data)->auteur);
    printf("numero = %d \n",(l->data)->num);
  }
}

void afficher_livre_l(cell_t c)
{
    printf("titre = %s \n",(c.data)->titre);
    printf("auteur = %s \n",(c.data)->auteur);
    printf("numero = %d \n",(c.data)->num);
}

void afficher_liste_l(cell_t *l)
{
  cell_t *actu;
  actu = l;
  while (actu != NULL){
    afficher_livre_l(*actu);
    actu = actu->suivant;
  }
}
