#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Liste_case.h"

struct zone{
  int dim;
  int nbcl;

  Liste Lzsg; /* liste des cases de la zone */
  Liste *B; /* tableau de liste de cases de la bordure */
  int **App; /* tableau a double entree des appartenances */
};

typedef struct zone S_Zsg;

S_Zsg init_zsg(int dim, int nbcl, Liste Lzsg, Liste *B, int **App);

int ajoute_zsg(int **M, S_Zsg *zone, int i, int j);

int ajoute_bordure(int **M, S_Zsg *zone, int i, int j);

int appartient_zsg(int **M, S_Zsg *zone, int i, int j);

int appartient_bordure(int **M, S_Zsg *zone, int i, int j);

int agrandit_zsg(int **M, S_Zsg *zone, int cl, int k, int l);

int sequence_aleatoire_rapide(int **M, Grille *G, int aff);
