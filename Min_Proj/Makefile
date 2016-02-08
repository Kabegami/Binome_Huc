all : livre.o biblio.o
	gcc -o biblio livre.o biblio.o

livre.o : livre.c livre.h
	gcc -c livre.c

biblio.o : biblio.c livre.h
	gcc -c biblio.c
