#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "biblio.h"
#include "table_hachage.h"

void afficheMenu(){
  
  printf("RAPPEL : les livres sont numerotes a partir de 0.\n");
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
  char *saisie;
  int numero;
  saisie = (char*)malloc(sizeof(char)*25);
  	
  char *titre;	
  char *auteur;
  Liste biblio;

  clock_t temps_initial;
  clock_t temps_final;
  double temps_cpu;

  int nbEntrees;

  printf("\n==============Choix de la structure=============\n");
  printf("1 - Liste chainee\n");
  printf("2 - Table de hachage\n");
  scanf("%d", &choix);


  /* =========== choix d'une liste doublement chainee pour la bibliotheque =========== */
  
  if(choix == 1){
    choix = 0;
    
    /* cree une bibliotheque et y ajoute des livres */

    init_liste(&biblio);
    
    printf("Insérer combien de livres dans la bibliotheque ? ");
    scanf("%d", &nbEntrees);
    lecture(&biblio, nbEntrees);

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
	  scanf("%d", &numero);

	  /* FILE *f1 = fopen("01_rec_num.txt", "a+");

	  // temps calcul et l'écrit dans un fichier
	  temps_initial = clock();*/
	  
	  c = rechercher_numero(biblio, numero);

	  /*temps_final = clock();
	  temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
	  fprintf(f1, "%d %f \n", nbEntrees, temps_cpu);

	  temps_initial = 0;
	  temps_final = 0;
	  temps_cpu = 0.0;
	  fclose(f1); */
	  
	
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
	
	  /*FILE *f2 = fopen("01_rec_titre.txt", "a+");

	  // temps calcul et l'écrit dans un fichier
	  temps_initial = clock();*/
	
	  c = rechercher_titre(biblio, saisie);
	  
	  /* temps_final = clock();
	  temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

	  fprintf(f2, "%d %f \n", nbEntrees, temps_cpu);
	
	  temps_initial = 0;
	  temps_final = 0;
	  temps_cpu = 0.0;
	  fclose(f2); */
	
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

	  /* FILE *f3 = fopen("01_rec_auteur.txt", "a+");

	  // temps calcul et l'écrit dans un fichier
	  temps_initial = clock();*/
	
	  Liste l_auteur =  rechercher_livres_auteur(biblio, saisie);

	  /* temps_final = clock();
	  temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

	  fprintf(f3, "%d %f \n", nbEntrees, temps_cpu);
	
	  temps_initial = 0;
	  temps_final = 0;
	  temps_cpu = 0.0;
	  fclose(f3); */
	
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
	  for(i = 0; auteur[i] != '\0'; i++)
	    auteur[i] = toupper(auteur[i]);
	
	  s_livre ajout = init_livre(titre, auteur, (biblio.debut->livre.num)+1);

	  printf("Inserer au debut de la bibliotheque ? (o/n)\n");
	  GetChaine(stdin, 25, saisie);

	  if(strcasecmp(saisie, "o") == 0){
	    inserer_debut(&biblio, ajout);
	    printf("Livre ajoute avec succes.\n");
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
	      printf("Livre ajoute avec succes.\n");
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
  }





  


    /* =========== choix d'une table de hachage pour la bibliotheque =========== */

  else{ 
    if(choix == 2){
      
      tableHachage t;
      t = initTableHachage(10);
      cell_t *cell;
      
      choix = 0;
      printf("Insérer combien de livres dans la bibliotheque ? ");
      scanf("%d", &nbEntrees);
      lecture_hachage(&t, nbEntrees);

      /* tant que le choix 0 n'a pas ete fait, on affiche le menu */
      while (!fin){
	printf("Nombre de livres dans la bibliotheque : %d\n", t.nbElem);
	afficheMenu();
	scanf("%d", &choix);

	switch(choix)
	  {

	    /* recherche par numero */
	  case 1:
	    printf("Veuillez entrer le numero du livre a rechercher : ");
	    scanf("%d", &numero);

	    /* FILE *f21 = fopen("02_rec_num.txt", "a+");

	    // temps calcul et l'écrit dans un fichier
	    temps_initial = clock();*/
	  
	    cell = recherche_num_t(t, numero);
	  
	    /*temps_final = clock();
	      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
	      fprintf(f21, "%d %f \n", nbEntrees, temps_cpu);

	      temps_initial = 0;
	      temps_final = 0;
	      temps_cpu = 0.0;
	      fclose(f21); */
	  
	
	    if(cell == NULL){
	      printf("Livre non trouve\n");
	    }
	    else{
	      afficher_livre_l(cell);
	      cell = NULL;
	    }
	
	    printf("\n");
	    break;

	    /* recherche par titre */
	  case 2:
	    printf("Veuillez entrer le titre du livre a rechercher : ");
	    GetChaine(stdin, 25, saisie);
	
	    /*FILE *f22 = fopen("02_rec_titre.txt", "a+");

	    // temps calcul et l'écrit dans un fichier
	    temps_initial = clock();*/
	
	    cell = recherche_titre_t(t, saisie);
	  
	    /*temps_final = clock();
	      temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

	      fprintf(f2, "%d %f \n", nbEntrees, temps_cpu);
	
	      temps_initial = 0;
	      temps_final = 0;
	      temps_cpu = 0.0;
	      fclose(f2); */
	
	    if(cell == NULL)
	      printf("Livre non trouve\n");
	    else{
	      afficher_livre_l(cell);
	      cell = NULL;
	    }
	    
	
	    printf("\n");
	    break;


	    // A REVOIR //
	    /* rechercher par auteur, affiche une liste de livres */
	  case 3:
	    printf("Veuillez entrer le nom de l'auteur a rechercher : ");
	    GetChaine(stdin, 25, saisie);

	    /* FILE *f23 = fopen("02_rec_auteur.txt", "a+");

	    // temps calcul et l'écrit dans un fichier
	    temps_initial = clock();*/
	
	    cell =  livre_meme_auteur_t(t, saisie);

	    /* temps_final = clock();
	       temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

	       fprintf(f3, "%d %f \n", nbEntrees, temps_cpu);
	
	       temps_initial = 0;
	       temps_final = 0;
	       temps_cpu = 0.0;
	       fclose(f3); */
	
	    if(cell == NULL)
	      printf("Livre non trouve\n");
	    else{
	      afficher_liste_l(cell);
	      cell = NULL;
	    }
	
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
	    for(i = 0; auteur[i] != '\0'; i++)
	      auteur[i] = toupper(auteur[i]);

	    s_livre *ajout;
	    ajout = (s_livre*)malloc(sizeof(s_livre));
	    *ajout = init_livre(titre, auteur, (t.nbElem));
	    
	    insertion_table(&t,ajout);
	    printf("Livre ajoute avec succes.\n");
	    printf("\n");
	    break;

	    // A REVOIR //
	    /* supprimer un ouvrage */
	  case 5:
	    printf("Veuillez saisir le titre de l'ouvrage a supprimer : ");
	    GetChaine(stdin, 25, saisie);
	    //suppression_t(t, saisie);
	    
	    printf("\n");
	    break;

	    /* recherche les livres au moins en double, affiche une liste de livres */
	  case 6:
	    printf("Recherche de doublons dans la bibliotheque\n");
	
	    cell = recherche_doublon_t(t);

	    if(cell == NULL)
	      printf(("Pas de doublons dans la bibliotheque\n"));
	    else{
	      afficher_liste_l(cell);
	      cell = NULL;
	    }

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
  }else{
    printf("Erreur de saisie\n");
  }
    return 0;
}
}
