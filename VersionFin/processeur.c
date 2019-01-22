#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "processeur.h"
#include "memoire.h"
#include "registres.h"

/*	FONCTIONNALITES DU PROCESSEUR
	
		- Lire en memoire a la case du PC : fait (prochaineInstruction)
		- Decoder les instructions
		- Executer les instructions
		- Ecrire les resultats dans les registres
*/

/*
	Prend un entier en entree, cet entier sera traduit dans sa forme hexadecimale
	Cette forme hexadecimale est une chaîne de caracteres contenue dans *ret
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
	Recupere un nombre de bits dans une chaine de bits
	Du bit debut au bit de fin (non inclus)
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

/*
	Convertit une chaine de caractere binaire
	en un entier. Gere les nombres signes
*/
int char2IntOps(char *str){
	int i = 0;
	int val = 0;
	if(str[0] == '0'){
		for(i = 1; i < strlen(str); i++){
			if(str[i] == '1')
				val+=pow(2, strlen(str)-1-i);
		}
	}else{
		for(i = 1; i < strlen(str); i++)
			if(str[i] == '0')
				val-=pow(2, strlen(str)-1-i);

		val-=1;
	}return val;
}

/*
	Recupere le program counter
	Index de la prochaine instruction a executer
*/
int prochaineInstruction(){
	return lireMemoire(LireRegistre(32));
}

/*
	Decode une instruction a partir de sa valeur entiere

	Cette fonction va construire une instruction dans un format standardise
	3 operandes et le nom de cette instruction
	ex : ADD R1 R2 R3
*/
instruction decoderInstruction (int donnee){
	// Parametres de l'instruction traduite retournee
	instruction res;
	char *oper1 = NULL, *oper2 = NULL, *oper3 = NULL;


	char code[6] = "";			// opcode de l'instruction
	char codeSpe[6] = "";		// code special pour les instructions speciales

	// Recuperation de l'opcode de l'instruction placee sur les 6 derniers bits
	recupererBits(26,6,donnee, code); 	
	
	/* ---------------------------
		Instructions speciales
	------------------------------
	*/
	if(!strcmp(code,"000000")) {
		recupererBits(0,6,donnee, codeSpe); 					// Recuperation du code special
		
		if(!strcmp(codeSpe,"000000")){
			char tmp[32] = "";
			recupererBits(0,32,donnee,tmp);						// Recuperation du code binaire de l'instruction
			if(tmp == "00000000000000000000000000000000"){		// SLL
				res.operateur = "NOP";
			}else{
				oper1 = (char*) malloc(sizeof(char)*5);
				oper2 = (char*) malloc(sizeof(char)*5);
				oper3 = (char*) malloc(sizeof(char)*5);
				recupererBits(11,5,donnee,oper1);	// rd
				recupererBits(16,5,donnee,oper2);   // rt
				recupererBits(6,5,donnee,oper3);	// sa
				res.operateur = "SLL" ;
			}
		}
		if(!strcmp(codeSpe,"000010")){ 							//SRL ou ROTR
			char tmp[32] = "";
			recupererBits(0,32,donnee,tmp);		// Recuperation du code binaire de l'instruction
			if(tmp[21]==0){
				oper1 = (char*) malloc(sizeof(char)*5);
				oper2 = (char*) malloc(sizeof(char)*5);
				oper3 = (char*) malloc(sizeof(char)*5);
				recupererBits(11,5,donnee,oper1);	// rd
				recupererBits(16,5,donnee,oper2);   // rt
				recupererBits(6,5,donnee,oper3);	// sa
				res.operateur = "SRL" ;
			}else{
				oper1 = (char*) malloc(sizeof(char)*5);
				oper2 = (char*) malloc(sizeof(char)*5);
				oper3 = (char*) malloc(sizeof(char)*5);
				recupererBits(11,5,donnee,oper1);	// rd
				recupererBits(16,5,donnee,oper2);   // rt
				recupererBits(6,5,donnee,oper3);	// sa
				res.operateur = "ROTR" ;
			}
		}
		if(!strcmp(codeSpe,"100000")){							// ADD
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			recupererBits(21,5,donnee,oper2);   // rs
			recupererBits(16,5,donnee,oper3);	// rt
			res.operateur = "ADD" ;
		}
		if(!strcmp(codeSpe, "100100")){							// AND
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "AND" ;
		}
		if(!strcmp(codeSpe,"011010")){ 							// DIV
			oper1 = (char*) malloc(sizeof(char)*5); // rs 
			oper2 = (char*) malloc(sizeof(char)*5); // rt
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			recupererBits(21,5,donnee,oper1);
			recupererBits(16,5,donnee,oper2);
			res.operateur = "DIV" ;
		}
		if(!strcmp(codeSpe,"001000")){ 							// JR
			oper1 = (char*) malloc(sizeof(char)*5); // rs 
			oper2 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			recupererBits(21,5,donnee,oper1);
			res.operateur = "JR" ;
		}
		if(!strcmp(codeSpe,"010000")){ 							// MFHI 
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			recupererBits(11,5,donnee,oper1);		// rd
			res.operateur = "MFHI" ;
		}
		if(!strcmp(codeSpe,"010010")){ 							// MFLO
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			recupererBits(11,5,donnee,oper1);		// rd
			res.operateur = "MFLO" ;
		}
		if(!strcmp(codeSpe,"011000")){ 							// MULT
			oper1 = (char*) malloc(sizeof(char)*5); // rs 
			oper2 = (char*) malloc(sizeof(char)*5); // rt
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			recupererBits(21,5,donnee,oper1);
			recupererBits(16,5,donnee,oper2);
			res.operateur = "MULT" ;
		}
		if(!strcmp(codeSpe,"100101")){ 							// OR
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "OR" ;
		}
		if(!strcmp(codeSpe,"101010")){ 							// SLT
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "SLT" ;
		}
		if(!strcmp(codeSpe,"100010")){ 							// SUB
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "SUB" ;
		}
		if(!strcmp(codeSpe,"100110")){ 							// XOR
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "XOR" ;
		}

	}
	/* ---------------------------
		Instructions non speciales
	------------------------------
	*/
	else{ 
		if(!strcmp(code,"001000")){ 							// ADDI
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*16); // immediate
			recupererBits(16,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(0,16,donnee,oper3);
			res.operateur = "ADDI" ;
		}
		if(!strcmp(code,"000100")){ 							// BEQ
			
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*16); // offset
			recupererBits(16,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(0,16,donnee,oper3);
			res.operateur = "BEQ" ;
		}
		if(!strcmp(code, "000111")){ 							// BGTZ
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			oper2 = (char*) malloc(sizeof(char)*16); // offset
			oper1 = (char*) malloc(sizeof(char)*5); // rs
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper1);
			res.operateur = "BGTZ" ;
		}
		if(!strcmp(code,"000110")){ 							// BLEZ
			oper3 = (char*) malloc(sizeof(char)*0); //Parametre inutilise
			oper2 = (char*) malloc(sizeof(char)*16); // offset
			oper1 = (char*) malloc(sizeof(char)*5); // rs
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper1);
			res.operateur = "BLEZ" ;
		}
		if(!strcmp(code,"000101")){ 							// BNE
			oper3 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper3);
			recupererBits(21,5,donnee,oper1);
			recupererBits(16,5,donnee,oper2);
			res.operateur = "BNE" ;
		}
		if(!strcmp(code,"000010")){ 							// J
			oper1 = (char*) malloc(sizeof(char)*26); 	// instr_index
			oper2 = (char*) malloc(sizeof(char)*0); 	//Parametre inutilise
			oper3 = (char*) malloc(sizeof(char)*0); 	//Parametre inutilise
			recupererBits(0,26,donnee,oper1);
			res.operateur = "J" ;			
		}
		if(!strcmp(code,"000011")){ 							// JAL
			oper1 = (char*) malloc(sizeof(char)*26); 	// instr_index
			oper2 = (char*) malloc(sizeof(char)*0); 	//Parametre inutilise
			oper3 = (char*) malloc(sizeof(char)*0); 	//Parametre inutilise
			recupererBits(0,26,donnee,oper1);
			res.operateur = "JAL" ;
		}
		if(!strcmp(code,"001111")){ 							// LUI
			oper3 = (char*) malloc(sizeof(char)*0); 	//Parametre inutilise
			oper2 = (char*) malloc(sizeof(char)*16); 	// immediate
			oper1 = (char*) malloc(sizeof(char)*5); 	// rt
			recupererBits(16,5,donnee,oper1);
			recupererBits(0,16,donnee,oper2);
			res.operateur = "LUI" ;
		}
		if(!strcmp(code,"100011")){ 							// LW
			oper2 = (char*) malloc(sizeof(char)*16); 	// offset
			oper3 = (char*) malloc(sizeof(char)*5); 	// base
			oper1 = (char*) malloc(sizeof(char)*5); 	// rt
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper3);
			recupererBits(16,5,donnee,oper1);
			res.operateur = "LW" ;
		}
		if(!strcmp(code,"101011")){ 							// SW
			oper2 = (char*) malloc(sizeof(char)*16); 	// offset
			oper3 = (char*) malloc(sizeof(char)*5); 	// base
			oper1 = (char*) malloc(sizeof(char)*5); 	// rt
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper3);
			recupererBits(16,5,donnee,oper1);
			res.operateur = "SW" ;
		}
	}

	// Construction de l'instruction a retourner
	res.operande1 = char2IntOps(oper1);
	res.operande2 = char2IntOps(oper2);
	res.operande3 = char2IntOps(oper3);
	return res;
	 
}
/*
	Execute l'instruction precedemment decodee

	Cette fonction recupere les donnees dans les registres
	et écrit le resultat dans un registre
*/
void executerInstruction(instruction instr){

	if(strcmp(instr.operateur, "ADD") == 0){
		printf("Operation : ADD $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		/*
			rd : 1er operande : destination
			rs : 2e
			rt : 3e
		*/
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) + LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "ADDI") == 0){
		printf("Operation : ADDI $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) + instr.operande3);

	}
	else if(strcmp(instr.operateur, "AND") == 0){
		printf("Operation : AND $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) & LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "BEQ") == 0){
		printf("Operation : BEQ $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		if(LireRegistre(instr.operande1) == LireRegistre(instr.operande2))
			EcrireRegistre(32, LireRegistre(32) + instr.operande3);
	}
	else if(strcmp(instr.operateur, "BGTZ") == 0){
		printf("Operation : BGTZ $%d,#%d\n",instr.operande1, instr.operande2);
		if(LireRegistre(instr.operande1) > 0)
			EcrireRegistre(32, LireRegistre(32) + instr.operande2);
	}
	else if(strcmp(instr.operateur, "BLEZ") == 0){
		printf("Operation : BLEZ $%d,#%d\n",instr.operande1, instr.operande2);
		if(LireRegistre(instr.operande1) <= 0)
			EcrireRegistre(32, LireRegistre(32) + instr.operande2);
	}
	else if(strcmp(instr.operateur, "BNE") == 0){
		printf("Operation : BNE $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		if(LireRegistre(instr.operande1) != LireRegistre(instr.operande2))
			EcrireRegistre(32, LireRegistre(32) + instr.operande3);
		
	}
	else if(strcmp(instr.operateur, "DIV") == 0){
		printf("Operation : DIV $%d,$%d\n",instr.operande1, instr.operande2);
		if(LireRegistre(instr.operande2) != 0){
			EcrireRegistre(33, LireRegistre(instr.operande1) % LireRegistre(instr.operande2)); //Reste
			EcrireRegistre(34, LireRegistre(instr.operande1) / LireRegistre(instr.operande2)); //Quotient entier
		}
	}
	else if(strcmp(instr.operateur, "J") == 0){
		printf("Operation : J #%d\n",instr.operande1);
		EcrireRegistre(32, LireRegistre(32) +instr.operande1);
	}
	else if(strcmp(instr.operateur, "JAL") == 0){
		printf("Operation : JAL #%d\n",instr.operande1);
		printf("Instruction non programmee\n");
	}
	else if(strcmp(instr.operateur, "JR") == 0){
		printf("Operation : JR $%d\n",instr.operande1);
		EcrireRegistre(32, LireRegistre(instr.operande1));
	}
	else if(strcmp(instr.operateur, "LUI") == 0){
		printf("Operation : LUI $%d,$%d\n",instr.operande1, instr.operande2);
		EcrireRegistre(LireRegistre(instr.operande1), instr.operande2 << 16);
	}
	else if(strcmp(instr.operateur, "MFHI") == 0){
		printf("Operation : MFHI $%d\n",instr.operande1);
		EcrireRegistre(instr.operande1, LireRegistre(33));
	}
	else if(strcmp(instr.operateur, "MFLO") == 0){
		printf("Operation : MFLO $%d\n",instr.operande1);
		EcrireRegistre(instr.operande1, LireRegistre(34));
	}
	else if(strcmp(instr.operateur, "MULT") == 0){ /*Ne gere pas l'overflow*/
		printf("Operation : MULT $%d,$%d\n",instr.operande1, instr.operande2);
		int val1 = LireRegistre(instr.operande1);
		int val2 = LireRegistre(instr.operande2);
		if(val1 * val2 > pow(2,32)-1){
			printf("Erreur : le nombre resultant de la multiplication ne rentre pas sur 32 bits. Nous ne sommes pas parvenu a resoudre ce probleme\n");
		}
		else
			EcrireRegistre(34, val1 * val2);
	}
	else if(strcmp(instr.operateur, "NOP") == 0){
		printf("Operation : NOP\n");
		
	}
	else if(strcmp(instr.operateur, "OR") == 0){
		printf("Operation : OR $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) | LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "ROTR") == 0){
		printf("Operation : ROTR $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, (LireRegistre(instr.operande2) >> instr.operande3) | (LireRegistre(instr.operande2) << (32 - instr.operande3)));
	}
	else if(strcmp(instr.operateur, "SLL") == 0){
		printf("Operation : SLL $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) << instr.operande3);
	}
	else if(strcmp(instr.operateur, "SLT") == 0){
		printf("Operation : SLT $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) < LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "SRL") == 0){
		printf("Operation : SRL $%d,$%d,#%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) >> instr.operande3);
	}
	else if(strcmp(instr.operateur, "SUB") == 0){
		printf("Operation : ADD $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) - LireRegistre(instr.operande3));
	}
	else if(strcmp(instr.operateur, "XOR") == 0){
		printf("Operation : ADD $%d,$%d,$%d\n",instr.operande1, instr.operande2, instr.operande3);
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) ^ LireRegistre(instr.operande3));
	}
}



