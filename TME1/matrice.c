#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Les structures \s */

typedef struct {
  int **tab;
  int taille;
}matrice;

/* Les fonction \f */

matrice alloue_matrice(int taille)
{
  matrice mat;
  int i;
  mat.tab = (int **) malloc(taille*sizeof(int * *));
  for(i = 0; i < taille;i++){
    (mat.tab)[i] = (int *)malloc(taille*sizeof(int *));
  }
  mat.taille = taille;
  return mat; 
}

void remplir_matrice(matrice *mat,int valeur)
{
  int i,j;
  srand(time(NULL));
  for(i = 0; i < mat->taille;i++){
    for(j = 0; j < mat->taille;j++){
      mat->tab[i][j] = (rand() % valeur);
    }
  } 
}

void afficher_matrice(matrice mat)
{
  int i,j;
  for(i = 0; i < mat.taille;i++){
    for(j = 0 ; j < mat.taille;j++){
      printf(" %d   ",(mat.tab)[i][j]);
    }
    printf(" \n");
  }
}

int dans_matrice(matrice mat, int valeur)
{
  int i,j;
  int cpt = 0;
  for(i = 0; i <mat.taille;i++){
    for(j = 0; j < mat.taille;j++){
      if (mat.tab[i][j] == valeur)
	cpt++;
    }
  }
  return cpt;
}

int valeur_identique(matrice mat)
{
  /* Complexite trop grande o(x²) */
  int i,j;
  int cpt;
  for(i = 0; i < mat.taille;i++){
    for(j = 0; j < mat.taille;j++){
      if (dans_matrice(mat, (mat.tab)[i][j]) > 1)
	return 1;
    }
  }
  return 0;
}

void remplir_tab(int tab[], int taille)
{
  int i;
  for(i = 0; i < taille; i++){
    tab[i] = 0;
  }
}

int verif(int tab[], int valeur)
{
  if (tab[valeur] >0) {
    return 1;
  }
  else{
    tab[valeur] += 1;
    return 0;
  }
}
int valeur_identique_rapide(matrice mat,int valeur)
{
  int tab[valeur + 1];
  remplir_tab(tab,valeur+1);
  int i,j;
  int b = 0;
  for(i = 0; i < mat.taille;i++){
    for(j = 0; j < mat.taille;j++){
      b += verif(tab,(mat.tab)[i][j]);
    }
  }
  if( !b){
    printf("La matrice ne possède pas de valeurs identiques \n");
    return 1;
  }
  else{
    printf("La matrice possède des valeurs identiques \n");
    return 0;
  }
}



/* Le main \m */

int main()
{
  matrice mat = alloue_matrice(2);
  int b;
  remplir_matrice(&mat,10);
  afficher_matrice(mat);
  b = valeur_identique_rapide(mat,10);
  return 0;
}
