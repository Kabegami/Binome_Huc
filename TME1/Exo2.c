#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
  int *tab;
  int taille;
}tableau;

tableau alloue_tableau(int n)
{
  tableau t1;
  t1.tab = (int *)malloc(n*sizeof(int));
  t1.taille = n;

  return t1;
}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

void remplir_tableau(tableau *ta, int v)
{
  int i;
  for(i = 0; i < ta->taille; i++){
    (ta->tab)[i] = rand_a_b(0,v);
  }
}

void afficherTab(tableau *tab)
{
  int i;
  for (i = 0; i < tab->taille; i++)
    printf("%d\n", (tab->tab)[i]);
}

int somme_car(tableau tab)
{
  int i;
  int somme = 0;
  
  for(i = 0; i < (tab.taille)-1;i++){ 
    somme += ((tab.tab[i+1]) - (tab.tab[i])) * ((tab.tab[i+1]) - (tab.tab[i]));
    printf("%d \n",somme);
  }
  return somme;
}


int main(){
  int s;
  tableau tab = alloue_tableau(100);
  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu;
  
  remplir_tableau(&tab,10);
  /*afficherTab(&tab);*/
  
  temps_initial = clock();
  
  s = somme_car(tab);
  /*printf("%d \n",somme_car(tab));*/
  
  temps_final = clock();
  temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
  printf("%d %f ", 100, temps_cpu);
  


  return 0;
}


