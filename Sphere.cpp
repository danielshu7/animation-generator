#include "Sphere.h"
#include "Trace_Command.h"
#include <cmath>

// ctor
Sphere::Sphere(double r,
       double c1, double c2, double c3,
       double a1, double a2, double a3,
       double r1, double r2, double r3,
       const Vector3& spec)
       : Object_Model(a1, a2, a3, r1, r2, r3)
       , radius(r)
       , center(c1, c2, c3)
{
    specularC = spec;
}

// hit
bool Sphere::hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj,
                 Vector3* uNormal) const
{
    // calculate components of quadratic formula (time variable)
    Vector3 e = ray.origin;
    Vector3 d = ray.direction;
    double A = d.dot(d);
    double B = 2 * d.dot(e - center);
    double C = (e - center).dot(e - center) - radius * radius;
    double disc = B * B - 4 * A * C;

    const double EPSILON = .000001;
    if(disc > EPSILON) {    // valid intersection found
        double sqrtd = std::sqrt(disc);
        double t = (- B - sqrtd) / (2 * A); // time of intersection
        if(t > t0 && t < *t1) {    // in range (note t1 originally infinity; afterwards take first)
            // calculate unit normal
            Vector3 point = e + t * d;
            Vector3 uNorm = (point - center) / radius;
            *curObj = this;
            *uNormal = uNorm;
            *t1 = t;    // update time of intersection
            return true;
        }  // otherwise check other intersection point
        t = (- B + sqrtd) / (2 * A);
        if(t > t0 && t < *t1) {
            // calculate unit normal
            Vector3 point = e + t * d;
            Vector3 uNorm = (point - center) / radius;
            *curObj = this;
            *uNormal = uNorm;
            *t1 = t;    // update time of intersection
            return true;
        }
    }   // if gets here, then no valid intersection
    return false;
}