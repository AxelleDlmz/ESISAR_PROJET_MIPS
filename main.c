#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBOPERANDE 4
#define TAILLEOPERANDE 16

/*
	TODO :
		- Séparation entre le mode "special" et le mode "normal" dans le switch
		- creation d'un switch pour chacune des operations
		- conversion en hex de la chaine binaire
		- fautes "eliminatoire"
*/

char *opStrNorm[10] = {
		"ADDI", "BEQ" , "BGTZ", "BLEZ", 
		"BNE" , "J"	  , "JAL" , "LUI" ,
		"LW"  , "SW"  
	};

	char *opStrSpecial[16] = {
		"ADD" , "AND" , "DIV" , "JR"  , 
		"MFHI", "MFLO", "MULT", "NOP" ,
		"OR"  , "ROTR", "SLL" , "SLT" , 
		"SRL" , "SUB" , "SYSCALL", "XOR"
	};

	char *opBitsNorm[10] = {
		"001000", "000100", "000111", "000110",
		"000101", "000010", "000011", "001111",
		"100011", "101011"
	};

	char *opBitsSpecial[16] = {
		"100000", "100100", "011010", "001000",
		"010000", "010010", "011000", "000000",
		"100101", "000010", "000000", "101010",
		"000010", "100010", "001100", "100110"
	};

	char *regBits[32] = {
		"00000", "00001", "00010", "00011",
		"00100", "00101", "00110", "00111",
		"01000", "01001", "01010", "01011",
		"01100", "01101", "01110", "01111",
		"10000", "10001", "10010", "10011",
		"10100", "10101", "10110", "10111",
		"11000", "11001", "11010", "11011",
		"11100", "11101", "11110", "11111"
	};


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

void traitementCommande(char tab[4][16]){
	char result[32]= "";
	char *numReg = (char*)malloc(sizeof(char)*2);
	int numRegI;

	if(strcmp(tab[0], "ADD") == 0){
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '$'){
			strcat(result, "000000");

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[3], 1, strlen(tab[3]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			strcat(result, "00000");

			strcat(result, "100000");

			printf("%s\n", result);

		}
		else{
			printf("%s\n", "Erreur : parametres de ADD");
		}
	}
}


int main(int argc, char **argv){


	char tab[NBOPERANDE][TAILLEOPERANDE];
	char *test = "ADD $1,$2,$3";
	stringSplit(test, tab);
	traitementCommande(tab);
	

	/*printf("%s\n",tab[0]);
	printf("%s\n",tab[1]);
	printf("%s\n",tab[2]);
	printf("%s\n",tab[3]);*/

	return 0;
}
