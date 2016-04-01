#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "version_rec.h"
#include "version_imp.h"
#include "version_rapide.h"
#include "graphe.h"
 
 
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

  int choix, aff;
  printf("===========Menu==========\n");
  printf("1 - AVEC affichage graphique\n");
  printf("2 - SANS affichage graphique\n");

  scanf("%d", &aff);
  
  printf("===========Menu==========\n");
  printf("1 - Version recursive\n");
  printf("2 - Version imperative\n");
  printf("3 - Version rapide\n");
  printf("4 - Graphe des zones\n");

  scanf("%d", &choix);
  
  switch(choix){
  case 1:
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
    //Affichage de la grille

    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }
     
    sequence_aleatoire_rec_2(M,G,G->dim,aff);
    
    Grille_redessine_Grille();
    
    Grille_attente_touche();
 
    Grille_ferme_fenetre();

    Grille_free(&G);
    break;

  case 2:
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

  

    //Affichage de la grille

    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    sequence_aleatoire_imp(M,G,G->dim,aff);
    
    Grille_redessine_Grille();

    Grille_attente_touche();
 
    Grille_ferme_fenetre();

    Grille_free(&G);
    break;

  case 3:
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
  
    //Affichage de la grille

    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    sequence_aleatoire_rapide(M,G,aff);
    
    Grille_redessine_Grille();

    Grille_attente_touche();
 
    Grille_ferme_fenetre();

    Grille_free(&G);
    
    break;

  case 4:
    Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
  
    //Affichage de la grille

    Grille_init(dim,nbcl, 500,&G);

    Grille_ouvre_fenetre(G);
    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    printf("%d %d \n",dim, G->dim);
    creer_graphe_zone(G, M);
    
    Grille_redessine_Grille();

    Grille_attente_touche();
 
    Grille_ferme_fenetre();

    Grille_free(&G);
   
    break;
    
  default:
    printf("Erreur de saisie\n");
  }
   

  return 0;
}
