#include <stdio.h>
#include <stdlib.h>
#include "table_hachage.h"
#include <math.h>




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

cell_t ** copy_T(tableHachage t, int taille)
{
  cell_t **new;
  int i;
  new = (cell_t **)malloc(taille*sizeof(cell_t *));
  for(i = 0; i < taille;i++){
      new[i] = NULL;
  }
  return new;
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

void augmenter_taille(tableHachage *t)
{
  /* Cette fonction ne marche pas et n'est pas utilise, car je n ai pas pu la finir a temps. Elle etait supposee gerer le changement de taille en transferant le contenu de notre ancienne table de hachage dans la nouvelle avec la fonction de Hachage (clef, nouvelle_taille),  mais dans l'etat actuelle elle provoque une erreur de segmentation. Cette demarche avait pour but de permetre a l utilisateurs de choisir entre une table couteuse en memoire et rapide et vice versa */
  int i;
  int new_taille;
  int c;
  cell_t **temp = copy_T(*t,t->taille *2);
  s_livre *livre;
  cell_t *actu;
  cell_t *cel;
  
  /* Lors du changement de taille,comme la fonction Hachage depend de la taille de notre table, si on change celle ci les clefs associees aux auteurs vont changer, il faut donc changer de cases nos anciens livres */
  printf("debut augmenter_taille");
  new_taille = t->taille * 2;
  for(i = 0; i < t->taille;)
    {
      actu = t->T[i];
      if (actu != NULL)
	{
	  while(actu->suivant != NULL){
	    livre = t->T[i]->data;
	    c = fonctionHachage(fonctionClef(livre->auteur),new_taille);
	    inserer_debut_l(&temp[c],livre);
	    cel = actu->suivant;
	    actu = cel;
	    suppression_l(&t->T[i],livre->titre,livre->auteur);
         }
	  livre = t->T[i]->data;
	  c = fonctionHachage(fonctionClef(livre->auteur),new_taille);
	  inserer_debut_l(&temp[i],livre);
	  suppression_l(&t->T[i],livre->titre,livre->auteur);
	}
    }
  t->taille = t->taille *2;
  t->T = temp;
  printf("fin insertion taille");
}

void insertion_table(tableHachage *t, s_livre *livre)
{

  int clef = fonctionClef(livre->auteur);
  int case_table = fonctionHachage(clef,t->taille);
  /* Ici, on considère que les auteurs ecrivent de maniere plus ou moins equivalente, ainsi on augmente la taille du tableau quand en moyenne les listes de livre contiennent 10 livre pour eviter les collision */
  /*if (t->nbElem > t->taille * 10)
    augmenter_taille(t); */
  inserer_debut_l(&((t->T)[case_table]),livre);
  t->nbElem++;
 
}

/* lit n entrees et les insere dans la bibliotheque */
void lecture_hachage(tableHachage *t, int n)
{
  FILE *f = fopen("GdeBiblio.txt", "r");

  int i;
  int num;
  char *auteur;
  char *titre;
  s_livre *livre;
  
  
  for(i = 0; i < n; i++){
    num = GetEntier(f);

    auteur = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, auteur);

    titre = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, titre);

    SkipLine(f);

    livre = (s_livre*)malloc(sizeof(s_livre));
    *livre = init_livre(titre,auteur,num);
    insertion_table(t, livre);
  }
  fclose(f);
}

void afficher_table(tableHachage t)
{
  int i;
  cell_t *actu = t.T[0];
  for(i = 0; i < t.taille;i++){
    if (t.T[i] == NULL){
      printf("Case numero : %d ", i);
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

cell_t* recherche_num_t(tableHachage t, int numero)
{
  int i;
  cell_t *cell;
  for(i = 0; i < t.taille;i++){
    cell = recherche_num_l(t.T[i],numero);
    if (cell != NULL)
      return cell;
  }
  return NULL;
}


cell_t* recherche_titre_t(tableHachage t, char *titre)
{
  int i;
  cell_t *cell;
  for(i = 0; i < t.taille;i++){
    cell = recherche_titre_l(t.T[i],titre);
    if (cell != NULL)
      return cell;
  }
  return NULL;
}


cell_t* livre_meme_auteur_t(tableHachage t, char *auteur)
{
  int clef = fonctionClef(auteur);
  int case_tab = fonctionHachage(clef,t.taille);
  cell_t *liste_auteur = NULL;
  recherche_auteur_l(&liste_auteur,t.T[case_tab],auteur);
  return liste_auteur;
}

cell_t* recherche_doublon_t(tableHachage t)
{
  cell_t *liste = NULL;
  int i;
  for(i = 0; i < t.taille;i++) {
    recherche_doublon_l(t.T[i],&liste);
    }
  return liste;
}

void suppression_t(tableHachage *t,char *titre, char *auteur)
{
  int clef = fonctionClef(auteur);
  int case_tab = fonctionHachage(clef,t->taille);
  suppression_l(&(t->T[case_tab]),titre,auteur);
  t->nbElem--;
}
/*
int main(){
  tableHachage t = initTableHachage(10);
  int i = fonctionClef("toto");
  s_livre l = init_livre("toto","Raoul",3);
  s_livre l2 = init_livre("billy","Raoul",4);
  int f = fonctionHachage(fonctionClef("toto"),10);
  cell_t *cel =creer_cellule_l(&l);
  afficher_table(t);
  suppression_t(&t,&l);
  afficher_table(t);
  augmenter_taille(&t);
  printf("%d \n",t.taille);
  afficher_table(t);
  printf("%d %d \n", i, f);
  return 0;
}

*/
