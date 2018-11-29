all: main.o tools.o
	gcc main.o -lm -o main
	gcc tools.o -o tools
	
main.o: main.c
	gcc -c main.c -Wall -pedantic -o main.o

tools.o: tools.c
	gcc -c tools.c -Wall -pedantic -o tools.o
