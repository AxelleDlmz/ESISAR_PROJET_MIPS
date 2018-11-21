#include "hexa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *RecupererLeNom(char* code, char** opcode, char** noms){
	int i = 0;
	while(strcmp(opcode[i],code)!=0 && i < TAILLE){
		i++;
	}
	if(i<TAILLE){
		return noms[i];
	}else{
		return "";
	}

}

char *RecupererLOpcode(char* nom, char** opcode, char** noms){
	int i = 0;
	while(strcmp(noms[i],nom)!=0 && i < TAILLE){
		i++;
	}
	if(i<TAILLE){
		return opcode[i];
	}else{
		return "-1";
	}

}