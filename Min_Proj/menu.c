#include <stdio.h>
#include "biblio.h"
#include "entree_sortie.h"

void remplir_livre(s_livre l)
{
  FILE *f = fopen("GdeBiblio.txt","r"); 
  char *chaine1 = (char *)(malloc(30*sizeof(char)));
  char *chaine2 = (char *)(malloc(30*sizeof(char)));
  int i;
  int nb;
  for(i = 0; i < 3; i++){
    GetChaine(f,10,chaine1);
    GetChaine(f,10,chaine2);
    /* cast pour arriver à un int */
    nb = GetEntier(f);
  }
  l = init_livre(chaine1,chaine2,nb);
}


int main(){
  s_livre l;
  remplir_livre(l);
  printf("titre = %s \n",l.titre);
  printf("auteur = %s \n",l.auteur);
  printf("numero = %d \n",l.num);
  return 0;
}
