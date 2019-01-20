/*instruction decoderInstruction (int donnee){
	
	instruction res;
	char binaire[32] = int2StrBinaire(donnee);
	char code[6] = recupererBits(0,6,binaire);
	char codeSpe[6] = "";
	char *oper1, *oper2, *oper3;


	if(code=="000000"){ 		// instruction spéciale
		
		code = recupererBits(26,32,binaire); // récupération des 6 derniers bits
		
		switch(code){

			case "000000":
				if(binaire == "00000000000000000000000000000000"){
					(*res).operande1 = ;
					(*res).operande2 = ;
					(*res).retour = ;
					(*res).operateur = "NOPE";

				}else{
					(*res).operande1 = ;
					(*res).operande2 = ;
					(*res).retour = ;
					(*res).operateur = "SLL";
				}

			case "100000": // ADD
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADD";
				break;

			case "100100": // AND
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "AND" ;
				break;

			case "011010": // DIV
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "DIV";
				break;

			case "001000": // JR
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "JR";
				break;

			case "010000": // MFHI
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MFHI";
				break;

			case "010010": // MFLO
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MFLO" ;
				break;

			case "011000": // MULT
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "MULT";
				break;

			case "100101": // OR
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "OR";
				break;

			case "100010" :
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "SUB";				
				break;

			case "100110":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "XOR";
				break;
				
		}
	}else{						//instruction non spéciale
		codeSpe = recupererBits(1,6,binaire);
		printf("%s%s\n","codeSpe :", codeSpe );
		switch(code){
			case "001000":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "ADDI";
				break;

			case "000111":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BEQ";
				break;

			case "000110":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BLEZ";
				break;

			case "000101":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "BNE";
				break;

			case "000010":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "J";
				break;

			case "000011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "JAL";
				break;

			case "001111":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "LUI";
				break;

			case "100011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "LW";
				break;

			case "101011":
				(*res).operande1 = ;
				(*res).operande2 = ;
				(*res).retour = ;
				(*res).operateur = "SW";
				break;
		}
	}
} */