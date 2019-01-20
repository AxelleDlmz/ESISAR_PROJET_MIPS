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
char * recupererBits(int deb, int fin, char * src){
	int longueur = fin - deb;
	char tmp[longueur];
	if(longueur < 1){
		return "";
	}
	for(int i = deb; i < fin; i++){
		tmp[i-deb]=src[i];
	}
	return tmp;
}


int prochaineInstruction(){
	return lireMemoire(LireRegistre(32));
}




