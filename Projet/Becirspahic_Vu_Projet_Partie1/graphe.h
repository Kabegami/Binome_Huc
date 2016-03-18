#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"

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

  Cellule_som *sommet_adj; /* Liste des aretes pointeurs sur les sommets adj */
};


typedef struct graphe_zone{
  int nbsom;    /* Nombre de sommets dans le graphe */
  Cellule_som *som;  /* Liste chainee des sommets du graphe */
  Sommet ***mat;     /* Matrice de pointeurs sur les sommets indiquant
			a quel sommet appartient une case (i,j) de la grille */
} Grapĥe_zone;
