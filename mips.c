#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#define TAILLE 100

int RecupCode(char * nomDuFichier){

	FILE * f = fopen(nomDuFichier,"r");
	char * res[TAILLE];
	char buff[TAILLE];
	int nombreDInstructions = 0;

	if(f == NULL){
		printf("%s %s\n", "ERREUR : Impossible de lire le fichier ", nomDuFichier);
		return -1;
	}

	while(fgets(buff,TAILLE,f)!=NULL){
		res[nombreDInstructions] = malloc(sizeof(buff));
		res[nombreDInstructions] = buff;
		printf("%s\n",res[nombreDInstructions]);
		nombreDInstructions++;
	}


}

int main(int argc, char const *argv[])
{
	RecupCode("test.txt");
	
	return 0;
}