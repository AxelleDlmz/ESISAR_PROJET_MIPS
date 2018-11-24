all: main.o tools.o
	gcc -o main main.o
	
main.o: main.c
	gcc -c main.c -Wall -pedantic -o main.o

tools.o: tools.c
	gcc -c tools.c -Wall -pedantic -o tools.o
