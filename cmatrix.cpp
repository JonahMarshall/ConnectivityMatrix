//
// Created by Jonah on 2018-09-28.
//

#include "cmatrix.hpp"

/*
 * Turns a connectivity matrix into a Stochastic matrix
 * by finding the importance
 */
cmatrix& cmatrix::find_imp() {
    for(unsigned int i = 0; i<myMatrix.size(); i++){
        double total = 0;
        for(unsigned int j = 0; j<myMatrix.size(); j++)
            total += myMatrix[j][i];
        if(total != 0){
            for(unsigned int k = 0; k<myMatrix.size(); k++)
                myMatrix[k][i] /= total;
        }
        else{
            for(unsigned int k = 0; k<myMatrix.size(); k++)
                myMatrix[k][i] = (double)1/myMatrix.size();
        }
    }
    return *this;
}

/*
 * Turns a Stochastic matrix into a transition matrix
 */
cmatrix& cmatrix::find_tran(){
     cmatrix q = cmatrix((int)myMatrix.size());
     q++;
     q.find_imp();
    *this *= p;
    q *= 1-p;
    *this += q;
    return *this;
}

/*
 * Applies the markov process to a transition matrix
 *          returns a column matrix
 */
cmatrix cmatrix::markov(){
    double total = 0;
    cmatrix rank((int)(*this).myMatrix.size(), 1);
    rank++;

    while(*this * rank != rank) {
        rank *= *this;
    };

    for(unsigned int i = 0; i<rank.myMatrix.size(); i++)
        total += rank.myMatrix[i][0];

    for(unsigned int j = 0; j<rank.myMatrix.size(); j++)
        rank.myMatrix[j][0] /= total;

    return rank;
}

/*
 * Same as markov, but prints out all rank matrices and the difference between (*this * rank) and rank
 */
cmatrix cmatrix::printed_markov(){
    double total = 0;
    int count = 0;
    cmatrix rank((int)(*this).myMatrix.size(), 1);
    rank++;

    std::cout<<"Markov Process:\n"<<std::endl;

    while(*this * rank != rank) {
        std::cout<<"-- Loop "<<++count<<" --"<<std::endl;
        std::cout<<"Rank matrix:\n"<<rank<<std::endl;
        std::cout<<"Difference between (this * rank) and rank:\n"<<(*this * rank) - rank<<std::endl;

        rank *= *this;
    };

    for(unsigned int i = 0; i<rank.myMatrix.size(); i++)
        total += rank.myMatrix[i][0];

    for(unsigned int j = 0; j<rank.myMatrix.size(); j++)
        rank.myMatrix[j][0] /= total;

    return rank;
}

/*
 * Puts a connectivity matrix through the full process to
 * become the result matrix representing the probability of each
 * page being visited
 *          returns a column matrix that is the result
 */
cmatrix cmatrix::full_process() {
    cmatrix result;
    (*this).find_imp();

    (*this).find_tran();

    result = (*this).markov();

    return result;
}

/*
 * Does full process, and shows the user the different matrices made on the way
 */
cmatrix cmatrix::printed_full_process(){
    cmatrix result;

    std::cout<<"Connectivity Matrix:"<<"\n"<<*this<<std::endl;

    (*this).find_imp();
    std::cout<<"Stochastic Matrix:"<<"\n"<<*this<<std::endl;

    (*this).find_tran();
    std::cout<<"Transition Matrix:"<<"\n"<<*this<<std::endl;

    result = (*this).printed_markov();
    std::cout<<"Result Matrix:"<<"\n"<<result<<std::endl;

    return result;
}

/*
 * Prints out a result matrix in a specific format
 */
void cmatrix::print_result() const{
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for(unsigned int i = 0; i<myMatrix.size(); i++)
            std::cout<<"Page "<<alphabet[i]<<": "<<round(myMatrix[i][0]*10000)/100<<"%"<<std::endl;
}