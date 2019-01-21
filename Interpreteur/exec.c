#include "processeur.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registres.h"
#include "memoire.h"
#include <string.h>

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
			EcrireRegistre(32, LireRegistre(32) + instr.operande3);
	}
	else if(strcmp(instr.operateur, "BGTZ") == 0){
		if(LireRegistre(instr.operande1) > 0)
			EcrireRegistre(32, LireRegistre(32) + instr.operande2);
	}
	else if(strcmp(instr.operateur, "BLEZ") == 0){
		if(LireRegistre(instr.operande1) <= 0)
			EcrireRegistre(32, LireRegistre(32) + instr.operande2);
	}
	else if(strcmp(instr.operateur, "BNE") == 0){
		if(LireRegistre(instr.operande1) != LireRegistre(instr.operande2))
			EcrireRegistre(32, LireRegistre(32) + instr.operande3);
		
	}
	else if(strcmp(instr.operateur, "DIV") == 0){
		if(LireRegistre(instr.operande2) != 0){
			EcrireRegistre(33, LireRegistre(instr.operande1) % LireRegistre(instr.operande2)); //Reste
			EcrireRegistre(34, LireRegistre(instr.operande1) / LireRegistre(instr.operande2)); //Quotient entier
		}
	}
	else if(strcmp(instr.operateur, "J") == 0){
		EcrireRegistre(32, LireRegistre(32) +instr.operande1);
	}
	else if(strcmp(instr.operateur, "JAL") == 0){
		printf("Don't know watta do\n");
	}
	else if(strcmp(instr.operateur, "JR") == 0){
		EcrireRegistre(32, LireRegistre(instr.operande1));
	}
	else if(strcmp(instr.operateur, "LUI") == 0){
		EcrireRegistre(LireRegistre(instr.operande1), instr.operande2 << 16);
	}
	else if(strcmp(instr.operateur, "LW") == 0){
		EcrireRegistre(instr.operande1, lireMemoire(LireRegistre(instr.operande3) + instr.operande2));
	}
	else if(strcmp(instr.operateur, "MFHI") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(33));
	}
	else if(strcmp(instr.operateur, "MFLO") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(34));
	}
	else if(strcmp(instr.operateur, "MULT") == 0){ /*Ne gere pas l'overflow*/
		int val1 = LireRegistre(instr.operande1);
		int val2 = LireRegistre(instr.operande2);
		if(val1 * val2 > pow(2,32)-1){
			printf("Erreur : le nombre resultant de la multiplication ne rentre pas sur 32 bits. Nous ne sommes pas parvenu a resoudre ce probleme\n");
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
		ajouterValeurMemoire(LireRegistre(instr.operande3) + instr.operande2, LireRegistre(instr.operande1));
	}
	else if(strcmp(instr.operateur, "SYSCALL") == 0){
		printf("Don't know watta do\n");
	}
	else if(strcmp(instr.operateur, "XOR") == 0){
		EcrireRegistre(instr.operande1, LireRegistre(instr.operande2) ^ LireRegistre(instr.operande3));
	}
}