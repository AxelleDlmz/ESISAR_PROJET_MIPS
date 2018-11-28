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


// char ConvertirEnHexa(char * binaire){
// 	int i = 0;
// 	int res = 0;
// 	char lettre[] = {'A','B','C','D','E','F'};
// 	while (binaire[i]!='\0'){
// 		res += (binaire[i]-'0')*Puissance(2,i);
// 		printf("%i\n",res);
// 		i++;
// 	}
// 	if(res>9){
// 		res -= 10;
// 		printf("%c\n", lettre[res]);
// 		return lettre[res];
// 	}else{
// 		printf("%i\n",  i );
// 		return (char)i;
// 	}
// }

void ConvertirEnHexa(char * binaire, char * retour){
	char * tmp;
	int ret;
	ret = strtoul(binaire, &tmp ,2);
	printf("EN BINAIRE > %i\n", ret);
	sprintf(retour,"%04x",ret);
	printf("EN HEXA > %s\n",retour);
}


int main(int argc, char const *argv[])
{
	char retour[10];
	/*ConvertirEnHexa("1100",retour);
	printf("(%i)\n",Puissance(2,3) );*/
	ConvertirEnHexa("00000000010010010000100000100000",retour);

	//490820

	return 0;

}