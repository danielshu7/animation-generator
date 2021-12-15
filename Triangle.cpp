#include "Triangle.h"
#include "Trace_Command.h"
#include "Matrix_3x3.h"

//ctor
Triangle::Triangle(double v11, double v12, double v13,
                   double v21, double v22, double v23,
                   double v31, double v32, double v33,
                   double a1, double a2, double a3,
                   double r1, double r2, double r3)
                   : Object_Model(a1, a2, a3, r1, r2, r3)
                   , a(v11, v12, v13)
                   , b(v21, v22, v23)
                   , c(v31, v32, v33)
{}

// hit
bool Triangle::hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj,
                   Vector3* uNormal) const
{
    // compute barycentric coordinates & check bounds
    Vector3 e = ray.origin;
    Vector3 d = ray.direction;
    Matrix_3x3 A(a - b, a - c, d);
    Matrix_3x3 betaMat(a - e, a - c, d);
    double beta = betaMat.det() / A.det();
    if(beta < 0 || beta > 1) return false;

    Matrix_3x3 gammaMat(a - b, a - e, d);
    double gamma = gammaMat.det() / A.det();
    if(gamma < 0 || (beta + gamma >= 1)) return false;

    Matrix_3x3 tMat(a - b, a - c, a - e);
    double t = tMat.det() / A.det();
    if(t > t0 && t < *t1) { // in range
        // calculate unit normal
        Vector3 uNorm = (c - a).cross(b - a).normalize();
        if(d.dot(uNorm) / d.norm() > 0) uNorm *= -1;  // invert direction if angle < 90
        *curObj = this;
        *uNormal = uNorm;
        *t1 = t;    // update time of intersection
        return true;
    }
    return false;
}