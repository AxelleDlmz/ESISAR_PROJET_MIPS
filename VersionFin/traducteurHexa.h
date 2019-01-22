#ifndef __TRADUCTEURHEXA_H
#define __TRADUCTEURHEXA_H

#define NBOPERANDE 4
#define TAILLEOPERANDE 16

int lireUneLigneDuFichier(char * nomDuFichier, char * ligneRetournee, long * ptr);
int ecireUneLigneDansLeFichier(char * nomDuFichier, char * ligne);
void viderLeFichier(char * nomDuFichier);
char *substr(char *src,int pos,int stopInd);
void ImmediateConcat(int nombre, char res[32]);
void BinToHex(char *binaire, char *retour);
void stringSplit(char *str, char tab[NBOPERANDE][TAILLEOPERANDE]);
void traitementCommande(char tab[NBOPERANDE][TAILLEOPERANDE], char res[8]);

#endif