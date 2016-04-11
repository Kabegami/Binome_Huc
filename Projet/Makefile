all : Flood-It.o API_Grille.o API_Gene_instance.o Liste_case.o version_rec.o version_imp.o version_rapide.o graphe.o file.o
	gcc -o interface Flood-It.o API_Grille.o API_Gene_instance.o Liste_case.o version_rec.o version_imp.o version_rapide.o graphe.o file.o -lSDL

Flood-It.o : Flood-It.c API_Grille.h API_Gene_instance.h
	gcc -c -lSDL Flood-It.c

API_Grille.o : API_Grille.c API_Grille.h
	gcc -c -lSDL API_Grille.c

API_Gene_instance.o : API_Gene_instance.c API_Gene_instance.h
	gcc -c -lSDL API_Gene_instance.c

Liste_case.o : Liste_case.c Liste_case.h
	gcc -c -lSDL Liste_case.c

version_rec.o : version_rec.c version_rec.h
	gcc -c -lSDL version_rec.c

version_imp.o : version_imp.c version_imp.h version_rec.h
	gcc -c -lSDL version_imp.c

version_rapide.o : version_rapide.c version_rapide.h
	gcc -c -lSDL version_rapide.c

graphe.o : graphe.c graphe.h file.h
	gcc -c -lSDL graphe.c file.h

file.o : file.c file.h graphe.h
	gcc -c file.c graphe.h
