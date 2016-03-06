#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "Liste_case.h"

/* fonction recursive, qui definit la zone de la couleur de la case i,j en parametre qui  met la couleur a -1 dans les cases deja visitees pour eviter une boucle infinie et qui remet la bonne couleur a la fin */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L)
{
  int couleur = M[i][j];
  //printf("couleur = %d\n", M[i][j]);
  //printf("%d\n", M[i][j]);
  //printf("%d\n", M[i+1][j]);
  Elnt_liste *actu;
  ajoute_en_tete(L,i,j);
  (*taille)++;

  while(M[i][j] == couleur){
    M[i][j] = -1;

  /* case de droite */
  if(i != (dim-1) && M[i+1][j] == couleur)
    {
      //printf("droite, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i+1,j,taille,L);
    }

  /* case du bas */
  if (j != (dim-1) && M[i][j+1] == couleur)
    {
      //printf("bas, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i,j+1,taille,L);
    }

  /* case de gauche */
  if (i != 0 && M[i-1][j] == couleur)
    {
      //printf("gauche, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i-1,j,taille,L);
    }

  /* case du haut */
  if(j != 0 && M[i][j-1] == couleur)
    {
      //printf("haut, taille = %d\n", *taille);
      trouve_zone_rec(M,dim,i,j-1,taille,L);
    }
  }
}

/* on stocke la couleur initiale avant de lancer notre fonction trouve_zone_rec puis apres avoir obtenu la zone on la recolorise a l aide de cette fonction 

   ! Attention ! On ne peut pas appeller peint et recherche_zone dans une fonction reccursive ensemble, mais je n en connais pas la raison */
void peint(Grille *G, int couleur, int **M, Liste *L)
{
  Elnt_liste *actu;
  actu = *L;
  while(actu != NULL){
    M[actu->i][actu->j] = couleur;
    Grille_attribue_couleur_case(G,actu->i,actu->j,M[actu->i][actu->j]);
    actu = actu->suiv;
  }
}


/*test*/

/* joue avec une couleur aleatoire en appelant la fonction trouve_zone_rec et retourne le nombre de coups necessaires pour gagner
aff est un entier indiquant si il faut reafficher la grille ou non
nbcouleur est le nombre de changement de couleur et notre valeur de retour
*/
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){

  srand(time(NULL));
  int nbCoups = 0;
  printf("nbcl = %d\n", nbcl);
  
  /* On definit Zsg, la zone contenant la case situee en haut a gauche */
  Liste L;
  init_liste(&L);
  int taille = 1;
  int new_couleur;
  int couleur = M[0][0];
  trouve_zone_rec(M, dim, 0, 0, &taille, &L);
  printf("Couleur Zsg : %d \n",couleur);
  affiche_liste(&L,M);

  /* selectionne une couleur tant que la grille contient plus d'une couleur  */
  do{
    new_couleur = (int)(rand()%(nbcl));

    /* si la couleur selectionnee est differente de la couleur de Zsg */
    if(new_couleur != couleur){
      couleur = new_couleur;
      peint(G,couleur,M,&L);
      /* on peint toute les cases avec la nouvelle couleur, puis on effectue une nouvelle recherche afin de voir si notre zone possede de nouvelles cases */ 
      detruit_liste(&L);
      taille = 0;
      printf("Couleur Zsg : %d\n", couleur);
      // printf("Couleur initiale : %d \n", M[i][j]);
      trouve_zone_rec(M,dim,0,0,&taille,&L);
      peint(G,couleur,M,&L);
      // printf("Couleur finale : %d \n",M[i][j]);
      printf("taille = %d \n",taille);
      affiche_liste(&L,M);

      //nbcl--;
      /* Pour la decrementation, je propose de dire que notre fonction s arrete quand notre zone partant de 0,0 est de taille = dim*dim */
      printf("nbcl = %d\n", nbcl);

      if(aff == 1){
      Grille_redessine_Grille();
      Grille_attente_touche();
      nbCoups++;
      }
    }
  }while(taille != dim*dim);
  
  printf("nbCoups = %d\n", nbCoups);
  return nbCoups;
}

int* initialise_tab_couleur(int nb_couleur)
{
  int i;
  int *tab = (int *)malloc(nb_couleur*sizeof(int));
  for(i = 0; i < nb_couleur;i++)
    {
      tab[i] = 0;
    }
  return tab;
}

int cpt_couleur(int *tab, int nb_couleur)
{
  int i;
  int cpt = 0;
  for(i = 0; i < nb_couleur;i++){
    if (tab[i] != 0)
      cpt++;
  }
  return cpt;
}

void afficher_tab(int *tab, int taille)
{
  int i;
  for(i = 0;i < taille; i++)
    printf("%d \n",tab[i]);
}

void nb_couleur_initiales(int **tab, int **M, int dim)
{
  int i,j;
  int valeur;
  for(i = 0; i < dim;i++){
      for(j = 0; j < dim;j++){
	valeur = M[i][j];
	(*tab)[valeur]++;
      }
  }
}
  
int sequence_aleatoire_rec_2(int **M, Grille *G, int dim, int aff){
  int *tab = initialise_tab_couleur(G->nbcl);
  nb_couleur_initiales(&tab,M,G->dim);
  afficher_tab(tab,G->nbcl);
  int nbCoups = 0;
  srand(time(NULL));
 /* On definit Zsg, la zone contenant la case situee en haut a gauche */
  Liste L;
  init_liste(&L);
  int taille = 0;
  int new_couleur;
  int couleur = M[0][0];
  int nbcl = G->nbcl;
  trouve_zone_rec(M, dim, 0, 0, &taille, &L);
  printf("Couleur initiale : %d \n",couleur);

  /* selectionne une couleur tant que la grille contient plus d'une couleur  */
  do{
    /* pb avec le rand car ce en changant la taille de nbcl, on n est pas sur que la couleur supprime du rand soit celle desire */
    do{
    new_couleur = (int)(rand()%(G->nbcl));
    }
    while(tab[new_couleur] == 0);

    /* si la couleur selectionnee est differente de la couleur de Zsg */
    if(new_couleur != couleur){
      tab[couleur] -= taille;
      couleur = new_couleur;
      tab[couleur] += taille;
      peint(G,couleur,M,&L);
      /* on peint toute les cases avec la nouvelle couleur, puis on effectue une nouvelle recherche afin de voir si notre zone possede de nouvelles cases */ 
      detruit_liste(&L);
      taille = 0;
      printf("Couleur Zsg : %d\n", couleur);
      // printf("Couleur initiale : %d \n", M[i][j]);
      trouve_zone_rec(M,dim,0,0,&taille,&L);
      peint(G,couleur,M,&L);
      // printf("Couleur finale : %d \n",M[i][j]);
      printf("taille = %d \n",taille);
      affiche_liste(&L,M);
      nbcl = cpt_couleur(tab,G->nbcl);
      nbCoups++;
      //nbcl--;
      /* Pour la decrementation, je propose de dire que notre fonction s arrete quand notre zone partant de 0,0 est de taille = dim*dim */
      printf("nbcl = %d\n", nbcl);
      if(aff == 1){
      Grille_attente_touche();
      Grille_redessine_Grille();
      }
    }
  }while(nbcl != 1);
  
  printf("nbCoups = %d\n", nbCoups);
  return nbCoups;
}

