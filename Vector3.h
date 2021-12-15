#ifndef VECTOR3_H
#define VECTOR3_H

/*
 * Class:       Vector3
 * Description: Structure representing a mathematical vector of 3 elements
 */
class Vector3 {
public:
    // default constructor initialized to 0 vector
    Vector3();

    // constructor forms vector with provided elements
    Vector3(double a1, double a2, double a3);

    // alternate constructor takes array
    explicit Vector3(double components[3]);

    // copy ctor
    Vector3(const Vector3& src);

    // assignment operator
    Vector3& operator=(const Vector3& rhs);

    // default dtor
    ~Vector3() noexcept = default;

    // equality operators
    bool operator==(const Vector3& rhs) const;
    bool operator!=(const Vector3& rhs) const;

    // subscript operators
    const double& operator[](int index) const;
    double& operator[](int index);

    // vector addition
    Vector3 operator+(const Vector3& vect) const;

    // vector subtraction
    Vector3 operator-(const Vector3& vect) const;

    // scalar multiplication
    Vector3 operator*(double factor) const;

    // scalar division
    Vector3 operator/(double divisor) const;

    // dot product
    double dot(const Vector3& vect) const;

    // pair-wise multiplication
    Vector3 pairMult(const Vector3& vect) const;

    // norm calculation
    double norm() const;

    // norm squared
    double normSq() const;

    // normalize: finds unit vector
    Vector3 normalize() const;

    // cross product
    Vector3 cross(const Vector3& vect) const;

    // addition + assignment
    Vector3& operator+=(const Vector3& vect);

    // subtraction + assignment
    Vector3& operator-=(const Vector3& vect);

    // scalar multiplication + assignment
    Vector3& operator*=(double factor);

    // scalar division + assignment
    Vector3& operator/=(double divisor);

private:
    // friend scalar multiplication for commutativity
    friend Vector3 operator*(double factor, const Vector3& vect);

    // x, y, z member values of vector
    double x;
    double y;
    double z;
};

// scalar multiplication for commutativity
Vector3 operator*(double factor, const Vector3& vect);


#endif //VECTOR3_H
