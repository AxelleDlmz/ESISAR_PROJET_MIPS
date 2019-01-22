#ifndef __TOOL_H
#define __TOOL_H


int lireFichier(const char * nomDuFichier, char contenuFichier[256][9]);
int compterLignes(const char * nomDuFichier);
void remplirMemoireAvecFichier(const char *nomFichier);
int char2int(char *str);
void traduireFichier(char *nomFic);


#endif