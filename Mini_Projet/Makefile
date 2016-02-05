all : entree_sortie.o biblio.o
	gcc -o biblio entree_sortie.o biblio.o

entree_sortie.o : entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

biblio.o : biblio.c entree_sortie.h
	gcc -c biblio.c
