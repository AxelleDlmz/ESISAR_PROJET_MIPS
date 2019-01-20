#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "processeur.h"
#include "memoire.h"
#include "registres.h"

/*	FONCTIONNALITES DU PROCESSEUR
	
		- Lire en mémoire à la case du PC : fait (prochaineInstruction)
		- Décoder les instructions
		- Exécuter les instructions
		- Ecrire les résultats dans les registres
*/

void int2StrBinaire(int donnee, char *ret){
	int i;
	for(i = 31; i >= 0; i--){
		if(abs(donnee)-pow(2,i)>=0){
			strcat(ret,"1");
			if(donnee > 0)
				donnee-=pow(2,i);
			else if(donnee < 0)
				donnee+=pow(2,i);
		}else{
			strcat(ret,"0");
		}
	}
}
/* 
	Récupère un nombre de bits dans une chaine de bits
	Du bit début au bit de fin (non inclus)
*/
/*void recupererBits(int deb, int fin, char * src, char *ret){
	printf("%d %d\n",deb, fin );
	int longueur = fin - deb +1;
	int i, j=0;
	//ret = (char *) malloc(sizeof(char)*(longueur+1));
	if(longueur < 1){
		ret = "";
	}
	for(i = deb; i < fin+1; i++){
		ret[j]=src[i];
		j++;
		printf("src[%d] = %c\n",i,src[i] );
	}
	ret[i] = '\0';
	printf("recup : %s\n", ret);
}*/

void recupererBits(int deb, int fin, int donnee, char *ret){
	int i,j=0;
	char src[32] = "";
	int2StrBinaire(donnee, src);

	for(i = deb; i < deb+fin; i++){
		ret[j++] = src[i];
	}
	ret[j] = '\0';	
}


int prochaineInstruction(){
	return lireMemoire(LireRegistre(32));
}




