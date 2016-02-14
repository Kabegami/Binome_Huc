#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <math.h>


typedef struct {
  int nbElem;
  int taille;
  cell_t **T; /* table de hachage avec resolution des collisions par chainage */
}tableHachage;


tableHachage* initTableHachage(int n)
{
  tableHachage *t = (tableHachage *)malloc(sizeof(tableHachage)); 
  int i;
  t->T = (cell_t **)malloc(n*sizeof(cell_t *));
  t->taille = n;
  t->nbElem = 0;
  for(i = 0; i < n; i++){
    t->T[i] = NULL;
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
  cell_t cel = creer_cellule_l(livre);
  int case_table = fonctionHachage(cel.clef,t->taille);
  printf("case numero : %d \n",case_table);
  inserer_debut_l((t->T)[case_table],livre);
  afficher_liste_l(t->T[case_table]);
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
    printf("toto \n");
    afficher_liste_l(t.T[i]);
    }
  }
}

int main(){
  tableHachage *t = initTableHachage(10);
  int i = fonctionClef("toto");
  s_livre l = init_livre("smdkqsopk","dmsksopkdpsk",3);
  int f = fonctionHachage(fonctionClef("smdkqsopk"),10);
  cell_t *liste = NULL;
  inserer_debut_l(liste,&l);
  afficher_liste_l(liste);
  insertion_table(t, &l);
  afficher_table(*t);
  printf("%d %d \n", i, f);
  return 0;
}
