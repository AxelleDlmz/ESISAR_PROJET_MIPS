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

/*
	Récupère le int de l'instruction stocké dans la mémoire
	Renvoie une instruction exécutable
*/
instruction decoderInstruction (int donnee){
	
	instruction res;
	char binaire[32] = int2StrBinaire(donnee);
	char code[6] = recupererBits(0,6,binaire);
	char codeSpe[6] = "";
	char *oper1, *oper2, *oper3;


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
		codeSpe = recupererBits(1,6,binaire);
		printf("%s%s\n","codeSpe :", codeSpe );
		switch(code){
			case "001000":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADDI";
				break;

			case "000111":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BEQ";
				break;

			case "000110":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BLEZ";
				break;

			case "000101":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BNE";
				break;

			case "000010":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "J";
				break;

			case "000011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "JAL";
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

void executerInstruction(instruction instr){

	if(strcmp(instr.operateur, "ADD") == 0){
		/*
			rd : 1er operande : destination
			rs : 2e
			rt : 3e
		*/
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) + LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "ADDI") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) + instr.operande3);

	}
	else if(strcmp(instr.operateur, "AND") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) & LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "BEQ") == 0){
		if(LireRegistre(instr.operande1) == LireRegistre(instr.operande2))
			/*Branch*/
			printf("BRANCH\n");
		/*la comparaison doit-elle se faire par une soustraction ?*/
	}
	else if(strcmp(instr.operateur, "BGTZ") == 0){
		if(LireRegistre(instr.operande1) > 0)
			/*Branch*/
			printf("BRANCH\n");
	}
	else if(strcmp(instr.operateur, "BLEZ") == 0){
		if(LireRegistre(instr.operande1) <= 0)
			/*Branch*/
			printf("BRANCH\n");
	}
	else if(strcmp(instr.operateur, "BNE") == 0){
		if(LireRegistre(instr.operande1) != LireRegistre(instr.operande2))
			/*Branch*/
			printf("BRANCH\n");
		
	}
	else if(strcmp(instr.operateur, "DIV") == 0){
		if(LireRegistre(instr.operande2) != 0){
			EcrireRegistre(33, LireRegistre(instr.operande1) % LireRegistre(instr.operande2));
			EcrireRegistre(34, LireRegistre(instr.operande1) / LireRegistre(instr.operande2));
		}
	}
	else if(strcmp(instr.operateur, "J") == 0){
		printf("BRANCH\n");
	}
	else if(strcmp(instr.operateur, "JAL") == 0){
		printf("Don't know watta do\n");
	}
	else if(strcmp(instr.operateur, "JR") == 0){
		EcrireRegistre(32, LireRegistre(instr.operande2));
	}
	else if(strcmp(instr.operateur, "LUI") == 0){
		EcrireRegistre(LireRegistre(instr.operande1), instr.operande2 << 16);
	}
	else if(strcmp(instr.operateur, "LW") == 0){
		
	}
	else if(strcmp(instr.operateur, "MFHI") == 0){
		EcrireRegistre(LireRegistre(instr.operande1), 33);
	}
	else if(strcmp(instr.operateur, "MFLO") == 0){
		EcrireRegistre(LireRegistre(instr.operande1), 34);
	}
	else if(strcmp(instr.operateur, "MULT") == 0){ /*Ne fonctionne pas*/
		int val1 = LireRegistre(instr.operande1);
		int val2 = LireRegistre(instr.operande2);
		if(val1 * val2 > pow(2,32)-1){
			EcrireRegistre(34, (val1 * val2) & 0xFFFFFFFF);
			EcrireRegistre(33, (val1 * val2) & (0xFFFFFFFF << 32));
		}
		else
			EcrireRegistre(34, val1 * val2);
	}
	else if(strcmp(instr.operateur, "NOP") == 0){
		
	}
	else if(strcmp(instr.operateur, "OR") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) | LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "ROTR") == 0){
		EcrireRegistre(instr.operande1, (LireRegistre(instr.operande2) >> instr.operande3) | (LireRegistre(instr.operande2) << (32 - instr.operande3)));
	}
	else if(strcmp(instr.operateur, "SLL") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) << instr.operande3);
	}
	else if(strcmp(instr.operateur, "SLT") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) < LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "SRL") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) >> instr.operande3);
	}
	else if(strcmp(instr.operateur, "SUB") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) - LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "SW") == 0){
		printf("Don't know watta do\n");
	}
	else if(strcmp(instr.operateur, "SYSCALL") == 0){
		printf("Don't know watta do\n");
	}
	else if(strcmp(instr.operateur, "XOR") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) ^ LireRegistre(instr.operande3));
	}
}