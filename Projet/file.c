#include <stdlib.h>
#include <stdio.h>
#include "file.h"


void init_file(File *f)
{
  f->nb = 0;
  f->debut = NULL;
  f->fin = NULL;
}

int est_file_vide(File *f)
{
  if (f->debut == NULL || f->fin == NULL)
    return 1;
  else
    return 0;
}

void enfile(File *f, int i)
{
  Elem_file *new = (Elem_file *)malloc(sizeof(Elem_file));
  new->i = i;
  new->suiv = NULL;
  if (est_file_vide(f)){
    new->prec = NULL;
    f->debut = new;
  }
  else{
    new->prec = f->fin;
    f->fin->suiv = new;
  }
  f->fin = new;
  f->nb++;
}

int defile(File *f)
{
  if (!(est_file_vide(f))){
    Elem_file *tmp = f->debut;
    int i = f->debut->i;
    f->debut->suiv->prec = NULL;
    f->debut = f->debut->suiv;
    f->nb--;
    free(tmp);
    return i;
  }
  return -1;
}
