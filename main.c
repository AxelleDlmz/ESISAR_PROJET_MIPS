#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBOPERANDE 4
#define TAILLEOPERANDE 16

/*	retourne une chaine de char
	src : chaine de depart
	pos : position de depart depuis laquelle on veut extraire
	stopInd : position de fin de l'extraction */

char *substr(char *src,int pos,int stopInd) { 
  char *dest=NULL;                        
  if (stopInd>0) {                  
    /* allocation et mise à zéro */          
    dest = calloc(stopInd+1, 1);      
    /* vérification de la réussite de l'allocation*/  
    if(NULL != dest) {
        strncat(dest,src+pos,stopInd);            
    }
  }                                       
  return dest;
}


/*
	src : chaine de caractere a separer
	tab : tableau de chaines de caracteres
		chaque case contient un morceau de la chaine

	Cette fonction coupe une chaine de caractere a chaque espace ou virgule
	chaque morceau est stocke dans tab
*/
void stringSplit(char *str, char tab[NBOPERANDE][TAILLEOPERANDE]){
	int cpt = 0, i; 		//cpt 		: compteur qui permet de reperer les separateurs
	char *strCpy = str;		//strCpy 	: sauvegarder str, car sa valeur est modifiee  
	int indexTab = 0; 		//indexTab  : compteur pour stocker le morceau i dans la i-1e-ieme case de tab
	char index;				//index 	: vaut chaque caratere de str un par un
	do{
		index = str[cpt];
		if(index == ' ' || index == ',' || index == '\0'){ 
			strncpy(tab[indexTab], str, cpt); 				//Copie du 1er au cpt-ieme-1 caractere de str dans tab[0], tab[1], ... tab[3]
			if(cpt < TAILLEOPERANDE)
				tab[indexTab][cpt] = '\0';					//Si la chaine copiee ne fait pas TAILLEOPERANDE caratere
			str = substr(str, cpt+1, strlen(str));			//On coupe 
			indexTab++;										
			cpt = 0;										//On reset cpt car on a coupe str
		}
		cpt++;
	}while(index != '\0'); 
	if(indexTab != NBOPERANDE){
		for(i = indexTab; i < NBOPERANDE;i++){
			tab[i][0] = '\0';
		}
	}

	str = strCpy;
}

int main(int argc, char **argv){
	char tab[NBOPERANDE][TAILLEOPERANDE];
	char *test = "ADfzubeofbo rufb";
	stringSplit(test, tab);

	printf("%s\n",tab[0]);
	printf("%s\n",tab[1]);
	printf("%s\n",tab[2]);
	printf("%s\n",tab[3]);

	return 0;
}
