#include <stdlib.h>
#include <stdio.h>
#include "memoire.h"

void initialiserMemoire(){
	int i;
	for(i = 0; i < TAILLEMEMOIRE ; i++){
		Memoire[i].valide = 0;
	}
}

