#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <cmath>
#incdlue <vector>



class Matrix {

private:
    std::vector<std::vector<double> > matrix;
    
public:
    vector<vector<double> > getPMW(vector<string> DNAsequences, int length);
    
    double score (Matrix m, std::string DNAsequence, double limit);
    
    size_t getLenghtMotif();
    
    double testPosition();
}


#endif 
