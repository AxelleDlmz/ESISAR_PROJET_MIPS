#ifndef __MEMOIRE_H
#define __MEMOIRE_H


#define TAILLEMEMOIRE 100

typedef struct caseMemoire caseMemoire;
struct caseMemoire{
	int valeur; /* Valeur de la case memoire (format : 0b011001...1 32 bits)*/
	int valide;	/* Bit de validite */
};


caseMemoire Memoire[TAILLEMEMOIRE];
/*
	Initialise tous les bits de validite
	du tableau a 0
*/
void initialiserMemoire();

/*
	adr : entier sous forme de 8 caracteres hexa (0xFAB52135)
	int : entier sous forme de 32 bits (0b011010...0)
	retour : 0 si succès, -1 si echec
*/
int ajouterValeurMemoire(int adr, int valeur);

/*
	adr : entier sous forme de 8 caracteres hexa (0xFAB52135)
	retour : 0 si succes, -1 si echec
*/
int supprimerValeurMemoire(int adr);

/*
	adr : entier sous forme de 8 caracteres hexa (0xFAB52135)
	retour : valeur de la case memoire si succes, NULL si echec
*/
int lireMemoire(int adr);

void lireTouteMemoire();


#endif