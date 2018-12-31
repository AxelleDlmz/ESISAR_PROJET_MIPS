#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "registres.h"
#include "tool.h"
#include "processeur.h"

void faireRoutine();



int main(int argc, char const *argv[])
{
	if(argc == 2){
		if(strlen(argv[1]) < 30){ /* on considere qu'un nom de fichier ne depasse pas 30 caracteres */
			remplirMemoireAvecFichier(argv[1]);
			NettoyerRegistres();
			EcrireRegistre(32,0);

			printf("%s\n", "MEMOIRE :");
			lireTouteMemoire();
			printf("******\n");
			faireRoutine();
		}
		else
			printf("%s\n","Erreur : nom de fichier trop long" );
	}
	else{
		printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips nomFichier");
		exit(EXIT_FAILURE);
	}
	return 0;
}

void faireRoutine(){
	/*int instr;
	char res[32] = "";
	instr = prochaineInstruction();
	printf("%d\n", instr );
	int2StrBinaire(instr,res);

	printf("%s\n",res );*/

	/*instruction instr;
	instr.operande1 = 1;
	instr.operande2 = 2;
	instr.operande3 = 14;
	instr.operateur = "ADDI";
	NettoyerRegistres();
	EcrireRegistre(2, 5);

	executerInstruction(instr);
	printf("###\n");
	AfficherRegistres();
	printf("###\n");*/

}