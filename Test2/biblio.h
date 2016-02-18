#include "livre.h"

typedef struct cellule{
  s_livre livre;
  struct cellule *suivant;
  struct cellule *prec;
}Cellule;

typedef struct{
  struct cellule *debut;
  struct cellule *fin;
  int nb;
}Liste;


void init_liste(Liste *b);

int est_vide(Liste b);

Cellule* creer_cellule(s_livre livre);

void lecture(Liste *b, int n);
  
void inserer_debut(Liste *b, s_livre livre);

void afficher_prem_livre(Liste biblio);

void afficher_livre(Cellule *c);

void afficher_biblio(Liste biblio);

Cellule* rechercher_numero(Liste b, int n);

Cellule* rechercher_titre(Liste b, char *chaine, char *auteur);

int rechercher_nombre_titre(Liste b, char *titre, char *auteur);

Liste rechercher_livres_auteur(Liste b, char *auteur);

void insertion_avant(Liste *b, s_livre l, char *titre);

void suppression(Liste *b, char *titre);

Liste doublon(Liste b);

