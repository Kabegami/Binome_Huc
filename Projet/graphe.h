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
  int num;  /* Numero du sommet */
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
  int *taille; // tableau des tailles par couleur dans la bordure
  Cellule_som **liste; /* Liste chainee des sommets par couleur */
  Cellule_som *zsg;    /* Sommet de la Zsg */
  Sommet **tab; //tableau de pointeurs sur des sommets(qui contient tous les sommets de notre grille)
}Graphe_bordure;

void ajoute_liste_sommet(Cellule_som **liste,Sommet *s);

void detruire_liste_sommet(Cellule_som *liste);

int recherche_sommet(Cellule_som *liste, Sommet s);

void affiche_voisin(Sommet *s);

void affiche_sommet(Cellule_som *liste);

int adjacent(Sommet *s1, Sommet *s2);

void ajoute_voisin(Sommet *s1, Sommet *s2);

int est_arete(Sommet *s1, Sommet *s2);

Sommet* creer_sommet(int num, int cl,Liste l, int nbcase_som,int marque, Cellule_som *sommet_adj);

void actualise_mat(Graphe_zone *Graphe, Sommet *s);

void creer_arete(Graphe_zone *Graphe, Grille *G);

void affiche_graphe(Grille *G, Graphe_bordure *bordure);

Graphe_zone* creer_graphe_zone(Grille *G, int **M);

void actualise_voisin(Graphe_bordure *bordure, Cellule_som *s);

Graphe_bordure* creer_bordure(Grille *G, Graphe_zone *Graphe, int tout);

void actualise_bordure(int cl, Graphe_zone *Graphe, Graphe_bordure *bordure);

void peint_zsg(Grille *G, int cl, Graphe_bordure *bordure);

int max_couleur(Grille *G, Graphe_bordure *bordure);

int bordure_vide(Grille *G, Graphe_bordure *bordure);
  
#endif
