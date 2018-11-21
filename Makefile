all : main.o hexa.o
	gcc main.o hexa.o -o main

main.o : main.c 
	gcc -c main.c -Wall -pedantic -o main.o

hexa.o : hexa.c hexa.h
	gcc -c hexa.c -Wall -pedantic -o hexa.o

