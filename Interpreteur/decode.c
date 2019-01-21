#include "processeur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

instruction decoderInstruction (int donnee){
	// Parametres de l'instruction traduite retournee
	instruction res;
	char *oper1 = NULL, *oper2 = NULL, *oper3 = NULL;


	char code[6] = "";			// opcode de l'instruction
	char codeSpe[6] = "";		// code special pour les instructions speciales
	

	// Recuperation de l'opcode de l'instruction placee sur les 6 derniers bits
	recupererBits(26,6,donnee, code); 							
	
	if(!strcmp(code,"000000")) { 				// Si l'opcode est 000000 on sait que l'instruction est spéciale
		recupererBits(0,6,donnee, codeSpe); 	// Recuperation du code special
		if(!strcmp(codeSpe,"000000")){
			char tmp[32] = "";
			recupererBits(0,32,donnee,tmp);		// Recuperation du code binaire de l'instruction
			if(tmp == "00000000000000000000000000000000"){
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
		if(!strcmp(codeSpe,"000010")){
			char tmp[32] = "";
			recupererBits(0,32,donnee,tmp);		// Recuperation du code binaire de l'instruction
			printf("tmp %s\n",tmp );
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
				res.operateur = "SRL" ;
			}
		}

		if(!strcmp(codeSpe,"100000")){
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			recupererBits(21,5,donnee,oper2);   // rs
			recupererBits(16,5,donnee,oper3);	// rt
			res.operateur = "ADD" ;
		}
		if(!strcmp(codeSpe, "100100")){
			oper1 = (char*) malloc(sizeof(char)*5);
			oper2 = (char*) malloc(sizeof(char)*5);
			oper3 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "AND" ;
		}
		if(!strcmp(codeSpe,"011010")){ // DIV
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "DIV" ;
		}
		if(!strcmp(codeSpe,"001000")){ // JR
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			recupererBits(21,5,donnee,oper2);
			res.operateur = "JR" ;
		}
		if(!strcmp(codeSpe,"010000")){ // MFHI 
			oper1 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			res.operateur = "MFHI" ;
		}
		if(!strcmp(codeSpe,"010010")){ // MFLO
			oper1 = (char*) malloc(sizeof(char)*5);
			recupererBits(11,5,donnee,oper1);	// rd
			res.operateur = "MFLO" ;
		}
		if(!strcmp(codeSpe,"011000")){ // MULT
			oper2 = (char*) malloc(sizeof(char)*5); // rs 
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "MULT" ;
		}
		if(!strcmp(codeSpe,"100101")){ // OR
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "OR" ;
		}
		if(!strcmp(codeSpe,"100010")){ // SUB
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "SUB" ;
		}
		if(!strcmp(codeSpe,"100110")){ // XOR
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
			oper2 = (char*) malloc(sizeof(char)*16); // offset
			oper1 = (char*) malloc(sizeof(char)*5); // rs
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper1);
			res.operateur = "BGTZ" ;
		}
		if(!strcmp(code,"000110")){ 							// BLEZ
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
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper1);
			res.operateur = "BNE" ;
		}
		if(!strcmp(code,"000010")){ 							// J
			oper1 = (char*) malloc(sizeof(char)*26); // instr_index
			recupererBits(0,26,donnee,oper1);
			res.operateur = "J" ;			
		}
		if(!strcmp(code,"000011")){ 							// JAL
			oper1 = (char*) malloc(sizeof(char)*26); // instr_index
			recupererBits(0,26,donnee,oper1);
			res.operateur = "JAL" ;
		}
		if(!strcmp(code,"001111")){ 							// LUI
			oper2 = (char*) malloc(sizeof(char)*16); // immediate
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(16,5,donnee,oper1);
			recupererBits(0,16,donnee,oper2);
			res.operateur = "LUI" ;
		}
		if(!strcmp(code,"100011")){ 							// LW
			oper2 = (char*) malloc(sizeof(char)*16); // offset
			oper3 = (char*) malloc(sizeof(char)*5); // base
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper3);
			recupererBits(16,5,donnee,oper1);
			res.operateur = "LW" ;
		}
		if(!strcmp(code,"101010")){ 							// SLT
			oper1 = (char*) malloc(sizeof(char)*5); // rd
			oper2 = (char*) malloc(sizeof(char)*5); // rs
			oper3 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(11,5,donnee,oper1);
			recupererBits(21,5,donnee,oper2);
			recupererBits(16,5,donnee,oper3);
			res.operateur = "SLT" ;

		}
		if(!strcmp(code,"101011")){ 							// SW
			oper2 = (char*) malloc(sizeof(char)*16); // offset
			oper3 = (char*) malloc(sizeof(char)*5); // base
			oper1 = (char*) malloc(sizeof(char)*5); // rt
			recupererBits(0,16,donnee,oper2);
			recupererBits(21,5,donnee,oper3);
			recupererBits(16,5,donnee,oper1);
			res.operateur = "SW" ;
		}
	}
	res.operande1 = char2IntOps(oper1);
	res.operande2 = char2IntOps(oper2);
	res.operande3 = char2IntOps(oper3);
	return res;
	 
}