#ifndef FILE_H
#define FILE_H

typedef struct e_file{
  int i;
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

void enfile(File *f, int i);

int defile(File *f);


#endif
