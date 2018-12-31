#include <stdlib.h>
#include <stdio.h>
#include "registres.h"


void NettoyerRegistres(){
	int i=0;
	for(i=0;i<=34;i++){
		Registres[i]=0;
	}
}


int LireRegistre(int index){
	return Registres[index];
}

void EcrireRegistre(int index, int donnee){
	if(donnee <= 2147483648 && donnee >= -2147483647) /* <= 2^31 && >= -(2^31-1)*/
		Registres[index]=donnee;
	else
		printf("[EcrireRegistre] Impossible d'ecrire car le nombre %d est trop grand\n",donnee );
}

void AfficherRegistres(){
	int i=0;

	for(i=0;i<=29;i+=3){
		printf("%s%d%s%d\t\t\t%s%d%s%d\t\t\t%s%d%s%d\n","R",i," = ",Registres[i],
														"R",i+1," = ",Registres[i+1],
														"R",i+2," = ",Registres[i+2]);
	}
	printf("%s%s%d\t\t\t%s%s%d\n","R30"," = ",Registres[30],"R31"," = ",Registres[31]);


	printf("%s%d\t\t\t%s%d\t\t\t%s%d\n","PC = ",Registres[32],
										"HI = ",Registres[33],
										"L0 = ",Registres[34] );
	
}
