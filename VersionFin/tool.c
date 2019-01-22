#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"
#include "memoire.h"
#include "traducteurHexa.h"

#define NBOPERANDE 4
#define TAILLEOPERANDE 16

int lireFichier(const char * nomDuFichier, char contenuFichier[256][9]){
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
	else{
		printf("Impossible d'ouvrir le fichier %s\n", nomDuFichier);
		exit(EXIT_FAILURE);
	}
	fclose(f);

	return i;
}

int compterLignes(const char * nomDuFichier){
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

void remplirMemoireAvecFichier(const char *nomFichier){
	int nbLignes, i; 
	unsigned int hexStr2hexInt;

	char content[256][9];
	nbLignes = lireFichier(nomFichier, content);
	/* Dans content on a les lignes du fichier
	   nbLignes contient le nombre de lignes */

	initialiserMemoire();
	for(i = 0; i < nbLignes-1; i++){
		sscanf(content[i], "%x", &hexStr2hexInt);
		ajouterValeurMemoire(i*4, hexStr2hexInt);
	}
}

int char2int(char *str){
	return (int)strtol(str,NULL,0);
}

void traduireFichier(char *nomFic){

	char tab[NBOPERANDE][TAILLEOPERANDE];
	char res[8] = "";
	char buffer[20] = "";
	long ptr = 0;
	
	while(lireUneLigneDuFichier(nomFic, buffer, &ptr) != -1){
		stringSplit(buffer, tab);
		traitementCommande(tab, res);

		if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
			printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
			exit(1);
		}
	}
	
	printf("%s\n", "Execution avec succes : traduction en hexa dans \"out.txt\"");
}