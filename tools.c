#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int ChercherDansTableau(char * src, char ** tab){
	int taille = sizeof(tab)/sizeof(tab[0]);
	for(int i = 0; i < taille; i++){
		if(tab[i]==src){
			return i;
		}
	}
	return -1;
}

int Puissance(int a, int b){
	int res = 1;
	while(b!=0){
		res = res*a;
		b--;
	}
	return res;
}


void ConvertirEnHexa(char * binaire, char * retour){
	char * tmp;
	int ret;
	ret = strtoul(binaire, &tmp ,2);
	printf("EN BINAIRE > %i\n", ret);
	sprintf(retour,"%04x",ret);
	printf("EN HEXA > %s\n",retour);
}

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
		


int main(int argc, char const *argv[])
{
	char retour[10];
	/*ConvertirEnHexa("1100",retour);
	printf("(%i)\n",Puissance(2,3) );*/
	ConvertirEnHexa("00000000010010010000100000100000",retour);

	//490820

	char ligne[1000];
	long ptr = 0;
	int i = 0;

	while(lireUneLigneDuFichier("./test.txt",ligne, &ptr)!=-1){
		printf("%s\n",ligne);  	
		i++;
	}

	viderLeFichier("./ecritureTest.txt");
	ecireUneLigneDansLeFichier("./ecritureTest.txt","coucou");
	ecireUneLigneDansLeFichier("./ecritureTest.txt","salut");

	return 0;
}

