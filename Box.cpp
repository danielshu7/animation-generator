#include "Box.h"
#include "Trace_Command.h"
#include <algorithm>

// ctor
Box::Box(double lb1, double lb2, double lb3,
         double rt1, double rt2, double rt3,
         double a1, double a2, double a3,
         double r1, double r2, double r3)
         : Object_Model(a1, a2, a3, r1, r2, r3)
         , p0(lb1, lb2, lb3)
         , p1(rt1, rt2, rt3)
{}

// hit
bool Box::hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj, Vector3* uNormal)
const
{
    // find time intervals in x,y,z directions
    Vector3 e = ray.origin;
    Vector3 d = ray.direction;
    double tMin[3], tMax[3];
    double tl, tu;
    for(int i = 0; i < 3; ++i) {
        double alpha = 1 / d[i];
        if((p0[i] - e[i]) * alpha < (p1[i] - e[i]) * alpha) {
            tMin[i] = (p0[i] - e[i]) * alpha;
            tMax[i] = (p1[i] - e[i]) * alpha;
        }
        else {
            tMin[i] = (p1[i] - e[i]) * alpha;
            tMax[i] = (p0[i] - e[i]) * alpha;
        }
    }

    char c1, c2;  // track which bounds
    // find largest lower bound
    if(tMin[0] > tMin[1]) {
        tl = tMin[0];
        c1 = 'x';
    }
    else {
        tl = tMin[1];
        c1 = 'y';
    }
    if(tMin[2] > tl) {
        tl = tMin[2];
        c1 = 'z';
    }

    // find smallest upper bound
    if(tMax[0] < tMax[1]) {
        tu = tMax[0];
        c2 = 'x';
    }
    else {
        tu = tMax[1];
        c2 = 'y';
    }
    if(tMax[2] < tu) {
        tu = tMax[2];
        c2 = 'z';
    }

    if(tl < tu) {  // intersection occurs
        double t = tl;
        if(t > t0 && t < *t1) {    // in range
            // calculate unit normal
            Vector3 uNorm;
            if(c1 == 'x') uNorm = Vector3(1, 0, 0);
            else if(c1 == 'y') uNorm = Vector3(0, 1, 0);
            else uNorm = Vector3(0, 0, 1);
            if(d.dot(uNorm) / d.norm() > 0) uNorm *= -1;  // invert direction if angle < 90

            *curObj = this;
            *uNormal = uNorm;
            *t1 = t;    // update time of intersection
            return true;
        }  // otherwise check other intersection point
        t = tu;
        if(t > t0 && t < *t1) {
            // calculate unit normal
            Vector3 uNorm;
            if(c2 == 'x') uNorm = Vector3(1, 0, 0);
            else if(c2 == 'y') uNorm = Vector3(0, 1, 0);
            else uNorm = Vector3(0, 0, 1);
            if(d.dot(uNorm) / d.norm() > 0) uNorm *= -1;  // invert direction if angle < 90

            *curObj = this;
            *uNormal = uNorm;
            *t1 = t;    // update time of intersection
            return true;
        }
    }
    return false;

}