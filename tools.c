#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ChercherDansTableau(char * src, char ** tab){
	int taille = sizeof(tab)/sizeof(tab[0]);
	for(int i = 0; i < taille; i++){
		if(tab[i]==src){
			return i;
		}
	}
	return -1;
}