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
  for(i = 0; i < t.taille;i++){
    if (t.T[i] == NULL)
      new[i] = NULL;
    else
      {
	new[i] = t.T[i];
      }
  }
  return new;
}

void augmenter_taille(tableHachage *t)
{
  cell_t **temp = copy_T(*t,t->taille *2);
  free(t->T);
  t->taille = t->taille *2;
  t->T = temp;
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
  t->nbElem++;
}

void insertion_table2(tableHachage *t, cell_t *cel)
{
  
/* Ici, nous faisons le choix de contenir que les livre d'un unique auteur dans une case de notre table. Ce choix nous permet d'avoir une recherche des livres d'un auteur et  une recherche d'un livre avec le paramètre (auteur,titre) très rapide.
       De plus, on peut considérer qu'en moyenne les auteur redigent un nombre de livre plus ou moins comparable ainsi notre table seras remplis de manirère relativement homogène */
  
  int case_table = fonctionHachage(cel->clef,t->taille);
  /* on augmente la taille de notre table */
  if (t->nbElem == t->taille)
    augmenter_taille(t);
  
  if ((t->T)[case_table] == NULL){
    inserer_debut_l(&((t->T)[case_table]),cel->data);
    t->nbElem++;
  }
  else{
    if ((t->T)[case_table]->data->auteur == cel->data->auteur)
      inserer_debut_l(&((t->T)[case_table]),cel->data);
    else{
	/* comme on a vérifier qu'il existait au moins une case de libre notre fonction recursive s'arrete forcement */
	cel->clef++;
	insertion_table2(t,cel);
      }
  }
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
  cell_t *cell;
  
  
  for(i = 0; i < n; i++){
    num = GetEntier(f);

    auteur = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, auteur);

    titre = (char*)malloc(25*sizeof(char));
    GetChaine(f, 25, titre);

    SkipLine(f);

    livre = (s_livre*)malloc(sizeof(s_livre));
    *livre = init_livre(titre,auteur,num);
    cell = creer_cellule_l(livre);
    insertion_table2(t, cell);
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
  return t.T[case_tab];
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
  int f = fonctionHachage(fonctionClef("toto"),10);
  cell_t *cel =creer_cellule_l(&l);
  insertion_table2(&t,cel);
  afficher_table(t);
  suppression_t(&t,&l);
  afficher_table(t);
  augmenter_taille(&t);
  printf("%d \n",t.taille);
  afficher_table(t);
  printf("%d %d \n", i, f);
  return 0;
}

