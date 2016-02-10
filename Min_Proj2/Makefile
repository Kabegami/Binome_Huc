all : livre.o biblio.o entree_sortie.o
	gcc -o biblio livre.o entree_sortie.o biblio.o

livre.o : livre.c livre.h entree_sortie.h
	gcc -c livre.c

biblio.o : biblio.c livre.h entree_sortie.h
	gcc -c biblio.c

entree_sortie.o : entree_sortie.c
	gcc -c entree_sortie.c

