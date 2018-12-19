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
	Récupère le int de l'instruction stocké dans la mémoire
	Renvoie une instruction exécutable
*/
instruction decoderInstruction (int donnee){
	instruction res;
	char binaire[32] = int2StrBinaire(donnee);
	char code[6]="";
	for(int i = 0; i < 7; i++)
		code[i]=binaire[i];

	if(code=="000000"){ 		// instruction spéciale
		for(int i = 26; i < 32; i++)
			code[i-26]=binaire[i];
		
		switch(code){
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
		}
	}else{

	}
}