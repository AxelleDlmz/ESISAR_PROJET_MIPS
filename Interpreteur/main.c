#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "tool.h"

void faireRoutine();

int main(int argc, char const *argv[])
{
	if(argc == 2){
		if(strlen(argv[1]) < 30){ /* on considere qu'un nom de fichier ne depasse pas 30 caracteres */
			remplirMemoireAvecFichier(argv[1]);
			/*lireTouteMemoire();*/
		}
	}
	else{
		printf("%s\n", "Erreur dans les arguments. Usage : ./emul-mips nomFichier");
		exit(EXIT_FAILURE);
	}
	return 0;
}

void faireRoutine(){
	
}