#include <tclap/CmdLine.h>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv){
	
	/*First we have to decide which way we are going to use the programm
	* Do we give the PMW matrix and a treshold T and receive the positions
	* Or do we give the positions and the length of the motif and receive the PMW matrix*/

	
	try {  
		
		TCLAP::CmdLine cmd("Motifs Génomique .1");
		 
		 //We decided which executionType
		TCLAP::SwitchArg matrixToPositions("P","Position","Output will be positions",false);
		TCLAP::SwitchArg positionsToMatrix("W","PositionWeightMatrix","Output will be a PWM",false);
		cmd.xorAdd(matrixToPositions,positionsToMatrix);
		
		//We give the name of the fasta file
		TCLAP::ValueArg<std::string> fastafile("f","fastafile","What is the name of the file containing the genome ?",true,"fastafile.txt","string");
		cmd.add(fastafile);
		
		//We give the name of the file which contains the matrix
		TCLAP::ValueArg<std::string> matrixfile("m","matrixfile","What is the name of the file containing the matrix ?",true,"matrixfile.txt","string");
		cmd.add(matrixfile);
		
		//We give the name of the Bed file
		TCLAP::ValueArg<std::string> bedfile("b","bedfile","What is the name of the bed file indicating the positions?",true,"bedfile.txt","string");
		cmd.add(bedfile);
		
		//We give the value of Treshold or Length
		TCLAP::ValueArg<int> treshold("t","treshold","What is the Treshold you want to fix?",true,1,"int");
		TCLAP::ValueArg<int> length("l","length","What is the length of the motif?",true,1,"int");
		cmd.xorAdd(treshold,length);


		cmd.parse( argc, argv );

		//Handling exception
		if(matrixToPositions.getValue() and length.isSet()){
			TCLAP::ArgException e1("Lack of coherence between argument and Programm Execution type specifier","length");
			throw e1;
		}else if(positionsToMatrix.getValue() and treshold.isSet()){
			TCLAP::ArgException e2("Lack of coherence between argument and Programm Execution type specifier","treshold");
			throw e2;
		}

		//Little Test
		if(matrixToPositions.getValue()){

				std::cout	<<"==First execution type"<<std::endl
							<<"Matrix will be taken from : "<<matrixfile.getValue()<<std::endl
							<<"Treshold is : "<<treshold.getValue()<<std::endl
							<<"Positions will be pasted in : "<<bedfile.getValue()<<std::endl;
		}else{
				std::cout	<<"==Second execution type"<<std::endl
							<<"Positions will be taken from : "<<bedfile.getValue()<<std::endl
							<<"Length of the Motif is : "<<length.getValue()<<std::endl
							<<"Matrix will be pasted in : "<<matrixfile.getValue()<<std::endl;
		}
		
		std::cout<<"Genome will be found in :"<<fastafile.getValue()<<std::endl;
		
	} catch (TCLAP::ArgException &e)  
	{ std::cerr << "error: " << e.error() << " for " << e.argId() << std::endl; }
	
}
