#include "matrix.hpp"


 //------------------------------------------------Constructors--------------------------------------------------------

 /*
  * Default constructor:
  *         initializes a 1x1 matrix with the value 0
  */
matrix::matrix() {
    dVec v;
    v.push_back(0.0);
    myMatrix.push_back(v);
}

/*
 * Constructor(int size):
 *          takes an int "size" and makes a size x size matrix where all values are 0
 */
matrix::matrix(int size) {
    dVec v;
    if(size>0) {
        for (int i = 0; i < size; i++)
            v.push_back(0.0);
        for (int j = 0; j < size; j++)
            myMatrix.push_back(v);
    }
    else
        throw std::invalid_argument("Size was less than 1");
}

/*
 * Constructor(int r, int c):
 *          takes two ints, r and c, and creates a matrix with
 *          r rows and c columns where all values are 0
 */
matrix::matrix(int r, int c) {
    dVec v;
    if(r && c > 0) {
        for (int i = 0; i < c; i++)
            v.push_back(0.0);
        for (int j = 0; j < r; j++)
            myMatrix.push_back(v);
    }
    else
        throw std::invalid_argument("Row or Column was less than 1");
}

/*
 * Constructor(vector<double> vec):
 *          takes a vector that has a perfect root and creates a root x root matrix
 */
matrix::matrix(dVec vec) {
    double d_sqrt = sqrt(vec.size());
    int i_sqrt = (int)d_sqrt;

    if (d_sqrt == i_sqrt) {
        for (int i = 0; i < i_sqrt; i++){
            dVec v(i_sqrt);
            myMatrix.push_back(v);
            for(int j = 0; j < i_sqrt; j++)
                myMatrix[i][j] = vec[(i_sqrt*i)+j];
        }
    }
    else{
        throw std::invalid_argument("Length of vector must be a perfect square");
    }
}
/*
 * Constructor(double[] arr, int size):
 *          takes an array of doubles that has a perfect root size and creates root x root matrix
 *          fills matrix with values from array
 */
matrix::matrix(double * d, int size) {
    double d_sqrt = sqrt(size);
    int i_sqrt = (int) d_sqrt;
    if (d_sqrt == i_sqrt) {
        for (int i = 0; i < i_sqrt; i++) {
            dVec v(i_sqrt);
            myMatrix.push_back(v);
            for (int j = 0; j < i_sqrt; j++)
                myMatrix[i][j] = d[(i_sqrt * i) + j];
        }
    }
    else {
        throw std::invalid_argument("Length of vector must be a perfect square");
    }
}

/*
 * Constructor(const char* filename):
 *          takes a filename and trys to open a file of that name
 *          if successful turns each line into a vector and then adds each vector to the matrix
 */
matrix::matrix(const char* filename){
    using namespace std;
    string line;
    ifstream file{filename};
    if(!file){
        cerr<<"Unable to open file"<<endl;
        exit(1);
    }
    while(getline(file, line)){
        dVec v;
        stringstream ss(line);
        double num = 0.0;
        while(ss>>num)
            v.push_back(num);
        myMatrix.push_back(v);
    }

    file.close();
}

//-------------------------------------------------------------------------------------------------------------------

/*
 * Set & Get Values
 */
void matrix::set_value(int r, int c, double val) {
    myMatrix[r][c] = val;
}

double matrix::get_value(int r, int c) const{
    return myMatrix[r][c];
}

/*
 * Sets all values to 0
 */
void matrix::clear() {
    for(unsigned int i = 0; i<myMatrix.size(); i++){
        for (unsigned int j = 0; j<myMatrix[i].size() ; ++j) {
            myMatrix[i][j] = 0.0;
        }
    }
}

/*
 * Destructor
 */
matrix::~matrix(){}


 //-------------------------------------------------Operators-------------------------------------------------------


                                                //Comparison
/*
 * Allows for == to be used on two matrices
 *          returns true the matrices have the same values in all places
 *          else returns false
 */
bool matrix::operator==(const matrix &m) const{
    if(myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size() ){
        for(unsigned int i = 0; i<myMatrix.size(); i++){
            for(unsigned int j = 0; j<myMatrix[i].size(); j++)
                if(std::abs(myMatrix[i][j] - m.myMatrix[i][j]) >=  TOLERANCE)
                    return false;
        }
        return true;
    }
    else
        throw std::invalid_argument("Matrices are not the same size");
}

/*
 * Allows for != to be used on two matrices
 *          returns true if the matrices do not have the same values in all places
 *          else returns false
 */
bool matrix::operator!=(const matrix &m) const{
    if (myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size()) {
        for (unsigned int i = 0; i < myMatrix.size(); i++) {
            for (unsigned int j = 0; j < myMatrix[i].size(); j++)
                if (std::abs(myMatrix[i][j] - m.myMatrix[i][j]) <= TOLERANCE)
                    return false;
        }
        return true;
    } else
        throw std::invalid_argument("Matrices are not the same size");
}

                                            //Multiplication

/*
 * Allows for the multiplication operator to multiply two matrices together
 *                  returns a new matrix
 */
matrix matrix::operator*(matrix &m) const{
    if(myMatrix[0].size() == m.myMatrix.size()) {
        matrix newmat = matrix(int(myMatrix.size()), (int(m.myMatrix[0].size())));
        for(unsigned int i = 0; i<m.myMatrix[0].size(); i++){ //
            for(unsigned int j = 0; j<myMatrix.size(); j++){
                for(unsigned int k = 0; k<m.myMatrix.size(); k++)
                    newmat.myMatrix[j][i] += myMatrix[j][k] * m.myMatrix[k][i]; //
            }
        }
        return newmat;
    }
    else
        throw std::invalid_argument("Matrices are not compatible sizes for multiplication");
}

/*
 * Allows for the *= operator to be used on two matrices
 *              for a *= b, a's matrix will be changed
 */
matrix& matrix::operator*=(matrix &m) {
    *this=  m * *this;
    return *this;
}

/*
 * Allows for a matrix to be multiplied by a double
 * All values in matrix are multiplied by the double
 *          returns a new matrix
 */
matrix matrix::operator*(double num) const{
    matrix newmat = *this;
    for(unsigned int i = 0; i<myMatrix.size(); i++)
        for(unsigned int j = 0; j<myMatrix.size(); j++)
            newmat.myMatrix[i][j] *= num;
    return newmat;
}

/*
 * Allows for the *= operator to be used on a matrix and a double
 *      ex. matrix m *= double d
 */
matrix& matrix::operator*=(double num) {
    *this = *this * num;
    return *this;
}

                                                //Addition
/*
 * Allows for the addition operator to add two matrices together
 *                  returns a new matrix
 */
matrix matrix::operator+(matrix &m) const{
        if (myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size()) {
            matrix newmat(int(myMatrix.size()), int(myMatrix[0].size()));
            for (unsigned int i = 0; i < myMatrix.size(); i++) {
                for (unsigned int j = 0; j < myMatrix[i].size(); j++)
                    newmat.myMatrix[i][j] = myMatrix[i][j] + m.myMatrix[i][j];
            }
            return newmat;
        } else
            throw std::invalid_argument("Matrices are not the same size");
}

/*
 * Allows ++ to be used with a matrix
 *          increments all values in the matrix by one
 */
matrix& matrix::operator++() { //Prefix
    for(unsigned int i = 0; i<myMatrix.size(); i++){
        for(unsigned int j = 0; j<myMatrix[i].size(); j++)
            myMatrix[i][j] += 1.0;
    }
    return *this;
}

matrix matrix::operator++(int /*unused*/) { //Postfix
    matrix newmat = *this;
    ++(*this);
    return newmat;
}

/*
 * Allows for the += operator to be used on two matrices
 *              for a += b, a's matrix will be changed
 */
matrix& matrix::operator+=(matrix &m) {
    if (myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size()) {
        for (unsigned int i = 0; i < myMatrix.size(); i++) {
            for (unsigned int j = 0; j < myMatrix[i].size(); j++)
                myMatrix[i][j] = myMatrix[i][j] + m.myMatrix[i][j];
        }
        return *this;
    } else
        throw std::invalid_argument("Matrices are not the same size");
}

                                        //Subtraction
/*
 * Allows for the subtraction operator to subtract one matrix from another
 *                  returns a new matrix
 */
matrix matrix::operator-(matrix &m) const{
        if (myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size()) {
            matrix newmat(int(myMatrix.size()), int(myMatrix[0].size()));
            for (unsigned int i = 0; i < myMatrix.size(); i++) {
                for (unsigned int j = 0; j < myMatrix[i].size(); j++)
                    newmat.myMatrix[i][j] = myMatrix[i][j] - m.myMatrix[i][j];
            }
            return newmat;
        } else
            throw std::invalid_argument("Matrices are not the same size");
}

/*
 * Allows for -- to be used with a matrix
 *          decrements all values in the matrix by one
 */
matrix& matrix::operator--() {
    for(unsigned int i = 0; i<myMatrix.size(); i++){ //Prefix
        for(unsigned int  j = 0; j<myMatrix[i].size(); j++)
            myMatrix[i][j] -= 1.0;
    }
    return *this;
}

matrix matrix::operator--(int /*unused*/){ //Postfix
    matrix newmat = *this;
    --(*this);
    return newmat;
}

/*
 * Allows for the -= operator to be used on two matrices
 *              for a -= b, a's matrix will be changed
 */
matrix& matrix::operator-=(matrix &m) {
    if (myMatrix.size() == m.myMatrix.size() && myMatrix[0].size() == myMatrix[0].size()) {
        for (unsigned int i = 0; i < myMatrix.size(); i++) {
            for (unsigned int j = 0; j < myMatrix[i].size(); j++)
                myMatrix[i][j] = myMatrix[i][j] - m.myMatrix[i][j];
        }
        return *this;
    } else
        throw std::invalid_argument("Matrices are not the same size");
}



//--------------------------------------------------------------------------------------------------------------

            //Assignment
//(Jeff gave me permission to skip this as it is redundant with my implementation of matrix)
//matrix& matrix::operator=(const matrix &m) {}

