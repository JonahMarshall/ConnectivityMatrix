//
// Created by Jonah on 2018-09-27.
//
#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#ifndef INC_3512ASSIGNMENT1_MATRIX_HPP
#define INC_3512ASSIGNMENT1_MATRIX_HPP

#endif //INC_3512ASSIGNMENT1_MATRIX_HPP

typedef std::vector<double> dVec;

/*
 * A Class to represent a two dimensional vector, known as a matrix
 *      Contains a two dimensional vector which is the objects actual matrix
 */
class matrix {
public:

    /*
     * Two dimensional vector, which is called a matrix
     */
    std::vector<dVec> myMatrix;

    /*
     * A value to represent the amount of difference acceptable when comparing doubles inside our matrices
     *
     * (Program works without this defined, using == or
     *          std::abs(a-b)<std::abs(std::min(a,b))*std::numeric_limits<double>::epsilon() instead,
     *  although the loop in markov will run significantly more times. For more accurate results and greater usage
     *  of function, replace with your own double equivalency check)
     */
     static constexpr double TOLERANCE = 0.0000001;

    //--------------------------------------Constructors---------------------------------------------

     /*
      * Default constructor:
      *         initializes a 1x1 matrix with the value 0
      */
    matrix();

    /*
     * Constructor(int size):
     *          takes an int "size" and makes a size x size matrix where all values are 0
     */
    matrix(int size);

    /*
     * Constructor(int r, int c):
     *          takes two ints, r and c, and creates a matrix with
     *          r rows and c columns where all values are 0
     */
    matrix(int r, int c);

    /*
     * Constructor(vector<double> vec):
     *          takes a vector of doubles that has a perfect root and creates a root x root matrix
     *          fills matrix with values from the vector
     */
    matrix(dVec vec);

    /*
     * Constructor(double[] arr, int size):
     *          takes an array of doubles that has a perfect root size and creates root x root matrix
     *          fills matrix with values from array
     */
    matrix(double d[], int size);

    /*
     * Constructor(const char* filename):
     *          takes a filename and tries to open a file of that name
     *          if successful turns each line into a vector and then adds each vector to the matrix
     */
    matrix(const char* filename);

    //---------------------------------------------------------------------------------------------------------

    /*
     * Set & Get Values
     */
    void set_value(int r, int c, double val);
    double get_value(int r, int c) const;

    /*
     * Sets all values to 0
     */
    void clear();

    /*
     * Destructor
     */
    ~matrix();


     //-----------------------------------------Operators----------------------------------------------------

                                             //comparison
    /*
     * Allows for == to be used on two matrices
     *          returns true the matrices have the same values in all places
     *          else returns false
     */
    bool operator==(const matrix &m) const;

    /*
     * Allows for != to be used on two matrices
     *          returns true if the matrices do not have the same values in all places
     *          else returns false
     */
    bool operator!=(const matrix &m) const;

                                            //addition
    /*
     * Allows ++ to be used with a matrix
     *          increments all values in the matrix by one
     */
    matrix& operator++(); //prefix
    matrix operator++(int /*unused*/); //postfix

    /*
     * Allows for the += operator to be used on two matrices
     *              for a += b, a's matrix will be changed
     */
    matrix& operator+=(matrix &m);

    /*
     * Allows for the addition operator to add two matrices together
     *                  returns a new matrix
     */
    matrix operator+(matrix &m) const;

                                        //subtraction
    /*
     * Allows for -- to be used with a matrix
     *          decrements all values in the matrix by one
     */
    matrix& operator--(); //prefix
    matrix operator--(int /*unused*/); //postfix

    /*
     * Allows for the -= operator to be used on two matrices
     *              for a -= b, a's matrix will be changed
     */
    matrix& operator-=(matrix &m);

    /*
     * Allows for the subtraction operator to subtract one matrix from another
     *                  returns a new matrix
     */
    matrix operator-(matrix &m) const;

            //multiplication
    /*
     * Allows for the multiplication operator to multiply two matrices together
     *                  returns a new matrix
     */
    matrix operator*(matrix &m) const;

    /*
     * Allows for the *= operator to be used on two matrices
     *              for a *= b, a's matrix will be changed
     */
    matrix& operator*=(matrix &m);

    /*
     * Allows for a matrix to be multiplied by a double
     * All values in matrix are multiplied by the double
     *          returns a new matrix
     */
    matrix operator*(double num) const;

    /*
     * Allows for the *= operator to be used on a matrix and a double
     *      ex. matrix m *= double d
     */
    matrix& operator*=(double num);

    //--------------------------------------------------------------------------------------------------------------

    //matrix& operator=(const matrix &m);

    /*
     * Output operator
     */
    friend std::ostream& operator<<(std::ostream& out, const matrix& mat){
        for(unsigned int i = 0; i<mat.myMatrix.size(); i++){
            out<<"{";
            for(unsigned int j = 0; j<mat.myMatrix[i].size(); j++){
                if(j != mat.myMatrix[i].size()-1)
                    out<<mat.myMatrix[i][j]<<",";
                else
                    out<<mat.myMatrix[i][j];
            }
            out<<"}"<<std::endl;
        }
        return out;
    }

};

