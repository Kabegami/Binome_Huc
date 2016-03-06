all : Flood-It.o API_Grille.o API_Gene_instance.o Liste_case.o test.o test2.o
	gcc -o interface Flood-It.o API_Grille.o API_Gene_instance.o Liste_case.o test.o test2.o -lSDL

Flood-It.o : Flood-It.c API_Grille.h API_Gene_instance.h
	gcc -c -lSDL Flood-It.c

API_Grille.o : API_Grille.c API_Grille.h
	gcc -c -lSDL API_Grille.c

API_Gene_instance.o : API_Gene_instance.c API_Gene_instance.h
	gcc -c -lSDL API_Gene_instance.c

Liste_case.o : Liste_case.c Liste_case.h
	gcc -c -lSDL Liste_case.c

test.o : test.c test.h
	gcc -c -lSDL test.c

test2.o : test2.c test2.h test.h
	gcc -c -lSDL test2.c
