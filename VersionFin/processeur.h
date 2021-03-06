#ifndef __PROCESSEUR_H
#define __PROCESSEUR_H
typedef struct{
	int operande1;
	int operande2;
	int operande3;
	char * operateur;
} instruction;

void int2StrBinaire(int donnee, char *ret);
void recupererBits(int deb, int fin, int donnee, char *ret);
int prochaineInstruction();
int char2IntOps(char * op);
void executerInstruction(instruction instr);
instruction decoderInstruction (int donnee);

#endif