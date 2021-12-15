#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object_Model.h"

/*
 * Class:       Triangle
 * Description: Class representing triangle model in 3D
 */
class Triangle : public Object_Model {
public:
    // ctor initializes vertex vectors
    Triangle(double v11, double v12, double v13,
             double v21, double v22, double v23,
             double v31, double v32, double v33,
             double a1, double a2, double a3,
             double r1, double r2, double r3);

    // Don't allow copy or assignment as there should never be a reason to use them
    Triangle(const Triangle&) = delete;
    const Triangle& operator=(const Triangle&) = delete;

    // destructor
    ~Triangle() override = default;

    /*
     * Function:    hit
     * Description: Checks if the ray intersects the object
     * Arguments:   ray  - ray to intersect with
     *              t0   - earliest time of interest
     *              t1   - pointer to latest time of interest
     *              curObj - holds object (or none)
     *              uNormal - holds normal vector of intersection (or none)
     * Returns:     bool - true if intersection found; false otherwise
     * Post:        t1 holds time of intersection
     */
    bool hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj, Vector3* uNormal)
    const override;

private:
    // members
    Vector3 a;
    Vector3 b;
    Vector3 c;
};


#endif //TRIANGLE_H
