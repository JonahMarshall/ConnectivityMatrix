//
// Created by Jonah on 2018-09-28.
//
#pragma once
#ifndef INC_3512ASSIGNMENT1_CMATRIX_HPP
#define INC_3512ASSIGNMENT1_CMATRIX_HPP

#endif //INC_3512ASSIGNMENT1_CMATRIX_HPP

#include "matrix.hpp"
/*
 * A Class to represent a special type of matrix called a connectivity matrix
 *          All initial values should be 0 or 1,
 *          other values will not return the expected result during full_process
 */
class cmatrix : public matrix {

public:
    /*
     * Inherits all constructors from matrix class
     */
    using matrix::matrix;

    /*
     * A Probability for a "random" walk
     */
    static constexpr double p = 0.85;

    /*
     * Turns a connectivity matrix into a Stochastic matrix
     * by finding the importance
     */
    cmatrix& find_imp();

    /*
     * Turns a Stochastic matrix into a transition matrix
     */
    cmatrix& find_tran();

    /*
     * Applies the markov process to a transition matrix
     *          returns a column matrix
     */
    cmatrix markov();

    /*
     * Same as markov, but prints out all rank matrices and the difference between (*this * rank) and rank
     */
    cmatrix printed_markov();

    /*
     * Puts a connectivity matrix through the full process to
     * become the result matrix representing the probability of each
     * page being visited
     *          returns a column matrix that is the result
     */
    cmatrix full_process();

    /*
     * Same as full_process, but also shows the user the different matrices made on the way
     */
    cmatrix printed_full_process();

    /*
     * Prints out a result matrix in a specific format
     */
    void print_result() const;

    //The << operator does not need to be re-declared since it is an operator, even though it is a friend class
};