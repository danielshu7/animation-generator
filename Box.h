#ifndef BOX_H
#define BOX_H

#include "Object_Model.h"

/*
 * Class:       Box
 * Description: Class representing axis-aligned 3D box model
 */
class Box : public Object_Model {
public:
    // ctor initializes vertices
    Box(double lb1, double lb2, double lb3,
        double rt1, double rt2, double rt3,
        double a1, double a2, double a3,
        double r1, double r2, double r3);

    // Don't allow copy or assignment as there should never be a reason to use them
    Box(const Box&) = delete;
    const Box& operator=(const Box&) = delete;

    // destructor
    ~Box() override = default;

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
    Vector3 p0;
    Vector3 p1;
};


#endif //BOX_H
