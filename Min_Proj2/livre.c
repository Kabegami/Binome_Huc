#include <stdio.h>
#include <stdlib.h>
#include "livre.h"
#include "entree_sortie.h"

s_livre init_livre(char *titre, char *auteur, int num)
{
  s_livre l;
  l.titre = titre;
  l.auteur = auteur;
  l.num = num;
  return l;
}
