#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "registres.h"
#include "tool.h"
#include "processeur.h"
#include "traducteurHexa.h"

void faireRoutineFichierInteractif();
void faireRoutineInteractifDirect();
void faireRoutineDirect();




int main(int argc, char const *argv[])
{
	if(argc == 3){
		if(strcmp(argv[2], "-pas") == 0){ /* Mode fichier interactif */
			remove("out.txt");
			printf("Mode fichier interactif : lecture dans %s\n", argv[1]);
			faireRoutineFichierInteractif(argv[1]);
		}else{
			printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips <nomFichier> <-pas>");
			exit(EXIT_FAILURE);
		}
	}else if(argc == 2){
		if(strcmp(argv[1], "-pas") == 0){ /* Mode interactif direct */
			remove("out.txt");
			printf("Mode interactif direct\n");
			faireRoutineInteractifDirect();
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

		traduireFichier(nomFic);

		remplirMemoireAvecFichier("out.txt");
		NettoyerRegistres();

		EcrireRegistre(2,3);
		EcrireRegistre(3,5);

		printf("%s\n", "MEMOIRE :");
		lireTouteMemoire();
		printf("******\n");

		while( ( valMem = lireMemoire(i*4) ) != -1){
			printf("Prochaine instruction : 0x%x\n", valMem );
			printf("Entrez une touche pour continuer, EXIT pour sortir\n");
			scanf("%s", retour);
			if(strcmp(retour, "EXIT") == 0){
				printf("Arret du programme\n");
				exit(0);
			}
			else{
				instruction instr = decoderInstruction(valMem);
				executerInstruction(instr);
				AfficherRegistres();

				i++;
			}
			
			
		}

	
	}
	else
		printf("%s\n","Erreur : nom de fichier trop long" );
}


void faireRoutineInteractifDirect(){
	char *retour;
	int valMem;
	int mode = 0; /* 0 = hexa, 1 = texte */
	/* Pour le mode texte */
	char tab[NBOPERANDE][TAILLEOPERANDE];
	char res[8] = "";
	char buffer[20] = "";

	NettoyerRegistres();
	EcrireRegistre(2,3);
	EcrireRegistre(3,2);

	do{
		if(mode == 0){
			retour = (char*)malloc(sizeof(char)*11);
			printf("Entrez la prochaine instruction (en hexa, avec 0x), mem pour afficher la memoire, reg pour les registres, EXIT pour sortir\n\n");
			scanf("%s", retour);
			retour[10] = '\n';
			if(strcmp(retour, "reg") == 0)
				AfficherRegistres();
			else if(strcmp(retour, "mem") == 0)
				lireTouteMemoire();
			else if(strcmp(retour, "txt") == 0)
				mode = 1;
			else if(strcmp(retour, "hex") == 0)
				printf("Deja en mode hex\n");
			else if(strlen(retour) == 11){
				valMem = char2int(retour);
				//printf("Placement en memoire et execution de l'instruction %x\n", valMem);
				if(ajouterValeurMemoire(LireRegistre(32), valMem) == -1){
					printf("ERREUR : placement en memoire impossible\n");
					exit(EXIT_FAILURE);
				}

				EcrireRegistre(32,LireRegistre(32) + 4);

				instruction instr = decoderInstruction(valMem);
				executerInstruction(instr);
			}
		}
		else if(mode == 1){
			retour = (char*)malloc(sizeof(char)*32);
			printf("Entrez la prochaine instruction (ex : ADDI_$1,$2,#3  en remplacant l'espace par '_'), reg pour afficher les registres\n\n");
			scanf("%s", retour);
			if(strcmp(retour, "reg") ==0)
				AfficherRegistres();
			else if(strcmp(retour, "hex") == 0)
				mode = 0;
			else if(strcmp(retour, "txt") == 0)
				printf("Deja en mode texte\n");
			else {
				stringSplit(retour, tab); /* A FINIR */
				traitementCommande(tab, res);
				valMem = (int)strtol(res,NULL,16);

				if(ajouterValeurMemoire(LireRegistre(32), valMem) == -1){
					printf("ERREUR : placement en memoire impossible\n");
					exit(EXIT_FAILURE);
				}

				EcrireRegistre(32,LireRegistre(32) + 4);
				instruction instr = decoderInstruction(valMem);
				executerInstruction(instr);
			}
		}
		else{
			printf("Erreur : format incompris\n");
			exit(EXIT_FAILURE);
		} 

		
		//printf("%s R%d R%d R%d\n\n",instr.operateur, instr.operande1, instr.operande2, instr.operande3 );


	}while(strcmp(retour, "EXIT") != 0);
	printf("Arret du programme\n");



}