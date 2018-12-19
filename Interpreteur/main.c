#include <stdlib.h>
#include <stdio.h>
#include "memoire.h"
#include "tool.h"

int main(int argc, char const *argv[])
{
	int nbLignes;
	char *nomFichier = "test.txt";
	char content[256][9];
	nbLignes = lireFichier(nomFichier, content);
	/*
	Dans content on a les lignes du fichier
	nbLignes contient le nombre de lignes */


	return 0;
}