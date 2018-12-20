#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processeur.h"
#include "memoire.h"

/*	FONCTIONNALITES DU PROCESSEUR
	
		- Lire en mémoire à la case du PC
		- Décoder les instructions
		- Exécuter les instructions
		- Ecrire les résultats dans les registres
*/

char * int2StrBinaire(int donnee){
	char binaire[32] = "";
	for(int i = 0; i > 32; i++){
		if(donnee-pow(2,i)>0){
			strcat(binaire,"1");
			donnee-=pow(2,i);
		}else{
			strcat(binaire,"0");
		}
	}
	return binaire;
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

/*
	Récupère le int de l'instruction stocké dans la mémoire
	Renvoie une instruction exécutable
*/
instruction decoderInstruction (int donnee){
	
	instruction res;
	char binaire[32] = int2StrBinaire(donnee);
	char code[6] = recupererBits(0,6,binaire);

	if(code=="000000"){ 		// instruction spéciale
		
		code = recupererBits(26,32,binaire); // récupération des 6 derniers bits
		
		switch(code){

			case "000000":
				if(binaire == "00000000000000000000000000000000"){
					(*res).operande1 = ;
					(*res).operande2 = ;
					(*res).retour = ;
					(*res).operateur = "NOPE";

				}else{
					(*res).operande1 = ;
					(*res).operande2 = ;
					(*res).retour = ;
					(*res).operateur = "SLL";
				}

			case "100000": // ADD
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADD";
				break;

			case "100100": // AND
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "AND" ;
				break;

			case "011010": // DIV
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "DIV";
				break;

			case "001000": // JR
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "JR";
				break;

			case "010000": // MFHI
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MFHI";
				break;

			case "010010": // MFLO
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MFLO" ;
				break;

			case "011000": // MULT
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MULT";
				break;

			case "100101": // OR
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "OR";
				break;

			case "100010" :
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "SUB";				
				break;

			case "100110":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "XOR";
				break;
				
		}
	}else{						//instruction non spéciale

		switch(code){
			case "001000":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADDI";
				break;

			case "001111":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "LUI";
				break;

			case "100011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "LW";
				break;

			case "101011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "SW";
				break;
		}
	}
}