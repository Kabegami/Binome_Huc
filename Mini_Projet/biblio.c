#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"

/* structure */

typedef struct{
  char *titre;
  char *auteur;
  int num;
}s_livre;

typedef struct {
  s_livre livre;
  s_livre *suivant;
}cellule;

s_livre def_livre(char *titre, char *auteur,int num)
{
  s_livre livre;
  livre.titre = (char *)malloc(strlen(titre)*sizeof(char));
  livre.titre = titre;
  livre.auteur = (char *)malloc(strlen(auteur)*sizeof(char));
  livre.auteur = auteur;
  livre.num = num;
  return livre;
}

void init_livre(s_livre *livre)
{
  /* On choisit 0 comme numéro non existant */
  /* livre->titre = (char *)malloc(30*sizeof(char));*/
  livre->titre = NULL;
  /*livre->auteur = (char *)malloc(30*sizeof(char));*/
  livre->auteur = NULL;
  livre->num = 0;
}


void init_cellule(cellule *L)
{
  init_livre(&(L->livre));
  L->suivant = (s_livre *)malloc(sizeof(void *));
  L->suivant = NULL;
}


/* Fonction de lecture */

void AfficheLine(FILE *f){
  char c ;
  
  do{
    c = getc(f) ;
    printf("%c",c);
  }
  while ((c!=EOF)&&(c!='\n')) ;
}


void remplir(s_livre *livre)
{
  FILE *fichier = fopen("GdeBiblio.txt", "r");
  livre->num = GetEntier(fichier);
  GetChaine(fichier,30,livre->auteur);
  GetChaine(fichier,30,livre->titre);
}

void affichage(int n)
{

  FILE *fichier = fopen("GdeBiblio.txt", "r");
  int i;

  for(i = 0; i < n; i++){
    AfficheLine(fichier); 
  }
  
}


int main()
{
  s_livre livre;
  init_livre(&livre);
  cellule *biblio;
  /* biblio = (cellule *)malloc(sizeof(void *));
     biblio = NULL;*/
  /*remplir(&livre);*/
  printf("%s \n",livre.auteur);
  affichage(10);
  return 0;
}

