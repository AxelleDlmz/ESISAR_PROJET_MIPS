#include "processeur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

instruction decoderInstruction (int donnee){
	instruction res;
	char code[6] = "";
	char codeSpe[6] = "";
	char *oper1, *oper2, *oper3;

	recupererBits(26,6,donnee, code); /* recupere les 6 premiers bits (opcode) */
	
	if(!strcmp(code,"000000")) { 		// instruction spéciale
		recupererBits(0,6,donnee, codeSpe); // récupération des 6 derniers bits
		if(!strcmp(codeSpe,"100000")){
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			recupererBits(21,5,donnee,oper2);   // rs
			recupererBits(16,5,donnee,oper3);	// rt
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "ADD" ;
		}
		if(!strcmp(codeSpe, "100100")){
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "AND" ;
		}
		if(!strcmp(codeSpe,"011010")){ // DIV
			//oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operateur = "DIV" ;
		}
		if(!strcmp(codeSpe,"001000")){ // JR ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?
			//oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operateur = "DIV" ;
		}
		if(!strcmp(codeSpe,"010000")){ // MFHI 
			oper1 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "MFHI" ;
		}
		if(!strcmp(codeSpe,"010010")){ // MFLO
			oper1 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "MFLO" ;
		}
		if(!strcmp(codeSpe,"011000")){ // MULT
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operateur = "MULT" ;
		}
		if(!strcmp(codeSpe,"100101")){ // OR
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "OR" ;
		}
		if(!strcmp(codeSpe,"100010")){ // SUB
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "SUB" ;
		}
		if(!strcmp(codeSpe,"100110")){ // XOR
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "XOR" ;
		}
	}else{
		if(!strcmp(codeSpe,"001000")){ //ADDI
			oper1 = (char*) malloc(sizeof(char)*16); // immediate
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "ADDI" ;
		}
		if(!strcmp(codeSpe,"000111")){ // BEQ
			oper1 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "BEQ" ;
		}
		if(!strcmp(codeSpe,"000110")){ //BLEZ
			oper1 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operateur = "BLEZ" ;
		}
		if(!strcmp(codeSpe,"000101")){ // BNE
			oper1 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "BNE" ;
		}
		if(!strcmp(codeSpe,"000010")){ //J
			oper1 = (char*) malloc(sizeof(char)*26); // instr_index
			recupererBits(0,26,donnee,oper1);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "J" ;			

		}
		if(!strcmp(codeSpe,"000011")){ //JAL
			oper1 = (char*) malloc(sizeof(char)*26); // instr_index
			recupererBits(0,26,donnee,oper1);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "JAL" ;
		}
		if(!strcmp(codeSpe,"001111")){ // LUI
			oper1 = (char*) malloc(sizeof(char)*16); // immediate
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(16,5,donnee,oper3);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "LUI" ;
		}
		if(!strcmp(codeSpe,"100011")){ // LW
			oper1 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // base
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "LW" ;
		}
		if(!strcmp(codeSpe,"101011")){ // SW
			oper1 = (char*) malloc(sizeof(char)*16); // offset
			oper2 = (char*) malloc(sizeof(char)*5); // base
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "SW" ;
		}
	}
		
		
		/*switch(code){

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

			
*/
	
	return res;
	 
}