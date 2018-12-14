#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

#define NBOPERANDE 4
#define TAILLEOPERANDE 16


int main(int argc, char **argv){ 

	char tab[NBOPERANDE][TAILLEOPERANDE];
	char res[8] = "";
	char buffer[20] = "";
	long ptr = 0;
	char *nomFichier = argv[1];

	if(argc < 2){
		printf("%s\n", "Erreur : usage ./emul-mips <nom Fichier>");
		exit(1);
	}
	else{
		printf("\n%s\n","			**************************" );
		printf("%s\n",	"			**** Traducteur MIPS  ****" );
		printf("%s\n",	"			****                  ****" );
		printf("%s\n",	"			**** BOMMELAERE Remi  ****" );
		printf("%s\n",	"			**** DELOMEZ Axelle   ****" );
		printf("%s\n",	"			**** THOMAS Alexandre ****" );
		printf("%s\n\n","			**************************" );

	}


	while(lireUneLigneDuFichier(nomFichier, buffer, &ptr) != -1){
		stringSplit(buffer, tab);
		traitementCommande(tab, res);

		if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
			printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
			exit(1);
		}
	}
	
	printf("%s\n", "Execution avec succes : traduction en hexa dans \"out.txt\"");

	return 0;
}