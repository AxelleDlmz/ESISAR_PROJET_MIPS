#include "processeur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

instruction decoderInstruction (int donnee){
	
	instruction res;
	char binaire[32] = "";
	int2StrBinaire(donnee, binaire);

	char code[6];
	recupererBits(0,6,binaire, code); /* recupere les 6 premiers bits (opcode) */
	printf("code %s\n", code);
	char codeSpe[6] ="";
	char *oper1, *oper2, *oper3;


	


	if(strcmp(code,"000000") == 0) { 		// instruction spéciale
		recupererBits(26,6,binaire, codeSpe); // récupération des 6 derniers bits
		printf("codeSPe %s\n", codeSpe);

		if(strcmp(code, "100100") == 0){
			recupererBits(21,5,binaire,oper2);
			recupererBits(16,5,binaire,oper3);
			recupererBits(11,5,binaire,oper1);
			res.operande2 = (int)strtol(oper2, NULL, 2);
			res.operande3 = (int)strtol(oper3, NULL, 2);
			res.operande1 = (int)strtol(oper1, NULL, 2);
			res.operateur = "AND" ;

			printf("%s R%d R%d R%d\n",res.operateur, res.operande1, res.operande2, res.operande3 );
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

			case "100000": // ADD
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADD";
				break;

			case "100100": // AND
				res.operande2 = (int)strtol(recupererBits(21,25,binaire), NULL, 2);
				res.operande3 = (int)strtol(recupererBits(16,20,binaire), NULL, 2);
				res.operande1 = (int)strtol(recupererBits(11,15,binaire), NULL, 2);
				res.operateur = "AND" ;
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
				
		}*/
	/*}else{						//instruction non spéciale
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
	}*/
	}
	return res;
	 
}