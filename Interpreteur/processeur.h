typedef struct instruction instruction;
struct{
	int operande1;
	int operande2;
	int operande3;
	char * operateur;
} instruction;

instruction decoderInstruction(int donnee);
void executerInstruction(instruction inst);
