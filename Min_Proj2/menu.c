#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"

/*void remplir_livre(s_livre l)
{
  FILE *f = fopen("GdeBiblio.txt","r"); 
  char *chaine1 = (char *)(malloc(30*sizeof(char)));
  char *chaine2 = (char *)(malloc(30*sizeof(char)));
  int i;
  int nb;
  for(i = 0; i < 3; i++){
    GetChaine(f,10,chaine1);
    GetChaine(f,10,chaine2);
    /* cast pour arriver à un int
    nb = GetEntier(f);
  }
  l = init_livre(chaine1,chaine2,nb);
}*/

void afficheMenu(){
  
  printf("\n-----------------------Menu-----------------------\n");
  printf("1 - Recherche d'un ouvrage par son numero\n");
  printf("2 - Recherche d'un ouvrage par son titre\n");
  printf("3 - Recherche de tous les livres d'un meme auteur\n");
  printf("4 - Insertion d'un nouvel ouvrage\n");
  printf("5 - Suppression d'un ouvrage\n");
  printf("6 - Recherche des ouvrages au moins en double\n");
  printf("0 - Quitter\n");
  printf("Choisissez une fonction : ");
   
}

int main(){

  int fin = 0;
  int choix;
  Cellule *c;
  char saisie[25];
  
  int num;	
  char *titre;	
  char *auteur;

  /* cree une bibliotheque et y ajoute des livres */
  Liste biblio;
  init_liste(&biblio);
  lecture(&biblio, 5000);

  /* tant que le choix 0 n'a pas ete fait, on affiche le menu */
  while (!fin){
    printf("Nombre de livres dans la bibliotheque : %d\n", biblio.nb);
    afficheMenu();
    scanf("%d", &choix);

    switch(choix)
      {

	/* recherche par numero */
      case 1:
	printf("Veuillez entrer le numero du livre a rechercher : ");
	int numero;
	scanf("%d", &numero);
	c = rechercher_numero(biblio, numero);
	
	if(c == NULL){
	  printf("Livre non trouve\n");
	}
	else{
	  afficher_livre(c);
	}
	
	printf("\n");
	break;

	/* recherche par titre */
      case 2:
	printf("Veuillez entrer le titre du livre a rechercher : ");
	GetChaine(stdin, 25, saisie);
	c = rechercher_titre(biblio, saisie);
	
	if(c == NULL)
	  printf("Livre non trouve\n");
	else
	  afficher_livre(c);
	
	printf("\n");
	break;

	/* rechercher par auteur, affiche une liste de livres */
      case 3:
	printf("Veuillez entrer le nom de l'auteur a rechercher : ");
	GetChaine(stdin, 25, saisie);
        Liste l_auteur =  rechercher_livres_auteur(biblio, saisie);
	
	if(est_vide(l_auteur))
	  printf("Livre non trouve\n");
	else
	  afficher_biblio(l_auteur);
	
	printf("\n");
	break;

	/* inserer un livre */
      case 4:
	titre = (char*)malloc(25*sizeof(char));
        auteur = (char*)malloc(25*sizeof(char));
	
	printf("Saisir le titre du livre (sans espaces) : ");
	GetChaine(stdin, 25, titre);

	printf("Saisir le nom de l'auteur (sans espaces) : ");
	GetChaine(stdin, 25, auteur);

	/* convertit le nom de l'auteur en majuscules */
	int i;
	while(auteur[i]){
	  toupper(auteur[i]);
	  i++;
	}

	s_livre ajout = init_livre(titre, auteur, (biblio.debut->livre.num)+1);
	  
	printf("Inserer au debut de la bibliotheque ? (o/n)\n");
	GetChaine(stdin, 25, saisie);

	if(strcasecmp(saisie, "o") == 0){
	  inserer_debut(&biblio, ajout);
	  printf("Livre ajoute avec succes\n");
	}
	else{
	  printf("Saisir le titre du livre avant lequel inserer le nouveau livre : ");
	  GetChaine(stdin, 25, saisie);
	  c = rechercher_titre(biblio, saisie) ;
	  if (c == NULL){
	    printf("Livre non trouve, arret de l'operation\n");
	  }
	  else{
	    insertion_avant(&biblio, ajout, saisie);
	    printf("Livre ajoute avec succes\n");
	  }
	  
	}

	printf("\n");
	break;

	/* supprimer un ouvrage */
      case 5:
	printf("Veuillez saisir le titre de l'ouvrage a supprimer : ");
	GetChaine(stdin, 25, saisie);
	suppression(&biblio, saisie);
	    
	printf("\n");
	break;

	/* recherche les livres au moins en double, affiche une liste de livres */
      case 6:
	printf("Recherche de doublons dans la bibliotheque\n");
	
	Liste d = doublon(biblio);

	if(est_vide(d))
	  printf(("Pas de doublons dans la bibliotheque\n"));
	else
	  afficher_biblio(d);

	printf("\n");
	break;

      case 0:
	printf("Fin du programme\n");

	fin = 1;

	printf("\n");
	break;

      default:
	printf("Erreur de saisie\n");
    }
  }
    return 0;
}
