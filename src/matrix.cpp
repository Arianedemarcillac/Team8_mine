#include "matrix.hpp"

std::vector<std::vector<double> > Matrix::getPMW(std::vector <std::string> DNAsequences, int length)
{
    Matrix pmw; //matrice à retourner de taille (LengthMotif x 4)

    for (size_t i(0); i < length; ++i) //on boucle selon la i-eme valeur du string
    {
        int count_A(0);
        int count_T(0);
        int count_G(0);
        int count_C(0);
        
        for (size_t j(0); j<DNAsequences.size(); ++j) //on boucle selon la j-ème composante de notre vecteur de string
        {
            if (DNAsequences[j][i]==A){
                ++count_A;
            }
			
			if (DNAsequences[j][i]==C){
                ++count_C;
            }
            
            if (DNAsequences[j][i]==G){
                ++count_G;
            }
            
            if (DNAsequences[j][i]==T){
                ++count_T;
				}
        }
        
        int total = count_A+count_T+count_G+count_C;
        double proba_A = ((count_A/total)+0.25)/(DNAsequence.size()+1);
        double proba_T = ((count_T/total)+0.25)/(DNAsequence.size()+1);
        double proba_G = ((count_G/total)+0.25)/(DNAsequence.size()+1);
        double proba_C = ((count_C/total)+0.25)/(DNAsequence.size()+1);
        std::vector <double> all_proba {proba_A,proba_C,proba_G, proba_T}; //CHANGER L4ORDE ICI
        
        for (size_t t(0); t<all_proba.size(); ++t) //ajoute pour chaque ligne les 4 probabilités
        {
            pmw.matrix[i][t].push_back(all_proba[t]);
        }

    }
    return pmw.matrix;
}

double Matrix::score(Matrix m, std::string DNAsequence, double limit){  //limit=seuil T
    
    double score(0);
    
    for (size_t i(0); i < DNAsequence.size(); ++i){
       
		if(DNAsequence[i] == A){
           score += (2+log2(m.matrix[i][0]));
		}
        
        if(DNAsequence[i] == C)
        {
            score += (2+log2(m.matrix[i][1]));
        }
        
        if(DNAsequence[i] == G)
        {
            score += (2+log2(m.matrix[i][2]));
        }
        
        if(DNAsequence[i] == T)
        {
            score += (2+log2(m.matrix[i][3]));
        }
    }
    
    try{
        if (score < limit){
            throw std::string("Score is lower than the limit");
			} 
        else {
            return score;
			}
        
        catch(std::string const& e){
            std::cerr << e << std::endl;
            return 0;
			}
		}
}


