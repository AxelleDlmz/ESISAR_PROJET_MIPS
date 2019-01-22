#ifndef __REGISTRES_H
#define __REGISTRES_H


int Registres[34];

void NettoyerRegistres();
int LireRegistre(int index);
void EcrireRegistre(int index, int donnee);
void AfficherRegistres();


#endif