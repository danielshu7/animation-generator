#ifndef MATRIX_3X3_H
#define MATRIX_3X3_H

#include "Vector3.h"

/*
 * Class:       Matrix_3x3
 * Description: Structure representing a mathematical 3x3 matrix
 */
class Matrix_3x3 {
public:
    // default ctor initialized to 0 matrix
    Matrix_3x3();

    // constructor forms matrix with provided elements
    Matrix_3x3(double a1, double a2, double a3,
               double b1, double b2, double b3,
               double c1, double c2, double c3);

    // alternate ctor takes double array
    Matrix_3x3(double entries[3][3]);

    // alternate ctor takes column vectors
    Matrix_3x3(Vector3 col1, Vector3 col2, Vector3 col3);

    // copy ctor
    Matrix_3x3(const Matrix_3x3& src);

    // assignment operator
    Matrix_3x3& operator=(const Matrix_3x3& rhs);

    // default dtor
    ~Matrix_3x3() noexcept = default;

    // equality operators
    bool operator==(const Matrix_3x3& rhs) const;
    bool operator!=(const Matrix_3x3& rhs) const;

    // subscript operators
    const double* operator[](int index) const;
    double* operator[](int index);

    // matrix addition
    Matrix_3x3 operator+(const Matrix_3x3& rhs) const;

    // matrix subtraction
    Matrix_3x3 operator-(const Matrix_3x3& rhs) const;

    // scalar multiplication
    Matrix_3x3 operator*(double factor) const;

    // scalar division
    Matrix_3x3 operator/(double divisor) const;

    // determinant
    double det() const;

    // inverse
    Matrix_3x3 inverse() const;

    // addition + assignment
    Matrix_3x3& operator+=(const Matrix_3x3& rhs);

    // subtraction + assignment
    Matrix_3x3& operator-=(const Matrix_3x3& rhs);

    // scalar multiplication + assignment
    Matrix_3x3& operator*=(double factor);

    // scalar division + assignment
    Matrix_3x3& operator/=(double divisor);

private:
    // friend scalar multiplication for commutativity
    friend Matrix_3x3 operator*(double factor, const Matrix_3x3& matrix);

    // double array member representation of matrix
    double mat[3][3];
};

// friend scalar multiplication for commutativity
Matrix_3x3 operator*(double factor, const Matrix_3x3& matrix);


#endif //README_MD_MATRIX_3X3_H
