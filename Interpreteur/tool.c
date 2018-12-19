#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"


int lireFichier(char * nomDuFichier, char contenuFichier[256][9]){
	FILE * f = fopen(nomDuFichier,"r");
	char ch;
	int i = 0, j = 0;
	if(f != NULL){
		while(!feof(f)){
			ch = fgetc(f);
			if(ch != '\n' && !feof(f)){
				contenuFichier[i][j] = ch;
				j++;
			}
			else{ /* ch == '\n' */
				contenuFichier[i][j] = '\0'; /* fin de la ligne donc de l'instruction hexa */
				j = 0;
				i++;
			}
		}

	}
	fclose(f);

	return i;
}

int compterLignes(char * nomDuFichier){
	FILE * f = fopen(nomDuFichier,"r");
	char ch;
	int nbLignes = 0;

	while(!feof(f))
	{
  		ch = fgetc(f);
  		if(ch == '\n')
  		{
    		nbLignes++;
  		}
	}

	fclose(f);
	return nbLignes;
}