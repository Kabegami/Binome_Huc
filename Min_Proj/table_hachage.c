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


void insertion_table(tableHachage *t, cell_t *c)
{
  if (c != NULL){
    int my_clef = fonctionClef(c->data->auteur);
    int clef = fonctionHachage(fonctionClef(c->data->auteur),100);
    inserer_debut_l(t->T[clef], c->data, my_clef);
  }
  else{
    printf("Erreur \n");
  }
}

void afficher_table(tableHachage t)
{
  int i;
  cell_t *actu = t.T[0];
  for(i = 0; i < t.taille;i++){
    afficher_liste_l(t.T[i]);
  }
}

int main(){
  tableHachage *t = initTableHachage(10);
  int i = fonctionClef("toto");
  int f = fonctionHachage(i, 100);
  s_livre l = init_livre("smdkqsopk","dmsksopkdpsk",3);
  insertion_table(t, creer_cellule_l(&l,fonctionClef("smdkqsopk")));
  afficher_table(*t);
  printf("%d %d \n", i, f);
  return 0;
}
