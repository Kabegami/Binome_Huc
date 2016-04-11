#ifndef FILE_H
#define FILE_H
#include "graphe.h"

typedef struct e_file{
  Sommet *s;
  struct e_file *prec;
  struct e_file *suiv;
} Elem_file;

typedef struct{
  int nb;
  Elem_file *debut;
  Elem_file *fin;
} File;

void init_file(File *f);

int est_file_vide(File *f);

void enfile(File *f, Sommet* s);

Sommet* defile(File *f);

void affiche_file(File *f);
  
#endif
