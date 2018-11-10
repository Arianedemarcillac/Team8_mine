#include "fastareader.h"
#incllde "matrix.hpp"
#include "fstream"
#include <string>
#include <iostream>
#include <vector>

struct Data {
	std::string key;
	int start;
	bool direction;
	std::string sequence;
	int score;
};

FastaReader::FastaReader (std::string file, std::string key)
 :file_(file), key_(key)
{}

FastaReader::~FastaReader()
{}

std ::string FastaReader::extract (int start, int end, bool dir)	//sens de lecture + endroit dans la séquence
{
	std::ifstream file_to_read (file_.c_str());  //ouverture du canal vers le fichier
	if (file_to_read.is_open())
	{
		bool stop (false);
		bool found (false);		//conditions d'arrêt
		std::string line;
		
		while ((std::getline(file_to_read, line)) && (!stop))
		{
			if (line[0] == '>')  //une ligne contenant une clé
			{
				if (!found)		//contrôle que la séquence n'aie pas déjà été trouvée
				{
					if (line.compare(1, line.size()-1, key_) == 0)
					{
						found = true;
					}
				}
				else
				{
					stop = true;
				}
			}
			else if (found)
			{
				seq_+=line;	//prends toute la séquence 
			}
		}
	}
	else
	{
		throw std::string("Error, file not open!");
	}
	
	if (!dir)		//est-ce que le fait d'inverser la séquence fait que l'on compte différemment ?? (ou tjrs de 5' à 3')
	{
		seq_=reverse();
	}
	return seq_.substr(start, end-1);
}

std::vector<Data> FastaReader::find_position (const int& length, Matrix m, double limit)
{
	std::ifstream file_to_read (file_.c_str());  //ouverture du canal vers le fichier
	if (file_to_read.is_open())
	{
		std::string line;
		std::vector<Data> result;
		
		while ((std::getline(file_to_read, line)))
		{
			int pos_start (0);
			
			if (line[0] == '>')  //une ligne contenant une clé
			{
				key_ = line.substr(1);
				pos_start=0;
			}
			else
			{
				bool direction (true);
				seq_+=line;	//prends toute la séquence
				std::string rev (reverse());	//pour parcourir les deux sens
				
				for (int i (0); i < seq_.size()-length; ++i)	//itère sur la séquence en prenant à chaque fois i comme point de départ
				{
					Matrix o;
					double score_1 (o.score(m, seq_.substr(i, i+length), limit));
					double score_2 (o.score(m, rev.substr(i, i+length),limit));		//les scores pour forward et reverse
					
					if (score_1 > 0 )
					{
						direction =true;
						Data data { key_; pos_start+i; direction; seq_.substr(i, i+length); score_1}
						result.push_back(data);
					}
					if (score_2 > 0)
					{
						direction = false;
						Data data { key_; pos_start+i; direction; rev.substr(i, i+length); score_2}
						result.push_back(data);
					}
				}
				pos_start = line.size()-1;		// au cas la séquence du chromosome est sur plusieurs lignes => ne pas recommencer à 0 pour les positions mais continuer.
			}
		}
		return result;
	}
	else
	{
		throw std::string("Error, file not open!");
	}

std::string FastaReader::reverse()
{
	std::string temp;
	
	for (int i (seq_.size()-1); i >= 0; --i)  // inverse le sens et la séquence
	{
		if (seq_[i] == 'A'){
			temp += 'T';
			}
		if (seq_[i] == 'T'){
			temp += 'A';
			}
		if (seq_[i] == 'G'){
			temp += 'C';
			}
		if (seq_[i] == 'C'){
			temp += 'G';
			}
	}
	return temp;
}


