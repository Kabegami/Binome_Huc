#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2.c"
#include "Liste_case.h"

S_Zsg init_zsg(int dim, int nbcl, Liste_case Lzsg, Liste_case *B, int **App)
{
  S_Zsg zone;
  zone.dim = dim;
  zone.nbcl = nbcl;
  zone.Lzsg = Lzsg;
  zone.B = B;
  zone.App = App;
  return zone;
}

/* ajoute la case M[i][j] dans la zone et retourne 0 si la case n est pas en bordure */
int ajoute_zsg(S_Zsg *zone, int i, int j)
{
  int couleur;
  if (zone->App[i][j] < 0)
    return 0;
  couleur = M[i][j];
  ajoute_en_tete(zone->Lzsg,i,j);
  suppression_el(zone->B[couleur],i,j);
  return 1;
}
