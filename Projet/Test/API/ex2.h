#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Liste_case.h"

struct zone{
  int dim;
  int nbcl;

  Liste_case Lzsg; /* liste des cases de la zone */
  Liste_case *B; /* tableau de liste de cases de la bordure */
  int **App; /* tableau a double entree des appartenances */
};

typedef struct zone S_Zsg;

S_Zsg init_zsg(int dim, int nbcl, Liste_case Lzsg, Liste_case *B, int **App);

int ajoute_zsg(S_Zsg *zone, int i, int j);
