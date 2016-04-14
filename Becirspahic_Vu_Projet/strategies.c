#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

int plus_court_chemin(Grille *G,Graphe_zone *Graphe, Graphe_bordure *bordure, Sommet* racine, Sommet **tab){
  Cellule_som *actu;
  int *visit = (int*)malloc(Graphe->nbsom*sizeof(int)); /* tableau visites */
  int *pere = (int*)malloc(Graphe->nbsom*sizeof(int));  /* tableau peres */
  int i,j,k;
  Sommet *cour;
  Sommet *cour_adj;
  File f;
  init_file(&f);

  for (i = 0; i < Graphe->nbsom; i++){
    visit[i] = -1;
    pere[i] = -1;
  }
  visit[racine->num] = 0;
  enfile(&f,racine);

  while (!(est_file_vide(&f))){
    cour = defile(&f);
    k = cour->num;
    //printf("defile %d\n",k);
    actu = cour->sommet_adj;
      while (actu != NULL){
	cour_adj = actu->sommet;
	j = actu->sommet->num;
	if (visit[j] == -1){
	  visit[j] = visit[k] + 1;
	  pere[j] = k;
	  enfile(&f,cour_adj);
	  //printf("enfile %d\n",j);
	}
	actu = actu->suiv;
      }
      //affiche_file(&f);
  }
  
  //printf("sommet | pere | visite\n");
  for (i = 0; i < Graphe->nbsom; i++){
    //printf("%d       ",i);
    if (pere[i] != -1)
      tab[i]->pere = tab[pere[i]];
    tab[i]->distance = visit[i];
    //printf("%d     ",pere[i]);
    // printf("%d\n",visit[i]);
    }
  return visit[Graphe->nbsom-1];
}

int max_bordure(Grille *G, int **M, int aff){
  Graphe_zone *Graphe = creer_graphe_zone(G, M);
  Graphe_bordure *bordure = creer_bordure(G, Graphe, 0);

  int max_cl;
  int nbCoups = 0;
  int cl_init = bordure->zsg->sommet->cl;
  int taille = 1;

  if(aff == 1){
    //Grille_attente_touche();
    Grille_redessine_Grille();
  }
  if(aff == 2){
    affiche_graphe(G, bordure);
    Grille_attente_touche();
    Grille_redessine_Grille();
  }
 
  while(taille < Graphe->nbsom){
    max_cl = max_couleur(G, bordure);
    actualise_bordure(max_cl, Graphe, bordure,&taille);
    peint_zsg(G, max_cl, bordure);
    nbCoups++;
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
  }
  printf("Couleur initiale : %d\n", cl_init);
  printf("Couleur finale : %d\n", bordure->zsg->sommet->cl);
  return nbCoups;
}



int max_voisin_bordure(Grille *G, int **M, int aff){
  Graphe_zone *Graphe = creer_graphe_zone(G, M);
  Graphe_bordure *bordure = creer_bordure(G, Graphe, 0);

  int max_cl;
  int nbCoups = 0;
  int cl_init = bordure->zsg->sommet->cl;
  int taille = 1;

  if(aff == 1){
    //Grille_attente_touche();
    Grille_redessine_Grille();
  }
  if(aff == 2){
    affiche_graphe(G, bordure);
    Grille_attente_touche();
    Grille_redessine_Grille();
  }
 
  while(taille < Graphe->nbsom){
    max_cl = max_voisin(G, bordure);
    actualise_bordure(max_cl, Graphe, bordure,&taille);
    peint_zsg(G, max_cl, bordure);
    nbCoups++;
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
  }
  printf("Couleur initiale : %d\n", cl_init);
  printf("Couleur finale : %d\n", bordure->zsg->sommet->cl);
  return nbCoups;
}


int chemin(Grille *G, int **M, int aff){
  Graphe_zone *Graphe = creer_graphe_zone(G, M);
  Graphe_bordure *bordure = creer_bordure(G, Graphe, 1);
  int min, max_cl, nbCoups;
  int i;
  int taille = 1;
  min = plus_court_chemin(G,Graphe, bordure, (Graphe->mat)[0][0],bordure->tab);
  i = min;
  
  //tableau contenant le chemin
  int *chemin = (int *)malloc((min+1)*sizeof(int));
  Sommet *actu = (bordure->tab)[Graphe->nbsom -1];
  while (actu->pere != NULL){
    chemin[i] = actu->num;
    actu = actu->pere;
    i--;
  }
  chemin[i] = actu->num;
  
  for(i = 0; i < min; i++){
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
    ajoute_liste_sommet(&(bordure->zsg),bordure->tab[chemin[i+1]]);
    actualise_bordure(bordure->tab[chemin[i+1]]->cl,Graphe,bordure,&taille);
    peint_zsg(G,bordure->tab[chemin[i+1]]->cl,bordure);
    nbCoups++;
  }
  printf("----------------------------------------\n");
  printf("Affichage de la zsg diagonale.\n");
  printf("Appuyez sur une touche pour continuer.\n");
  printf("----------------------------------------\n");
  Grille_attente_touche();

  while(!(bordure_vide(G,bordure))){
    max_cl = max_voisin(G, bordure);
    actualise_bordure(max_cl, Graphe, bordure,&taille);
    peint_zsg(G, max_cl, bordure);
    nbCoups++;
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
  }
  return nbCoups;
}

/* test strat perso --------------------------------*/

int iteration_chemin(Grille *G, int **M, int aff, Graphe_zone *Graphe, Graphe_bordure *bordure, int *chemin, int min, int nbCoups, int k, int l){
  Sommet *actu;
  int i,j;
  int taille = 1;
  for (j = 0; j < Graphe->nbsom; j++){
    bordure->tab[j]->pere = NULL;
    bordure->tab[j]->distance = 0;
  }
  min = plus_court_chemin(G,Graphe, bordure, (Graphe->mat)[k][l],bordure->tab);
  i = min;
  free(chemin);
  chemin = (int *)malloc((min+1)*sizeof(int));

  actu = (bordure->tab)[Graphe->nbsom -1];
  while (actu->pere != NULL){
    chemin[i] = actu->num;
    actu = actu->pere;
    i--;
  }
  chemin[i] = actu->num;
  
  for(i = 0; i < min; i++){
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
    ajoute_liste_sommet(&(bordure->zsg),bordure->tab[chemin[i+1]]);
    actualise_bordure(bordure->tab[chemin[i+1]]->cl,Graphe,bordure,&taille);
    peint_zsg(G,bordure->tab[chemin[i+1]]->cl,bordure);
    nbCoups++;
  }
  //printf("nbcoups interne %d\n", nbCoups);
  return nbCoups;
}

int cherche_differente_couleur(Grille *G, int **M, Graphe_zone *Graphe, Graphe_bordure *bordure){
  int i;
  while (Graphe->mat[i][0]->cl == Graphe->mat[i+1][0]->cl){
    if (i != G->dim-1){
      i++;
    }
  }
  return i;
}

int chemin2(Grille *G, int **M, int aff){
  Graphe_zone *Graphe = creer_graphe_zone(G, M);
  Graphe_bordure *bordure = creer_bordure(G, Graphe, 1);
  int min, max_cl, nbCoups;
  int i, k;
  int taille = 1;
  int *chemin;
  Sommet *actu;
  min = plus_court_chemin(G,Graphe, bordure, (Graphe->mat)[0][0],bordure->tab);
  i = min;
  
  //tableau contenant le chemin
  chemin = (int *)malloc((min+1)*sizeof(int));
  actu = (bordure->tab)[Graphe->nbsom -1];
  while (actu->pere != NULL){
    chemin[i] = actu->num;
    actu = actu->pere;
    i--;
  }
  chemin[i] = actu->num;
  
  for(i = 0; i < min; i++){
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
    ajoute_liste_sommet(&(bordure->zsg),bordure->tab[chemin[i+1]]);
    actualise_bordure(bordure->tab[chemin[i+1]]->cl,Graphe,bordure,&taille);
    peint_zsg(G,bordure->tab[chemin[i+1]]->cl,bordure);
    nbCoups++;
  }
  int nv_cl;
  nv_cl = cherche_differente_couleur(G, M, Graphe, bordure);
  nbCoups = iteration_chemin(G, M, aff, Graphe, bordure, chemin, min, nbCoups, nv_cl, 0);
    
  printf("----------------------------------------\n");
  printf("Affichage de la zsg diagonale.\n");
  printf("Appuyez sur une touche pour continuer.\n");
  printf("----------------------------------------\n");
  Grille_attente_touche();

  while(!(bordure_vide(G,bordure))){
    max_cl = max_couleur(G, bordure);
    actualise_bordure(max_cl, Graphe, bordure,&taille);
    peint_zsg(G, max_cl, bordure);
    nbCoups++;
    if(aff == 1){
      //Grille_attente_touche();
      Grille_redessine_Grille();
    }
    if(aff == 2){
      affiche_graphe(G, bordure);
      Grille_attente_touche();
      Grille_redessine_Grille();
    }
  }
  return nbCoups;
}
