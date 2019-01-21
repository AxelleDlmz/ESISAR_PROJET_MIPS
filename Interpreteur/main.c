#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "registres.h"
#include "tool.h"
#include "processeur.h"

void faireRoutineFichierInteractif();
void faireRoutineInteractifDirect();
void faireRoutineDirect();




int main(int argc, char const *argv[])
{
	//if(strcmp(argv[1], "-pas") != 0) /*si le premier mot n'est pas "-pas"*/
	/*{
		if(strlen(argv[1]) < 30){ /* on considere qu'un nom de fichier ne depasse pas 30 caracteres */
			/*remplirMemoireAvecFichier(argv[1]);
			NettoyerRegistres();
			EcrireRegistre(32,0);

			printf("%s\n", "MEMOIRE :");
			lireTouteMemoire();
			printf("******\n");
			faireRoutineFichier();
		}
		else
			printf("%s\n","Erreur : nom de fichier trop long" );
	}

	else{
		printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips nomFichier");
		exit(EXIT_FAILURE);
	}*/

	if(argc == 3){
		if(strcmp(argv[2], "-pas") == 0){ /* Mode fichier interactif */
			printf("Mode fichier interactif : lecture dans %s\n", argv[1]);
			faireRoutineFichierInteractif(argv[1]);
		}else{
			printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips <nomFichier> <-pas>");
			exit(EXIT_FAILURE);
		}
	}else if(argc == 2){
		if(strcmp(argv[1], "-pas") == 0){ /* Mode interactif direct */
			printf("Mode interactif direct\n");
			faireRoutineInteractifDirect();
		}
		else{ /* Mode direct : lecture dans un fichier execution et affichage de l'etat en fin d'exec*/
			printf("Mode direct : lecture dans %s\n", argv[1]);
			faireRoutineDirect();
		}
	}else{
		printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips [nomFichier] [-pas]");
		exit(EXIT_FAILURE);
	}

	return 0;
}

void faireRoutineFichierInteractif(char *nomFic){
	if(strlen(nomFic) < 30){
		char retour[5];
		int i = 0, valMem;

		remplirMemoireAvecFichier(nomFic);
		NettoyerRegistres();

		printf("%s\n", "MEMOIRE :");
		lireTouteMemoire();
		printf("******\n");

		while( ( valMem = lireMemoire(i*4) ) != -1){
			printf("Prochaine instruction : 0x%x\n", valMem );
			printf("Entrez une touche pour continuer, reg pour afficher les registres, EXIT pour sortir\n");
			scanf("%s", retour);
			if(strcmp(retour, "EXIT") == 0){
				printf("Arret du programme\n");
				exit(0);
			}else if(strcmp(retour, "reg") == 0){
				AfficherRegistres();
			}
			/*instruction instr = decoderInstruction(valMem);
			executerInstruction(instr);*/

			i++;
		}

	
	}
	else
		printf("%s\n","Erreur : nom de fichier trop long" );
}


void faireRoutineInteractifDirect(){
	char retour[11];
	int valMem;

	NettoyerRegistres();
	EcrireRegistre(2,3);
	EcrireRegistre(3,2);

	do{
		printf("Entrez la prochaine instruction (en hexa, avec 0x), mem pour afficher la memoire, reg pour les registres, EXIT pour sortir\n");
		scanf("%s", retour);
		retour[10] = '\n';
		if(strcmp(retour, "reg") == 0)
			AfficherRegistres();
		else if(strcmp(retour, "mem") == 0)
			lireTouteMemoire();
		else if(strlen(retour) == 11){
			valMem = char2int(retour);
			//printf("Placement en memoire et execution de l'instruction %x\n", valMem);
			if(ajouterValeurMemoire(LireRegistre(32), valMem) == -1){
				printf("ERREUR : placement en memoire impossible\n");
				exit(EXIT_FAILURE);
			}
			EcrireRegistre(32,LireRegistre(32) + 4);

			instruction instr = decoderInstruction(valMem);
			printf("%s R%d R%d R%d\n\n",instr.operateur, instr.operande1, instr.operande2, instr.operande3 );
			executerInstruction(instr);
		}
		else{
			printf("Erreur : format incompris\n");
			exit(EXIT_FAILURE);
		}
	}while(strcmp(retour, "EXIT") != 0);
	printf("Arret du programme\n");



}

void faireRoutineDirect(){

}

void faireRoutine(){
	/*int instr;
	char res[32] = "";
	instr = prochaineInstruction();
	printf("%d\n", instr );
	int2StrBinaire(instr,res);

	printf("%s\n",res );*/

	instruction instr;
	instr.operande1 = 1;
	instr.operande2 = 2;
	instr.operande3 = 3;
	instr.operateur = "XOR";
	NettoyerRegistres();
	
	EcrireRegistre(2, 1);
	EcrireRegistre(3, 1);

	executerInstruction(instr);
	printf("###\n");
	AfficherRegistres();
	printf("###\n");

}