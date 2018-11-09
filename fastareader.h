#ifndef FASTAREADER_H
#define FASTAREADER_H

#include <string>
#include "matrix.hpp"

class FastaReader {
	
public:

//Constructeur et destructeur
	FastaReader (std::string file, std::string key = "none");
	~FastaReader();

//fonctions pour lire le fichier et extraire la séquence demandée
	void extract(int start, int end, bool dir);
	std::vector<Data> find_position(const int& length, Matrix m, double limit);

private:

	std::string reverse ();
	
	std::string file_; //nom du fichier
	std::string key_;	//clé
	std::string seq_;	//séquence à afficher
};

#endif
