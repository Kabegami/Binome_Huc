#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"

/* fonction recursive, qui definit la zone de la couleur de la case i,j en parametre qui utilise met la couleur a -1, dans les cases deja visite pour eviter une boucle infinie et qui remet la bonne couleur a la fin */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L);
