#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "traducteurHexa.h"

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

int lireUneLigneDuFichier(char * nomDuFichier, char * ligneRetournee, long * ptr){
	FILE * f = fopen(nomDuFichier,"r");
	if(f != NULL){
		fseek(f,*ptr, SEEK_SET);
			if(fgets(ligneRetournee, 1000,f)!=NULL){
				* ptr = ftell(f);
				fclose(f);
				return 1;
			}else{	/*Determine la fin de fichier*/
				fclose(f);
				return -1;
			}
	}
	fclose(f);
	return -1;
}

int ecireUneLigneDansLeFichier(char * nomDuFichier, char * ligne){
	/*char tmp[strlen(ligne)+1];*/
	char *tmp = malloc(sizeof(char)*strlen(ligne)+1);
	FILE * f;
	strcpy(tmp,ligne);
	strcat(tmp,"\n");
	f = fopen(nomDuFichier,"a");
	if(f==NULL){
		fclose(f);
		return -1;
	}else{
		fputs(tmp,f);
		fclose(f);
		return 1;
	}
}

void viderLeFichier(char * nomDuFichier){
	FILE * f = fopen(nomDuFichier,"w");
	fclose(f);
}	


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

/*	nombre = valeur immediate a concatener
	res    = chaine de bits qui correspond a la trame */

void ImmediateConcat(int nombre, char res[32]){
	int i=0;
	char result[16]="";
	if(nombre>0){
		for(i=15;i>=0;i--){
			if(nombre-pow(2,i) < 0){
				strcat(result, "0");
			}
			else if (nombre- pow(2,i) >=0){
				strcat(result, "1");
				nombre =nombre-pow(2,i);
			}	
		}
	}else{																			
		nombre=65536+nombre;									/*Pour la partie négative en complément a deux, pour ne pas réaliser une autre fonction*/
		for(i=15;i>=0;i--){										/*On peut dire que ne nombre négatif peut se convertir comme le maximum (2^16) moins la valeur*/
			if(nombre-pow(2,i) < 0){							/*absolu du nombre*/
				strcat(result, "0");
			}
			else if (nombre- pow(2,i) >=0){
				strcat(result, "1");
				nombre =nombre-pow(2,i);
			}	
		}

	}

	strcat(res,result);
}


void ImmediateIndex(int nombre, char res[32]){
	int i=0;
	char result[26]="";
	if(nombre>0){
		for(i=25;i>=0;i--){
			if(nombre-pow(2,i) < 0){
				strcat(result, "0");
			}
			else if (nombre- pow(2,i) >=0){
				strcat(result, "1");
				nombre =nombre-pow(2,i);
			}	
		}
	}else{																			
		nombre=67108864+nombre;									/*Pour la partie négative en complément a deux, pour ne pas réaliser une autre fonction*/
		for(i=25;i>=0;i--){										/*On peut dire que ne nombre négatif peut se convertir comme le maximum (2^16) moins la valeur*/
			if(nombre-pow(2,i) < 0){							/*absolu du nombre*/
				strcat(result, "0");
			}
			else if (nombre- pow(2,i) >=0){
				strcat(result, "1");
				nombre =nombre-pow(2,i);
			}	
		}

	}

	strcat(res,result);
}

/*	Prends en parametre un nombre binaire sous forme d'une chaine de char --> "00101100111001"
	et retourne (dans le parametre retour) une chaine de char au format hexa (sur 8 bits) */

void BinToHex(char *binaire, char *retour){
	char * tmp;
	int ret, cpt;
	ret = strtoul(binaire, &tmp ,2);
	tmp = malloc(sizeof(char)*strlen(retour));
	sprintf(tmp,"%04x",ret);

	for(cpt = strlen(tmp); cpt < 8; cpt++){		/* On fait ça pour combler de 0 	*/
		strcat(retour, "0");					/* pour avoir une sortie sur 8 bits */
	}
	strcat(retour, tmp);

	free(tmp);
}


/*	src : chaine de caractere a separer
	tab : tableau de chaines de caracteres
		chaque case contient un morceau de la chaine

	Cette fonction coupe une chaine de caractere a chaque espace ou virgule
	chaque morceau est stocke dans tab */

void stringSplit(char *str, char tab[NBOPERANDE][TAILLEOPERANDE]){
	int cpt = 0, i; 		/*cpt 		: compteur qui permet de reperer les separateurs					*/
	char *strCpy = str;		/*strCpy 	: sauvegarder str, car sa valeur est modifiee						*/  
	int indexTab = 0; 		/*indexTab  : compteur pour stocker le morceau i dans la i-1e-ieme case de tab 	*/
	char index;				/*index 	: vaut chaque caratere de str un par un 							*/
	do{
		index = str[cpt];
		if(index == '_' || index == ' ' || index == ',' || index == '(' || index == ')' || index == '\0'){ 
			strncpy(tab[indexTab], str, cpt); 				/*Copie du 1er au cpt-ieme-1 caractere de str dans tab[0], tab[1], ... tab[3]	*/
			if(cpt < TAILLEOPERANDE)
				tab[indexTab][cpt] = '\0';					/*Si la chaine copiee ne fait pas TAILLEOPERANDE caractere 						*/
			str = substr(str, cpt+1, strlen(str));			/*On coupe 																		*/
			indexTab++;										
			cpt = 0;										/*On reset cpt car on a coupe str 												*/
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

/* tab = tableau de chaine de char, qui contient chaque morceau de l'instruction
	--> exemple : tab[0] = "ADD", tab[1] = "$1", tab[2] = "$23", tab[3] = "$2"
   res = chaine de char qui contient le resultat en hexa */

void traitementCommande(char tab[4][16], char res[8]){
	char result[32]= "";
	char resultHex[8] = "";
	char *numReg = (char*)malloc(sizeof(char)*2);
	int numRegI;
	char* nombre;
	int numeroD;
	

	if(strcmp(tab[0], "ADD") == 0 || strcmp(tab[0], "AND") == 0 || strcmp(tab[0], "OR") == 0 ||		/* Regroupe toutes les trames speciales */
		strcmp(tab[0], "XOR") == 0 || strcmp(tab[0], "SUB") == 0 || strcmp(tab[0], "SLT") == 0){	/* qui ont 3 registres comme parametre  */
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

			if(strcmp(tab[0], "ADD") == 0)
				strcat(result, "100000");
			else if(strcmp(tab[0], "AND") == 0)
				strcat(result, "100100");
			else if(strcmp(tab[0], "OR") == 0)
				strcat(result, "100101");
			else if(strcmp(tab[0], "XOR") == 0)
				strcat(result, "100110");
			else if(strcmp(tab[0], "SUB") == 0)
				strcat(result, "100010");
			else if(strcmp(tab[0], "SLT") == 0)
				strcat(result, "101010");
			else{
				printf("%s\n", "Erreur");
				exit(1);
			}

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}
	}
	else if(strcmp(tab[0], "DIV") == 0 || strcmp(tab[0], "MULT") == 0){		/* Groupe les speciaux qui ont 	*/
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '\0'){		/* deux registres en parametres */
			strcat(result, "000000");

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			strcat(result, "0000000000");

			if(strcmp(tab[0], "DIV") == 0)
				strcat(result, "011010");
			else if(strcmp(tab[0], "MULT") == 0)
				strcat(result, "011000");

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}

	}
	else if(strcmp(tab[0], "MFHI") == 0 || strcmp(tab[0], "MFLO") == 0){		/* Groupe les speciaux qui ont 	*/
		if(tab[1][0] == '$' && tab[2][0] == '\0' && tab[3][0] == '\0'){			/* un registre en parametres	*/
			strcat(result, "0000000000000000");

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			strcat(result, "00000");

			if(strcmp(tab[0], "MFLO") == 0)
				strcat(result, "010010");
			else if(strcmp(tab[0], "MFHI") == 0)
				strcat(result, "010000");

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}
	}
	else if(strcmp(tab[0], "SLL") == 0){
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '#'){
			strcat(result, "00000000000");

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[3], 1, strlen(tab[3])); /* Ici, ce n'est pas un registre 		*/
			numRegI = atoi(numReg);						/* mais on utilise quand meme le tab 	*/
			strcat(result, regBits[numRegI]);			/* des reg pour faire la conversion 	*/
														/* car c'est un entier de 32 bits 		*/
			strcat(result, "000000");

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}				
	}
	else if((strcmp(tab[0], "SRL") == 0) || (strcmp(tab[0], "ROTR") == 0)){
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '#'){
			
			if(strcmp(tab[0],"SRL") == 0)
				strcat(result,"00000000000"); /* Opcode */
			else if (strcmp(tab[0],"ROTR") == 0)
				strcat(result,"00000000001"); /* Opcode */
			else{
				printf("%s\n", "Erreur");
				exit(1);
			}


			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[3], 1, strlen(tab[3])); /* Ici, ce n'est pas un registre 		*/
			numRegI = atoi(numReg);						/* mais on utilise quand meme le tab 	*/
			strcat(result, regBits[numRegI]);			/* des reg pour faire la conversion 	*/
														/* car c'est un entier de 32 bits 		*/
			strcat(result, "000010");

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}				
	}
	else if(strcmp(tab[0], "JR") == 0){
		if(tab[1][0] == '$' && tab[2][0] == '\0' && tab[3][0] == '\0'){
			strcat(result, "00000");

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			strcat(result, "000000000000000");

			strcat(result, "001000");

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}

	}
	else if(strcmp(tab[0], "NOP") == 0){
		if(tab[1][0] == '\0' && tab[2][0] == '\0' && tab[3][0] == '\0')
			strcat(result, "00000000000000000000000000000000");
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		} 
	}
	else if (strcmp(tab[0],"ADDI") == 0){ /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '#'){
			strcat(result,"001000");

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);
			
			nombre = substr(tab[3],1,strlen(tab[3]));
			numeroD=atoi(nombre);
			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}

			ImmediateConcat(numeroD, result);

		}
		else
			printf("%s\n", "Erreur : parametres");
	}
	else if (strcmp(tab[0],"LUI") == 0){ /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '#' && tab[3][0] == '\0'){
			strcat(result,"001111"); /* Opcode */
			strcat(result,"00000");  /* rien dedans */

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);
														/* all is ok */

			nombre = substr(tab[2],1,strlen(tab[2]));
			numeroD=atoi(nombre);

			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}


			ImmediateConcat(numeroD, result);

		}
		else
			printf("%s\n", "Erreur : parametres");
	}
	else if (strcmp(tab[0],"LW") == 0){ /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '#' && tab[3][0] == '$'){

			strcat(result,"100011"); /* OPcode */

			numReg = substr(tab[3], 1, strlen(tab[3])); 	/* base */
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));		/* registre */
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			nombre = substr(tab[2],1,strlen(tab[2]));
			numeroD=atoi(nombre);

			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}


			ImmediateConcat(numeroD, result);
		}
		else
			printf("%s\n", "Erreur : parametres");
	}

	else if (strcmp(tab[0],"SW") == 0){ /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '#' && tab[3][0] == '$'){


			strcat(result,"101011"); /* OPcode */


			numReg = substr(tab[3], 1, strlen(tab[3])); 	/* base */
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));		/* registre */
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			nombre = substr(tab[2],1,strlen(tab[2]));
			numeroD=atoi(nombre);

			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}


			ImmediateConcat(numeroD, result);
		}
		else
			printf("%s\n", "Erreur : parametres");
	}



	/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
	else if ((strcmp(tab[0],"BEQ") == 0) || (strcmp(tab[0],"BNE") == 0)){ /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '#'){
			
			if(strcmp(tab[0],"BEQ") == 0)
				strcat(result,"000100"); /* Opcode */
			else if (strcmp(tab[0],"BNE") == 0)
				strcat(result,"000101"); /* Opcode */
			else{
				printf("%s\n", "Erreur");
				exit(1);
			}

			

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);
			
			nombre = substr(tab[3],1,strlen(tab[3]));
			numeroD=atoi(nombre);
			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}

			ImmediateConcat(numeroD, result);

		}
		else
			printf("%s\n", "Erreur : parametres");
	}

	else if ((strcmp(tab[0],"BGTZ") == 0) || (strcmp(tab[0],"BLEZ") == 0)) { /* NORMAL */
		if(tab[1][0] == '$' && tab[2][0] == '#' && tab[3][0] == '\0'){
			
			if(strcmp(tab[0],"BGTZ") == 0)
				strcat(result,"000111"); /* Opcode */
			else if (strcmp(tab[0],"BLEZ") == 0)
				strcat(result,"000110"); /* Opcode */
			else{
				printf("%s\n", "Erreur");
				exit(1);
			}

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);
														/* all is ok */
			strcat(result,"00000");  /* rien dedans */

			nombre = substr(tab[2],1,strlen(tab[2]));
			numeroD=atoi(nombre);

			if(numeroD>32767 || numeroD<-32768){
				printf("%s\n","Erreur : Valeur immediate trop grande (>32767) ou trop petite (<-32768" );
				exit(1);
			}

			ImmediateConcat(numeroD, result);

		}
		else
			printf("%s\n", "Erreur : parametres");
	}

	else if ((strcmp(tab[0] ,"J") == 0) || (strcmp(tab[0] ,"JAL") == 0)){
		if (tab[1][0] == '#' && tab[2][0] == '\0' && tab[3][0] == '\0'){

			if(strcmp(tab[0],"J") == 0)
				strcat(result,"000010"); /* Opcode */
			else if (strcmp(tab[0],"JAL") == 0)
				strcat(result,"000011"); /* Opcode */
			else{
				printf("%s\n", "Erreur");
				exit(1);
			}
	
			nombre = substr(tab[1],1,strlen(tab[1]));
			numeroD=atoi(nombre);

			if(numeroD>33554431 || numeroD<-33554432){
				printf("%s\n","Erreur : Valeur immediate trop grande (>33554431) ou trop petite (<-33554432" );
				exit(1);
			}

			ImmediateIndex(numeroD, result);
		}
	}





	else{
		printf("%s%s\n", "Erreur : je ne connais pas l'instruction ", tab[0]);
		exit(1);
	}

	
	BinToHex(result, resultHex);
	free(numReg);
	strcpy(res,resultHex);

}