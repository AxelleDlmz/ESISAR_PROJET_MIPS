#include "processeur.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registres.h"

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