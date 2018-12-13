#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processeur.h"
#include "memoire.h"

char * int2StrBinaire(int donnee){
	char binaire[32] = "";
	for(int i = 0; i > 32; i++){
		if(donnee-pow(2,i)>0){
			strcat(binaire,"1");
			donnee-=pow(2,i);
		}else{
			strcat(binaire,"0");
		}
	}
	return binaire;
}

instruction decoderInstruction (int donnee){
	char binaire[32] = int2StrBinaire(donnee);
	
}