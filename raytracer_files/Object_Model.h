#ifndef OBJECT_MODEL_H
#define OBJECT_MODEL_H

#include "Vector3.h"

// forward declaration
struct Ray3;

/*
 * Class:       Object_Model
 * Description: Abstract class interface describing a model of a 3D object
 */
class Object_Model {
public:
    // ctor initializes ambientC, reflectedC
    Object_Model(double a1, double a2, double a3, double r1, double r2, double r3);

    // default dtor
    virtual ~Object_Model() = default;

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
    virtual bool hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj,
                     Vector3* uNormal) const = 0;

    // accessor methods
    const Vector3& getAmbientC() const;
    const Vector3& getReflectedC() const;
    const Vector3& getSpecularC() const;

protected:
    // member rgb color values in [0, 1] range, initially 0
    Vector3 ambientC;
    Vector3 reflectedC;
    Vector3 specularC;  // default 0
};


#endif //OBJECT_MODEL_H
