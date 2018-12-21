#include <stdlib.h>
#include <stdio.h>
#include "memoire.h"

void initialiserMemoire(){
	int i;
	for(i = 0; i < TAILLEMEMOIRE ; i++){
		Memoire[i].valide = 0;
	}
}

int ajouterValeurMemoire(int adr, int valeur){
	int retour = -1;
	int indexMemoire = adr/4;

	if(adr % 4 == 0){
		Memoire[indexMemoire].valeur = valeur;
		Memoire[indexMemoire].valide = 1;
		retour = 0;
	}
	else
		printf("[Memoire][Ajouter Valeur] L'adresse %d n'est pas divisible par 4\n", adr);

	return retour;
}

int supprimerValeurMemoire(int adr){
	int retour = -1;
	int indexMemoire = adr/4;

	if(adr % 4 == 0){
		Memoire[indexMemoire].valide = 0;

		retour = 0;
	}
	else
		printf("[Memoire][Supprimer Valeur] L'adresse %d n'est pas divisible par 4\n", adr);

	return retour;
}

int lireMemoire(int adr){
	int retour = -1;
	int indexMemoire = adr/4;

	if(adr % 4 == 0 ){
		if(Memoire[indexMemoire].valide)
			retour = Memoire[indexMemoire].valeur;
		else
			printf("[Memoire][Lire Valeur] La case memoire a l'adresse %d n'est pas valide\n", adr);
	}
	else
		printf("[Memoire][Lire Valeur] L'adresse %d n'est pas divisible par 4\n", adr);

	return retour;
}

void lireTouteMemoire(){
	int i = 0, val;
	while( ( val = lireMemoire(i*4) ) != -1){
		printf("0x%x\n", val );
		i++;
	}
}