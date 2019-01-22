#include <stdlib.h>
#include <stdio.h>
#include "memoire.h"

/*
	Place tous les bits de validite de chacune des case a 0
*/
void initialiserMemoire(){
	int i;
	for(i = 0; i < TAILLEMEMOIRE ; i++){
		Memoire[i].valide = 0;
	}
}

/*
	Ajoute une valeur en memoire a une adresse donnee en parametre.
	Retourne -1 si il y a erreur, 0 sinon
*/
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
/*
	Place le bit de validite d'une case memoire a 0
	Retourne -1 si il y a erreur, 0 sinon
*/
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

/*
	Retourne la valeur presente dans une case memoire
*/
int lireMemoire(int adr){
	int retour = -1;
	int indexMemoire = adr/4;

	if(adr % 4 == 0 ){
		if(Memoire[indexMemoire].valide)
			retour = Memoire[indexMemoire].valeur;
	}
	else
		printf("[Memoire][Lire Valeur] L'adresse %d n'est pas divisible par 4\n", adr);

	return retour;
}

/*
	Affiche l'ensemble des cases memoires
*/
void lireTouteMemoire(){
	int i = 0;
	
	for(i = 0; i < TAILLEMEMOIRE; i++){
		if(Memoire[i].valide == 1)
			printf("%x : %d\n", i*4, lireMemoire(i*4)  );
	}
}