#include "Vector3.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

// default constructor initialized to 0 vector
Vector3::Vector3() : x(0), y(0), z(0)
{}

// constructor forms vector with provided elements
Vector3::Vector3(double a1, double a2, double a3) : x(a1), y(a2), z(a3)
{}

// alternate constructor takes array
Vector3::Vector3(double components[3]) : x(components[0]), y(components[1]), z(components[2])
{}

// copy ctor
Vector3::Vector3(const Vector3& src) : x(src[0]), y(src[1]), z(src[2])
{}

// assignment operator
Vector3& Vector3::operator=(const Vector3& rhs)
{
    if (this != &rhs) {
        Vector3 tmp(rhs);
        std::swap(x, tmp.x);
        std::swap(y, tmp.y);
        std::swap(z, tmp.z);
    }
    return *this;
}

// equality operators
bool Vector3::operator==(const Vector3& rhs) const
{
    const double EPSILON = .000001;
    return std::abs(x - rhs.x) < EPSILON &&
           std::abs(y - rhs.y) < EPSILON &&
           std::abs(z - rhs.z) < EPSILON;
}

bool Vector3::operator!=(const Vector3& rhs) const
{
    return !(*this == rhs);
}

// subscript operators
const double& Vector3::operator[](int index) const
{
    if(index == 0) return x;
    else if(index == 1) return y;
    else return z;
}

double& Vector3::operator[](int index)
{
    return const_cast<double&>(const_cast<const Vector3&>(*this)[index]);
}

// vector addition
Vector3 Vector3::operator+(const Vector3& vect) const
{
    Vector3 result;
    result[0] = x + vect[0];
    result[1] = y + vect[1];
    result[2] = z + vect[2];
    return result;
}

// vector subtraction
Vector3 Vector3::operator-(const Vector3& vect) const
{
    Vector3 result;
    result[0] = x - vect[0];
    result[1] = y - vect[1];
    result[2] = z - vect[2];
    return result;
}

// scalar multiplication
Vector3 Vector3::operator*(double factor) const
{
    Vector3 result;
    result[0] = x * factor;
    result[1] = y * factor;
    result[2] = z * factor;
    return result;
}

// scalar multiplication for commutativity (friend)
Vector3 operator*(double factor, const Vector3& vect)
{
    return vect * factor;
}

// scalar division
Vector3 Vector3::operator/(double divisor) const
{
    if(divisor != 0) {
        return (*this) * (1 / divisor);
    }
    else {
        Vector3 result;
        for(int i = 0; i < 3; ++i) {
            if((*this)[i] == 0) {
                result[i] = std::numeric_limits<double>::quiet_NaN();
            }
            else if((*this)[i] > 0) {
                result[i] = std::numeric_limits<double>::infinity();
            }
            else {
                result[i] = -std::numeric_limits<double>::infinity();
            }
        }
        return result;
    }
}

// dot product
double Vector3::dot(const Vector3& vect) const
{
    return x * vect[0] + y * vect[1] + z * vect[2];
}

// pair-wise multiplication
Vector3 Vector3::pairMult(const Vector3& vect) const
{
    Vector3 result;
    result[0] = x * vect[0];
    result[1] = y * vect[1];
    result[2] = z * vect[2];
    return result;
}

// norm calculation
double Vector3::norm() const
{
    return std::sqrt(normSq());
}

// norm squared
double Vector3::normSq() const
{
    return dot(*this);
}

// normalize: finds unit vector
Vector3 Vector3::normalize() const
{
    double n = norm();
    if (n == 0) {
        std::cout << "ERROR: Cannot normalize zero vector" << std::endl;
        return (*this);
    }
    return (*this) / n;
}

// cross product
Vector3 Vector3::cross(const Vector3& vect) const
{
    Vector3 result;
    result[0] = (*this)[1] * vect[2] - (*this)[2] * vect[1];
    result[1] = (*this)[2] * vect[0] - (*this)[0] * vect[2];
    result[2] = (*this)[0] * vect[1] - (*this)[1] * vect[0];

    return result;
}

// addition + assignment
Vector3& Vector3::operator+=(const Vector3& vect)
{
    *this = *this + vect;
    return *this;
}

// subtraction + assignment
Vector3& Vector3::operator-=(const Vector3& vect)
{
    *this = *this - vect;
    return *this;
}

// scalar multiplication + assignment
Vector3& Vector3::operator*=(double factor)
{
    *this = (*this) * factor;
    return *this;
}

// scalar division + assignment
Vector3& Vector3::operator/=(double divisor)
{
    *this = (*this) / divisor;
    return *this;
}