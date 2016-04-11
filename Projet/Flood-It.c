#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "version_rec.h"
#include "version_imp.h"
#include "version_rapide.h"
#include "strategies.h"
 
 
int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine;
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 


  if(argc!=5){
    printf("usage: %s <dimension nb_de_couleurs niveau_difficulte graine>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);

  /* Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  
  
  int choix, aff, nbCoups;
  int fin = 0;

  do{
    printf("----------------------Menu----------------------\n");
    printf("0 - SANS affichage graphique\n");
    printf("1 - AVEC affichage graphique\n");
    printf("3 - Quitter\n\n");
    printf("Note: si la dimension entrée est inférieure à 6\non peut visualiser les étapes du jeu et le graphe\nau format texte.\n");

    printf("Choix : ");
    scanf("%d", &aff);
  } while (aff != 0 && aff != 1 && aff != 3);
  
  if (aff == 3) return 0;
  if (dim < 6) aff = 2;

  printf("\n----------------------Menu----------------------\n");
  printf("1 - Version recursive\n");
  printf("2 - Version imperative\n");
  printf("3 - Version rapide\n");
  printf("4 - Max-bordure\n");
  printf("5 - Parcours en largeur\n");

  printf("Strategie : ");
  scanf("%d", &choix);
  printf("\n-------------------------------------------------\n");
  
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
    //Affichage de la grille

    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }
    switch(choix){
    case 1:
      temps_initial = clock();
      
      nbCoups = sequence_aleatoire_rec_2(M,G,G->dim,aff);
      
      temps_final = clock();
      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
      printf("Nombre de coups:%d\nTemps CPU:%f\n", nbCoups, temps_cpu);

      temps_initial = 0;
      temps_final = 0;
      temps_cpu = 0.0;
      
      break;

    case 2:
      temps_initial = clock();
      
      nbCoups = sequence_aleatoire_imp(M,G,G->dim,aff);
      
      temps_final = clock();
      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
      printf("Nombre de coups:%d\nTemps CPU:%f\n", nbCoups, temps_cpu);

      temps_initial = 0;
      temps_final = 0;
      temps_cpu = 0.0;
      
      break;

    case 3:
      //FILE *f1 = fopen("01_rec_num.txt", "a+");

      //temps calcul et l'écrit dans un fichier
      temps_initial = clock();
      
      nbCoups = sequence_aleatoire_rapide(M,G,aff);
      
      temps_final = clock();
      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
      printf("Nombre de coups:%d\nTemps CPU:%f\n", nbCoups, temps_cpu);

      temps_initial = 0;
      temps_final = 0;
      temps_cpu = 0.0;
      //  fclose(f1);
      break;

    case 4:
      temps_initial = clock();
      
      nbCoups = max_bordure(G, M, aff);
      
      temps_final = clock();
      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
      printf("Nombre de coups:%d\nTemps CPU:%f\n", nbCoups, temps_cpu);

      temps_initial = 0;
      temps_final = 0;
      temps_cpu = 0.0;

      break;

    case 5:
      temps_initial = clock();
      
      nbCoups = chemin(G,M,aff);
      
      temps_final = clock();
      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
      printf("Nombre de coups:%d\nTemps CPU:%f\n", nbCoups, temps_cpu);

      temps_initial = 0;
      temps_final = 0;
      temps_cpu = 0.0;

      break;
    default:
      printf("Erreur de saisie\n");
      return 1;
      break;
    }
    
    Grille_redessine_Grille();

    if (aff != 0)
      Grille_attente_touche();
 
    Grille_ferme_fenetre();

    Grille_free(&G);
  return 0;
}
