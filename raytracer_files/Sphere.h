#ifndef SPHERE_H
#define SPHERE_H

#include "Object_Model.h"

/*
 * Class:       Sphere
 * Description: Class representing 3D sphere model
 */
class Sphere : public Object_Model {
public:
    // ctor initializes radius, center, ambientC, reflectedC, specularC
    Sphere(double r,
           double c1, double c2, double c3,
           double a1, double a2, double a3,
           double r1, double r2, double r3,
           const Vector3& spec);

    // Don't allow copy or assignment as there should never be a reason to use them
    Sphere(const Sphere&) = delete;
    const Sphere& operator=(const Sphere&) = delete;

    // destructor
    ~Sphere() override = default;

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
    double radius;
    Vector3 center;
};


#endif //README_MD_SPHERE_H
