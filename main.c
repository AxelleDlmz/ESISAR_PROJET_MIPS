#include "hexa.h"
#include <stdio.h>
#include <stdlib.h>



int main(){

	char* OPCODE[TAILLE];			//Tableau des opcodes des fonctions
	char* NOM[TAILLE];				//Tableau des noms des fonctions

	OPCODE[0] = "00";
	NOM[0] = "tortue";

	OPCODE[1] = "01";
	NOM[1] = "nicaragua";

	printf("%s\n",RecupererLeNom("01", OPCODE, NOM));
	printf("%s\n",RecupererLOpcode("tortue", OPCODE, NOM));


	return 1;
}