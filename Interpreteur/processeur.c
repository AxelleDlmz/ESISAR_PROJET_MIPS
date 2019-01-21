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
void recupererBits(int deb, int fin, int donnee, char *ret){
	int i,j=0;
	char src[32] = "";
	int2StrBinaire(donnee, src);

	for(i = 31-deb-fin+1; i < 31-deb+1; i++){
		ret[j++] = src[i];
	}
	ret[j] = '\0';	
}

int char2IntOps(char * op){
	if(op != NULL)
		return (int)strtol(op, NULL, 2);
	return NULL;
}

int prochaineInstruction(){
	return lireMemoire(LireRegistre(32));
}




