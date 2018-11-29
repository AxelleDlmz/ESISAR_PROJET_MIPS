#Makefile Projet Mips
all: main.o tools.o
	gcc main.o tools.o -lm -o main
	
main.o: main.c
	gcc -c main.c -ansi -Wall -pedantic -o main.o

tools.o: tools.c tools.h
	gcc -c tools.c -ansi -Wall -pedantic -o tools.o
