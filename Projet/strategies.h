#include "graphe.h"

int plus_court_chemin(Grille *G,Graphe_zone *Graphe, Graphe_bordure *bordure, Sommet* racine, Sommet **tab);

int max_bordure(Grille *G, int **M, int aff);

int max_voisin_bordure(Grille *G, int **M, int aff);

int chemin(Grille *G, int **M, int aff);

int parcour_chemin(Grille *G, int **M, int aff, Graphe_zone **Graphe,Sommet *depart, Graphe_bordure **bordure);

int max_esperance(Grille *G, int **M, int aff);
