#include <stdio.h>
#include <stdlib.h>
#include "livre.h"
#include "entree_sortie.h"

typedef struct cellule{
  s_livre livre;
  struct cellule *suivant;
  struct cellule *prec;
}Cellule;

typedef struct {
  struct cellule *debut;
  struct cellule *fin;
}Biblio;

/* Comme il s'agit d'une liste simple, notre objet stockant notre bibliotèque est un pointeur de Cellule */

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
    printf("La bibliothèque est vide \n");
  else{
    printf("titre = %s \n",(biblio->livre).titre);
    printf("auteur = %s \n",(biblio->livre).auteur);
    printf("numero = %d \n",(biblio->livre).num);
  }
}



void lecture(Cellule **biblio, int n){

  FILE *f = fopen("GdeBiblio.txt", "r");

  int i;
  int num;
  char *auteur;
  char *titre;
  s_livre livre;
  
  
  for(i = 0; i <= n; i++){
    num = GetEntier(f);

    auteur = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, auteur);

    titre = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, titre);

    SkipLine(f);

    livre = init_livre(titre,auteur,num);
    Inserer(biblio,livre);
  }
}


/* lecture avec fscanf */
/*
void lecture2(int n){

  FILE *f = fopen("GdeBiblio.txt", "r");
 
  int i;
  int num;
  char *titre; /* sans le [25] on a quelque chose de bizarre */
/*char *auteur;
  
  for (i = 0;  i <= n; i++){
    fscanf(f, "%d %s %s ", &num, &auteur, &titre);
    printf("%d %s %s\n", num, &auteur, &titre);
    
  }
}

*/
/* lit une ligne du fichier et l'insère dans un livre */
/*
s_livre lecture3(){

  FILE *f = fopen("GdeBiblio.txt", "r");

  int i;
  int num;
  char *titre;
  char *auteur;
  s_livre l;

  fscanf(f, "%d %s %s ", &num, &auteur, &titre);
  // printf("%d %s %s\n", num, &auteur, &titre);

  l = init_livre(titre, auteur, num);
  printf("%d %s %s\n", l.num, l.auteur, l.titre);
  return l;
}
*/

int main(){

  Cellule *biblio = NULL;
  printf("Test fonction lecture\n");
  lecture(&biblio,10);
  printf("\n");
  afficher_prem_livre(biblio);
  
  /*
  printf("Test fonction lecture2\n");
  lecture2(10);
  printf("\n");

  printf("Test fonction lecture3\n");
  lecture3();
  printf("\n");
  */
  
  /*s_livre l = init_livre("Toto a la plage", "Raoul", 1);
  Cellule *biblio = NULL;
  Inserer(&biblio,l);
  afficher_prem_livre(biblio);*/
  return 0;
}
