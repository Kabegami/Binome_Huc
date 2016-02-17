all : livre.o biblio.o  entree_sortie.o table_hachage.o liste.o
	gcc -o menu livre.o biblio.o entree_sortie.o table_hachage.o liste.o

livre.o : livre.c livre.h
	gcc -c livre.c

biblio.o : biblio.c livre.h
	gcc -c biblio.c

entree_sortie.o : entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

table_hachage.o : table_hachage.c table_hachage.h livre.h liste.h
	gcc -c table_hachage.c

liste.o : liste.c livre.h liste.h table_hachage.h
	gcc -c liste.c
