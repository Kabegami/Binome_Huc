#include <stdio.h>
#include <stdlib.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Liste_case.h"
#include "file.h"
#ifndef graphe_h
#define graphe_h

typedef struct sommet Sommet;

/* Element d'une liste chainee de pointeurs sur Sommets */
typedef struct cellule_som{
  Sommet *sommet;
  struct cellule_som *suiv;
} Cellule_som;

struct sommet{
  int num;  /* Numero du sommet (sert uniquement a l'affichage) */
  int cl;   /* Couleur d'origine du sommet-zone */
  Liste cases;     /* Listes des cases du sommet-zone */
  int nbcase_som;  /* Nombre de cases de cette liste */
  int marque;      /* 0 si dans Zsg, 1 dans bordure, 2 non visite */

  Cellule_som *sommet_adj; /* Liste des aretes pointeurs sur les sommets adj */
  int distance ; /* Nombre d’aretes reliant ce sommet a la racine
		    du parcours en largeur */
  Sommet* pere;  /* Pere du sommet dans l’arborescence du parcours
		    en largeur */
};


typedef struct graphe_zone{
  int nbsom;    /* Nombre de sommets dans le graphe */
  Cellule_som *som;  /* Liste chainee des sommets du graphe */
  Sommet ***mat;     /* Matrice de pointeurs sur les sommets indiquant
			a quel sommet appartient une case (i,j) de la grille */  
}Graphe_zone;


typedef struct graphe_bordure{
  int *taille; // tableau de int 
  Cellule_som **liste; /* Liste chainee des sommets par couleur */
  Cellule_som *zsg;    /* Sommet de la Zsg */
  Sommet **tab; //tableau de pointeurs sur des sommets(qui contient tous les sommets de notre plateau)
}Graphe_bordure;

#endif
