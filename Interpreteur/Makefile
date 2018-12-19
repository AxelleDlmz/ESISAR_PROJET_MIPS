all : memoire.o processeur.o
	gcc memoire.o
	gcc processeur.o -o processeur

processeur.o : memoire.h processeur.h
	gcc -c processeur.c -Wall -o processeur.o

memoire.o : memoire.h
	gcc -c memoire.c -Wall -o memoire.o

clear :
	rm *.o