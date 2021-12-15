#include "Matrix_3x3.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

// default ctor initialized to 0 matrix
Matrix_3x3::Matrix_3x3() : mat{{0}}
{}

// constructor forms matrix with provided elements
Matrix_3x3::Matrix_3x3(double a1, double a2, double a3,
           double b1, double b2, double b3,
           double c1, double c2, double c3)
           : mat{{a1, a2, a3},
                 {b1, b2, b3},
                 {c1, c2, c3}}
{}

// alternate ctor takes double array
Matrix_3x3::Matrix_3x3(double entries[3][3])
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            mat[i][j] = entries[i][j];
        }
    }
}

// alternate ctor takes column vectors
Matrix_3x3::Matrix_3x3(Vector3 col1, Vector3 col2, Vector3 col3)
{
    for(int i = 0; i < 3; ++i) {
        mat[i][0] = col1[i];
    }
    for(int i = 0; i < 3; ++i) {
        mat[i][1] = col2[i];
    }
    for(int i = 0; i < 3; ++i) {
        mat[i][2] = col3[i];
    }
}

// copy ctor
Matrix_3x3::Matrix_3x3(const Matrix_3x3& src)
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            mat[i][j] = src[i][j];
        }
    }
}

// assignment operator
Matrix_3x3& Matrix_3x3::operator=(const Matrix_3x3& rhs)
{
    if (this != &rhs) {
        Matrix_3x3 tmp(rhs);
        std::swap(mat, tmp.mat);
    }
    return *this;
}


// equality operators
bool Matrix_3x3::operator==(const Matrix_3x3& rhs) const
{
    const double EPSILON = .000001;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(std::abs(mat[i][j] - rhs[i][j]) >= EPSILON) return false;
        }
    }
    return true;
}

bool Matrix_3x3::operator!=(const Matrix_3x3& rhs) const
{
    return !(*this == rhs);
}

// subscript operators
const double* Matrix_3x3::operator[](int index) const
{
    return mat[index];
}

double* Matrix_3x3::operator[](int index)
{
    return const_cast<double*>(const_cast<const Matrix_3x3&>(*this)[index]);
}

// matrix addition
Matrix_3x3 Matrix_3x3::operator+(const Matrix_3x3& rhs) const
{
    Matrix_3x3 result;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            result[i][j] = mat[i][j] + rhs[i][j];
        }
    }
    return result;
}

// matrix subtraction
Matrix_3x3 Matrix_3x3::operator-(const Matrix_3x3& rhs) const
{
    Matrix_3x3 result;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            result[i][j] = mat[i][j] - rhs[i][j];
        }
    }
    return result;
}

// scalar multiplication
Matrix_3x3 Matrix_3x3::operator*(double factor) const
{
    Matrix_3x3 result;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            result[i][j] = mat[i][j] * factor;
        }
    }
    return result;
}

// scalar multiplication for commutativity (friend)
Matrix_3x3 operator*(double factor, const Matrix_3x3& matrix)
{
    return matrix * factor;
}

// scalar division
Matrix_3x3 Matrix_3x3::operator/(double divisor) const
{
    if(divisor != 0) {
        return (*this) * (1 / divisor);
    }
    else {
        Matrix_3x3 result;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(mat[i][j] == 0) {
                    result[i][j] = std::numeric_limits<double>::quiet_NaN();
                }
                else if(mat[i][j] > 0) {
                    result[i][j] = std::numeric_limits<double>::infinity();
                }
                else {
                    result[i][j] = -std::numeric_limits<double>::infinity();
                }
            }
        }
        return result;
    }
}

// determinant
double Matrix_3x3::det() const
{
    return mat[0][0] * mat[1][1] * mat[2][2] +
           mat[0][1] * mat[1][2] * mat[2][0] +
           mat[0][2] * mat[1][0] * mat[2][1] -
           mat[2][0] * mat[1][1] * mat[0][2] -
           mat[2][1] * mat[1][2] * mat[0][0] -
           mat[2][2] * mat[1][0] * mat[0][1];
}

// inverse
Matrix_3x3 Matrix_3x3::inverse() const
{
    Matrix_3x3 adj;
    adj[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
    adj[0][1] = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2];
    adj[0][2] = mat[0][1] * mat[2][2] - mat[0][2] * mat[1][1];
    adj[1][0] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
    adj[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
    adj[1][2] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
    adj[2][0] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
    adj[2][1] = mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1];
    adj[2][2] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    return adj / det();
}

// addition + assignment
Matrix_3x3& Matrix_3x3::operator+=(const Matrix_3x3& rhs)
{
    *this = *this + rhs;
    return *this;
}

// subtraction + assignment
Matrix_3x3& Matrix_3x3::operator-=(const Matrix_3x3& rhs)
{
    *this = *this - rhs;
    return *this;
}

// scalar multiplication + assignment
Matrix_3x3& Matrix_3x3::operator*=(double factor)
{
    *this = (*this) * factor;
    return *this;
}

// scalar division + assignment
Matrix_3x3& Matrix_3x3::operator/=(double divisor)
{
    *this = (*this) / divisor;
    return *this;
}