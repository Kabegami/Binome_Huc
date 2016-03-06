#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Liste_case.h"

void trouve_zone_imp(int **M,int dim, int i, int j, int *taille, Liste *L);

int  sequence_aleatoire_imp(int **M,Grille *G,int dim, int aff);
