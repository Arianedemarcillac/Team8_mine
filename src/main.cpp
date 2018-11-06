#include <tclap/CmdLine.h>
#include <string>
#include <vector>

int main(int argc, char **argv){
	
	/*First we have to decide which way we are going to use the programm
	* Do we give the PMW matrix and a treshold T and receive the positions
	* Or do we give the positions and the length of the motif and receive the PMW matrix
	* For simplicity we could call it FindingPositions and CreatingMatrix*/

	
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
		
		//We give the value of Treshold/Length
		TCLAP::ValueArg<int> value("v","value","What is the Treshold/the length of the motif ?",true,1,"int");
		cmd.add(value);


		cmd.parse( argc, argv );

		std::cout<<fastafile.getValue()<<"/"<<matrixfile.getValue()<<"/"<<bedfile.getValue()<<"/"<<value.getValue()<<std::endl;
		
		if(matrixToPositions.getValue()){
			double Treshold(value.getValue());
		}else{
			size_t Length(value.getValue());
		}
		
	} catch (TCLAP::ArgException &e)  
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
	
}
