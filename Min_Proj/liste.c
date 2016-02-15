#include "table_hachage.h"

cell_t init(){
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

void suppression_l(cell_t **liste, char *titre, int numero)
{
  cell_t *actu;
  cell_t *prec;
  actu = *liste;
  /* cas particulier premier elem de la liste */
  /* c'est le if qui provoque une erreur de segmentation */
  if (actu->data->titre == titre || actu->data->num == numero){
    *liste = actu->suivant;
    free(actu);
  }
  else{
    while((actu->suivant->data->titre != titre ||actu->suivant->data->num != numero) && actu->suivant != NULL ){
      actu = actu->suivant;
    }
  /* le if ne fait pas partie du while car si sinon notre fonction supprimerais tout les ouverage portant le titre donné et non pas un ouvrage */
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

cell_t* recherche_titre_l(cell_t *b, char *t)
{
  cell_t * actu;
  actu = b;
  while(actu != NULL){
    if (actu->data->titre == t)
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
    printf("titre = %s \n",(l->data)->titre);
    printf("auteur = %s \n",(l->data)->auteur);
    printf("numero = %d \n",(l->data)->num);
  }
}

void afficher_livre_l(cell_t *c)
{
    printf("titre = %s \n",(c->data)->titre);
    printf("auteur = %s \n",(c->data)->auteur);
    printf("numero = %d \n",(c->data)->num);
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
