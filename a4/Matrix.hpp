//////////////////////////////////////////////
// 
// Your Name:  Nicholas Cheng
// 
// CS 368, Spring 2018
// Matrix.hpp
//
//////////////////////////////////////////////

#ifndef LECTURE9_MATRIX_HPP
#define LECTURE9_MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept> // includes runtime_error, which is a subclass of exception

/**
 * @brief This class derives from runtime_error
 *        It is thrown in the case of Non-postive matrix dimensions
 */
class NonPositiveDimensionException : public std::runtime_error {
public:
    // constructor that calls the base class constructor in its initializer list
    NonPositiveDimensionException() : std::runtime_error(
            "dimensions must be positive") {// no other code in the constructor
    }
};

/**
 * @brief This class derives from runtime_error
 *        It is thrown in the case of any dimension mismatch
 */
class DimensionMismatchException : public std::runtime_error {
public:
    DimensionMismatchException() : std::runtime_error("dimensions do not match") {
    }
};

/**
 * @brief This class derives from runtime_error
 *        It is thrown in the case of attempting to access an out-of-bounds index
 */
class RowIndexOutOfBoundsException : public std::runtime_error {
public:
    RowIndexOutOfBoundsException() : std::runtime_error("row index out of bounds") {
    }
};

///////////////////////////////////////////////////////
// DECLARATION OF THE MATRIX TEMPLATED CLASS
// YOU WILL NEED TO ADD MORE PROTOTYPES HERE
///////////////////////////////////////////////////////
template<typename T>
class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<T>> data;

public:
    Matrix();

    Matrix(int r, int c);

    void print() const;

    int getRows() const;

    int getCols() const;

    // two different [] operators, one for each side of an operator
    std::vector<T> &operator[](const int index);

    const std::vector<T> &operator[](const int index) const;

    // basic addition, subtraction, and multiplication operators
    const Matrix<T> operator+(const Matrix<T> &rhs) const;

    const Matrix<T> operator-(const Matrix<T> &rhs) const;

    const Matrix<T> operator*(const Matrix<T> &rhs) const;

    // compound assignment operators
    Matrix<T> &operator+=(const Matrix<T> &rhs);

    Matrix<T> &operator-=(const Matrix<T> &rhs);

    Matrix<T> &operator*=(const Matrix<T> &rhs);

    Matrix<T> &operator*=(const int scalar);

    //an additional overload for complex numbers
    Matrix<T> &operator*=(const std::complex<int> scalar);

    // equality operators
    const bool operator==(const Matrix<T> &rhs) const;

    const bool operator!=(const Matrix<T> &rhs) const;

    // friends
    // matrix multiplication operator, for scalar integers
    /**
     * @brief overrides the * operator for Matrix<T>
     *        specifically for scalar integers
     * @param scalar the integer we are multiplying the matrix by
     * @param rhs  the Matrix<T> to be multiplied by
     * @return the matrix resulting from the multiplication
     */
    friend const Matrix<T> operator*(int scalar, const Matrix<T> &rhs) {
        Matrix<T> result(rhs.rows, rhs.cols);
        // multiply every value of the matrix in place by the integer scalar
        for (int i = 0; i < rhs.rows; ++i) {
            for (int j = 0; j < rhs.cols; ++j) {
                result[i][j] = scalar * rhs[i][j];
            }
        }
        return result;
    }
    /**
     * @brief calls the other * override for Matrix<T> in correct order
     * @param scalar the integer we are multiplying the matrix by
     * @param rhs  the Matrix<T> to be multiplied by
     * @return the matrix resulting from the multiplication
     */
    friend const Matrix<T> operator*(const Matrix<T> &rhs, int scalar) {
        // call the other * operator in the correct order
        return scalar * rhs;
    }

    //matrix multiplication operator, for complex numbers
    /**
     * @brief overrides the * operator for Matrix<T>
     *        specifically for complex numbers
     * @param scalar the complex number we are multiplying the matrix by
     * @param rhs  the Matrix<T> to be multiplied by
     * @return the matrix resulting from the multiplication
     */
    friend const Matrix<T> operator*(std::complex<int> scalar, const Matrix<T> &rhs) {
        Matrix<T> result(rhs.rows, rhs.cols);
        // multiply every matrix value in place by the complex number
        for (int i = 0; i < rhs.rows; ++i) {
            for (int j = 0; j < rhs.cols; ++j) {
                result[i][j] = scalar * rhs[i][j];
            }
        }
        return result;
    }
    /**
     * @brief calls the other * override for Matrix<T> in correct order
     * @param scalar the complex number we are multiplying the matrix by
     * @param rhs  the Matrix<T> to be multiplied by
     * @return the matrix resulting from the multiplication
     */
    friend const Matrix<T> operator*(const Matrix<T> &rhs, std::complex<int> scalar) {
        // call the other * operator for complex numbers in the correct order
        return scalar * rhs;
    }

    /**
 * @brief overrides the << operator for Matrix<T>
 *        because this is a friend function, and because we have a templated class
 *        we need to define the function inside our class declaration
 * @param os the stream that we are using << with
 * @param obj  the Matrix<T> we are trying to insert into the stream
 * @return a non-const reference, which allows us to chain << operators
 */
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &obj) {
        for (auto rowIt = obj.data.begin(); rowIt != obj.data.end(); ++rowIt) {
            for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
                if (colIt != rowIt->end() - 1) {
                    os << *colIt << " ";
                } else {
                    os << *colIt;
                }
            }
            os << std::endl;
        }
        return os;
    }
};

///////////////////////////////////////////////////////
// IMPLEMENTATION OF THE MATRIX TEMPLATED CLASS
// YOU WILL NEED TO ADD MORE FUNCTION DEFINITIONS HERE
///////////////////////////////////////////////////////

/**
 * @brief default Constructor for Matrix<T>
 *        calls the other constructor through an initializer list
 */

template<typename T>
Matrix<T>::Matrix() : Matrix(1, 1) {
}


/**
 * @brief Constructor for Matrix<T>
 *        Matrices store their data in a single vector called data
 *        We assume the matrix will use row-major ordering
 * @param r the number of rows (non-negative)
 * @param c the number of cols (non-negative)
 */
template<typename T>
Matrix<T>::Matrix(int r, int c) {
    if (r <= 0 || c <= 0) {
        throw NonPositiveDimensionException();
    }
    rows = r;
    cols = c;
    data.resize(rows);
    for (int r = 0; r < rows; ++r) {
        data[r].resize(cols);
    }
}

/**
 * @brief prints out to the terminal the elements of this matrix
 *        we assume row-major ordering of the elements
 */
template<typename T>
void Matrix<T>::print() const {
    for (auto rowit = data.begin(); rowit != data.end(); ++rowit) {
        std::vector<T> rowData = *rowit;
        for (auto colit = rowData.begin(); colit != rowData.end(); ++colit) {
            if (colit != rowData.end() - 1)
                std::cout << *colit << " ";
            else
                std::cout << *colit;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief returns the matrix's number of rows
 *
 * @return number of rows in this matrix
 */
template<typename T>
int Matrix<T>::getRows() const {
    return rows;
}

/**
 * @brief returns the matrix's number of columns
 *
 * @return number of columns in this matrix
 */
template<typename T>
int Matrix<T>::getCols() const {
    return cols;
}

/**
 * @brief accesses the row index of this Matrix
 *        we assume row-major ordering and a start index of 0
 *        this non-const function returns a non-const reference
 * @param index     the index which corresponds to a vector (row) in the matrix
 * @return a non-const vector reference that is suitable for a Left-value
 */
template<typename T>
std::vector<T> &Matrix<T>::operator[](const int index) {
    if (index < 0 || index > this->rows) {
        throw RowIndexOutOfBoundsException();
    }
    return data[index];
}


/**
 * @brief accesses the row index of this Matrix
 *        we assume row-major ordering and a start index of 0
 * @param       the index which corresponds to a vector (row) in the matrix
 * @return      a const vector reference that is suitable for a Right-value
 */
template<typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
    if (index < 0 || index > this->rows) {
        throw RowIndexOutOfBoundsException();
    }
    return data[index];
}

/**
 * @brief adds the Matrix<T> on the right side of the + operator to the matrix on the left
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the + operator
 * @return a const Matrix that represents the sum
 */
template<typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) const {
    // matrix the function is being called on
    Matrix<T> lhs = *this;
    // check dimensions and throw exception if there is a mismatch
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        throw DimensionMismatchException();
    }
    int rows = rhs.rows;
    int cols = rhs.cols;
    Matrix<T> result(rows, cols);
    // add each matrix together elementwise
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return result;
}

/**
 * @brief subtracts the Matrix<T> on the right side of the operator from the matrix on the left
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a const Matrix that represents the difference
 */
template<typename T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T> &rhs) const {
    // matrix the function is being called on
    Matrix<T> lhs = *this;
    // check dimensions and throw exception if there is a mismatch
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        throw DimensionMismatchException();
    }
    int rows = rhs.rows;
    int cols = rhs.cols;
    Matrix<T> result(rows, cols);
    // subtract each matrix elementwise
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = lhs[i][j] - rhs[i][j];
        }
    }
    return result;
}

/**
 * @brief multiplies the Matrix<T> on the right side of the operator from the matrix on the left
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a const Matrix that represents the product
 */
template<typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) const {
    // matrix the function is being called on
    Matrix<T> lhs = *this;
    // check dimensions and throw exception if there is a mismatch
    if (lhs.cols != rhs.rows) {
        throw DimensionMismatchException();
    }
    Matrix<T> result(lhs.rows, rhs.cols);
    // multiply each matrix elementwise
    for (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < rhs.cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < rhs.rows; k++) {
                result[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return result;
}

/**
 * @brief adds the Matrix<T> on the right side of the + operator to the matrix on the left
 *        then sets the matrix on the left to this new sum
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a reference to the new summed matrix
 */
template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs) {
    // call other + operator
    *this = *this + rhs;
    return *this;
}

/**
 * @brief subtracts the Matrix<T> on the right side of the operator from the matrix on the left
 *        then sets the matrix on the left to this new difference
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a reference to the new subtracted matrix
 */
template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs) {
    // call other - operator
    *this = *this - rhs;
    return *this;
}

/**
 * @brief multiplies the Matrix<T> on the right side of the operator from the matrix on the left
 *        then sets the matrix on the left to this new product
 *        is called on the Matrix on the left
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a reference to the new multiplied matrix
 */
template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &rhs) {
    // call other * operator
    *this = *this * rhs;
    return *this;
}

/**
 * @brief a reversible overload of compound assignment for scalars and matrices
 *        calls the relevant friend function overload *
 * @param scalar  a const int that will be multiplied by the matrix
 * @return a reference to the new multiplied matrix
 */
template<typename T>
Matrix<T> &Matrix<T>::operator*=(const int scalar) {
    // call friend function for *
    *this = scalar * *this;
    return *this;
}

/**
 * @brief a reversible overload of compound assignment for complex numbers and matrices
 *        calls the relevant friend function overload *
 * @param scalar  a const complex number that will be multiplied by the matrix
 * @return a reference to the new multiplied matrix
 */
template<typename T>
Matrix<T> &Matrix<T>::operator*=(const std::complex<int> scalar) {
    // call friend function for *
    *this = scalar * *this;
    return *this;
}

/**
 * @brief checks to see if both matrices are equivalent to each other
 *        that is, equal in both dimensions and values
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a boolean representing their equality
 */
template<typename T>
const bool Matrix<T>::operator==(const Matrix<T> &rhs) const {
    // matrix the function is being called on
    Matrix<T> lhs = *this;
    // dimension check first
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        return false;
    }
    int rows = rhs.rows;
    int cols = rhs.cols;
    // check every element of each array for equality
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief checks to see if both matrices are not equivalent to each other
 *        that is, inequal equal in either dimensions or values
 * @param rhs a const reference to the Matrix on the right of the operator
 * @return a boolean representing their inequality
 */
template<typename T>
const bool Matrix<T>::operator!=(const Matrix<T> &rhs) const {
    // matrix the function is being called on
    Matrix<T> lhs = *this;
    // call other equality operator, then reverse the output
    return !(lhs == rhs);
}

#endif //LECTURE9_MATRIX_HPP
