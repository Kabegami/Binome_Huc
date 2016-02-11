all : livre.o biblio.o menu.o
	gcc -o menu livre.o biblio.o menu.o

livre.o : livre.c livre.h
	gcc -c livre.c

biblio.o : biblio.c livre.h
	gcc -c biblio.c

menu.o : menu.c livre.h biblio.h entree_sortie.h
	gcc -c menu.c
