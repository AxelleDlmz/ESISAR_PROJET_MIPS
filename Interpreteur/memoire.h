#ifndef __MEMOIRE_H
#define __MEMOIRE_H


#define TAILLEMEMOIRE 100

typedef struct caseMemoire caseMemoire;
struct caseMemoire{
	int valeur; /* Valeur de la case memoire (format : 0b011001...1 32 bits)*/
	int valide;	/* Bit de validite */
};


caseMemoire Memoire[TAILLEMEMOIRE];
void initialiserMemoire();

int ajouterValeur(int adr, int valeur);
int supprimerValeur(int adr);
int lireMemoire(int adr);


#endif