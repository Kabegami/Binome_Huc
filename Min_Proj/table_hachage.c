#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <math.h>


typedef struct {
  int nbElem;
  int taille;
  cell_t **T; /* table de hachage avec resolution des collisions par chainage */
}tableHachage;


tableHachage initTableHachage(int n)
{
  tableHachage t;
  int i;
  t.T = (cell_t **)malloc(n*sizeof(cell_t *));
  t.taille = n;
  t.nbElem = 0;
  for(i = 0; i < n; i++){
    t.T[i] = NULL;
  }
  return t;
}

int fonctionClef(char *nom)
{
  int clef = 0;
  int i;
  for(i = 0; nom[i] != '\0';i++){
    clef += nom[i];
  }
  return clef;
}

int fonctionHachage(int clef, int m)
{
  double  a = (sqrt(5)-1)/2;
  return (int)(m*(clef*a-(int)(clef*a)));
}


void insertion_table(tableHachage *t, s_livre *livre)
{
  cell_t *cel = creer_cellule_l(livre);
  int case_table = fonctionHachage(cel->clef,t->taille);
  inserer_debut_l(&((t->T)[case_table]),livre);
}

void afficher_table(tableHachage t)
{
  int i;
  cell_t *actu = t.T[0];
  for(i = 0; i < t.taille;i++){
    if (t.T[i] == NULL){
      printf("Case numero : %d", i);
      printf("est vide \n");
    }
    else{
    printf("Case numero : %d \n", i);
    printf("\n");
    afficher_liste_l(t.T[i]);
    }
    printf("---------------------------\n");
  }
}

cell_t* recherche_num(tableHachage t, int numero)
{
  int i;
  cell_t *cell;
  for(i = 0; i < t.taille;i++){
    cell = recherche_num_l(t.T[i],numero);
    if (cell != NULL)
      return cell;
  }
}


cell_t* recherche_titre(tableHachage t, char *titre)
{
  int i;
  cell_t *cell;
  for(i = 0; i < t.taille;i++){
    cell = recherche_titre_l(t.T[i],titre);
    if (cell != NULL)
      return cell;
  }
}


cell_t* livre_meme_auteur(tableHachage t, char *auteur)
{
  int clef = fonctionClef(auteur);
  int case_tab = fonctionHachage(clef,t.taille);
  return t.T[case_tab];
}

cell_t* recherche_doublon(tableHachage t)
{
  cell_t *liste = NULL;
  int i;
  for(i = 0; i < t.taille;i++) {
    recherche_doublon_l(t.T[i],&liste);
    }
  return liste;
}

void suppression_t(tableHachage *t,s_livre *livre)
{
  int clef = fonctionClef(livre->auteur);
  int case_tab = fonctionHachage(clef,t->taille);
  suppression_l(&(t->T[case_tab]),livre->titre,livre->num);
}

int main(){
  tableHachage t = initTableHachage(10);
  int i = fonctionClef("toto");
  s_livre l = init_livre("toto","Raoul",3);
  s_livre l2 = init_livre("billy","Raoul",4);
  s_livre l3 = init_livre("toto","Raoul",5);
  int f = fonctionHachage(fonctionClef("toto"),10);
  cell_t *liste;
  insertion_table(&t, &l);
  insertion_table(&t, &l2);
  insertion_table(&t, &l3);
  afficher_table(t);
  printf("recherche doublon : \n");
  liste = recherche_doublon(t);
  afficher_liste_l(liste);
  return 0;
}
