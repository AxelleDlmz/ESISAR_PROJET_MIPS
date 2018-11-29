#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NBOPERANDE 4
#define TAILLEOPERANDE 16


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
			}else{	//Determine la fin de fichier
				fclose(f);
				return -1;
			}
	}
	fclose(f);
	return -1;
}

int ecireUneLigneDansLeFichier(char * nomDuFichier, char * ligne){
	char tmp[strlen(ligne)+1];
	strcpy(tmp,ligne);
	strcat(tmp,"\n");
	FILE * f = fopen(nomDuFichier,"a");
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
  //free(dest);     
  return dest;
}

/*
	nombre = valeur immediate a concatener
	res    = chaine de bits qui correspond a la trame
*/
void ImmediateConcat(int nombre, char res[32]){
	int i=0;
	char result[16]="";

	for(i=15;i>=0;i--){
		if(nombre-pow(2,i) < 0){
			strcat(result, "0");
		}
		else if (nombre- pow(2,i) >=0){
			strcat(result, "1");
			nombre =nombre-pow(2,i);
		}	
	}

	strcat(res,result);
	printf("{result}%s\n", res);
}

/*
	Prends en parametre un nombre binaire sous forme d'une chaine de char --> "00101100111001"
	et retourne (dans le parametre retour) une chaine de char au format hexa (sur 8 bits)
*/
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

void traitementCommande(char tab[4][16], char res[8]){
	char result[32]= "";
	char resultHex[8] = "";
	char *numReg = (char*)malloc(sizeof(char)*2);
	int numRegI;

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

			//printf("%s\n", result);

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


			//printf("%s\n", result);
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

			//printf("%s\n", result);
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

			//printf("%s\n", result);
		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}				
	}
	else if(strcmp(tab[0], "SRL") == 0){
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
			strcat(result, "000010");

			//printf("%s\n", result);
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

			//printf("%s\n", result);

		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}

	} /* TODO SYSCALL */
	else if(strcmp(tab[0], "NOP") == 0){
		if(tab[1][0] == '\0' && tab[2][0] == '\0' && tab[3][0] == '\0'){
			strcat(result, "00000000000000000000000000000000");

			//printf("%s\n", result);
		}
		else{
			printf("%s\n", "Erreur : parametres");
			exit(1);
		}
	}
	else if (strcmp(tab[0],"ADDI") == 0){ //NORMAL
		if(tab[1][0] == '$' && tab[2][0] == '$' && tab[3][0] == '#'){
			strcat(result,"001000");

			numReg = substr(tab[2], 1, strlen(tab[2]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);

			numReg = substr(tab[1], 1, strlen(tab[1]));
			numRegI = atoi(numReg);
			strcat(result, regBits[numRegI]);
			


			char* nombre;
			int numeroD;
			nombre = substr(tab[3],1,strlen(tab[3]));
			numeroD=atoi(nombre);
			if(numeroD>65535){
				printf("%s\n","Erreur : Valeur immediate trop grande (>65535)" );
				exit(1);
			}

			ImmediateConcat(numeroD, result);

		}
		else
			printf("%s\n", "Erreur : parametres");
	}
	/*else if(strcmp(tab[0], "J") == 0){ // NORMAL 
		if(strlen(tab[1]) < 7 && tab[2][0] == '\0' && tab[3][0] == '\0'){
			strcat(result, "00001000");


		}
		else
			printf("%s\n", "Erreur : parametres");
	}*/
	else{
		printf("%s%s\n", "Erreur : je ne connais pas l'instruction ", tab[0]);
		exit(1);
	}

	
	BinToHex(result, resultHex);
	printf("%s\n", resultHex);

	free(numReg);
	strcpy(res,resultHex);

}	


int main(int argc, char **argv){

	char tab[NBOPERANDE][TAILLEOPERANDE];
	char res[8] = "";
	char *testADD = "ADD $1,$2,$9";
	char *testDIV = "DIV $16,$31";
	char *testMFHI = "MFHI $7";
	char *testSLL = "SLL $2,$5,#15";


	stringSplit(testADD, tab);
	traitementCommande(tab, res);
	if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
		printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
		exit(1);
	}

	stringSplit(testDIV, tab);
	traitementCommande(tab, res);
	if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
		printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
		exit(1);
	}

	stringSplit(testMFHI, tab);
	traitementCommande(tab, res);
	if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
		printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
		exit(1);
	}

	stringSplit(testSLL, tab);
	traitementCommande(tab, res);
	if(ecireUneLigneDansLeFichier("./out.txt", res) == -1){
		printf("%s%s\n", "Erreur : ecriture dans ", "out.txt");
		exit(1);
	}

	return 0;
}
//20a2000f
//20A20000