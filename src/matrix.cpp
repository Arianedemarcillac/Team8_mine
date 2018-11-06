#include "matrix.hpp"

// C'est pas très beau, je suis d'accord, mais juste être d'accord pour la conception de la méthode

std::vector<std::vector<double> > Matrix::getPMW(std::vector <std::string> DNAsequence)
{
    std::vector<std::vector<double> > pmw; //matrice à retourner de taille (LengthMotif x 4)

    for (size_t i(0); i < getLenghtMotif(); ++i) //on boucle selon la i-eme valeur du string
    {
        int count_A(0);
        int count_T(0);
        int count_G(0);
        int count_C(0);
        
        for (size_t j(0); j<DNAsequence.size(); ++j) //on boucle selon la j-ème composante de notre vecteur de string
        {
            if (DNAsequence[j][i]==A)
            {
                ++count_A;
            }
        
            if (DNAsequence[j][i]==T)
            {
                ++count_T;
            }
        
            if (DNAsequence[j][i]==G)
            {
                ++count_G;
            }
        
            if (DNAsequence[j][i]==C)
            {
                ++count_C;
            }
        }
        
        int total = count_A+count_T+count_G+count_C;
        double proba_A = ((count_A/total)+0.25)/(DNAsequence.size()+1);
        double proba_T = ((count_T/total)+0.25)/(DNAsequence.size()+1);
        double proba_G = ((count_G/total)+0.25)/(DNAsequence.size()+1);
        double proba_C = ((count_C/total)+0.25)/(DNAsequence.size()+1);
        vector <double> all_proba {proba_A,proba_T,proba_G,proba_C};
        
        for (size_t t(0); t<all_proba.size(); ++t) //ajoute pour chaque ligne les 4 probabilités
        {
            pmw[i][t].push_back(all_proba[t]);
        }

    }
    
    return pmw;
    
}



