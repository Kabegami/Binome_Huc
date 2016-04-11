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

void enfile(File *f, Sommet *s)
{
  Elem_file *new = (Elem_file *)malloc(sizeof(Elem_file));
  new->s = s;
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

Sommet* defile(File *f)
{
  if (!(est_file_vide(f))){
    Elem_file *tmp = f->debut;
    Sommet *s = f->debut->s;
    if (f->debut->suiv != NULL){
      f->debut->suiv->prec = NULL;
      f->debut = f->debut->suiv;
    }
    else{
      f->debut = NULL;
      f->fin = NULL;
    }
    f->nb--;
    free(tmp);
    return s;
  }
  return NULL;
}

void affiche_file(File *f){
  Elem_file *cour =  f->debut;
  while (cour != NULL){
    printf("sommet %d\n", cour->s->num);
    cour = cour->suiv;
  }
}
