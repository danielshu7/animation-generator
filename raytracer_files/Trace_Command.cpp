#include "Trace_Command.h"
#include "limits"
#include "Object_Model.h"
#include "Ilight_Command.h"
#include "Dispatcher.h"
#include "TiffWrite_Command.h"
#include "Screen_Command.h"
#include <iostream>
#include <algorithm>

// constructor
Trace_Command::Trace_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Trace_Command::run() const
{
    if(validNumParam(0, 0, "TRACE")) {
        trace();
    }
}

// trace
void Trace_Command::trace() const
{
    // iterate through all pixels and calculate color
    for(int i = 0; i < checkImageWidth; ++i) {
        for(int j = 0; j < checkImageHeight; ++j) {
            Vector3 pixelColor;
            if(orthoCam) {  // orthocamera view
                Ray3 ray{Vector3(i, j, 0), Vector3(0, 0, -1)};
                pixelColor = rayTrace(ray);
            }
            else { // pinhole camera view
                Vector3 w = (-1) * cam.gazeDir.normalize();
                Vector3 u = (cam.up).cross(w).normalize();
                Vector3 v = w.cross(u);
                double uMag = cam.leftx + (cam.rightx - cam.leftx) * i /
                        (Screen_Command::screenWidth - 1);
                double vMag = cam.lefty + (cam.righty - cam.lefty) * j /
                        (Screen_Command::screenHeight - 1);
                Ray3 ray{cam.eyepoint, uMag * u + vMag * v - cam.dist * w};
                pixelColor = rayTrace(ray);
            }

            // clamp to [0, 1]
            for(int k = 0; k < 3; ++k) {
                if(pixelColor[k] < 0) pixelColor[k] = 0;
                else if(pixelColor[k] > 1) pixelColor[k] = 1;
            }

            // update image array
            checkImage[j][i][0] = (GLubyte) (pixelColor[0] * 255);
            checkImage[j][i][1] = (GLubyte) (pixelColor[1] * 255);
            checkImage[j][i][2] = (GLubyte) (pixelColor[2] * 255);
        }
    }
    display();
    if(Dispatcher::depth == 1) {
        // prepWrite only if depth is 1 (i.e. not in a nested read file)
        TiffWrite_Command::prepWrite();
    }
}

// rayTrace
Vector3 Trace_Command::rayTrace(const Ray3& ray) const
{
    // loop through all objects and find closest intersection
    double bound = std::numeric_limits<double>::infinity(); // initialize to infinity
    double* t1 = &bound;
    const Object_Model** curObj = new const Object_Model*;
    Vector3* uNormal = new Vector3;

    if(hit(ray, EPSILON, t1, curObj, uNormal)) { // nearest intersection found
        // calculate the point and color at that point
        Vector3 point = ray.origin + (*t1) * ray.direction;
        return shade(point, ray.direction, curObj, uNormal);
    }   // otherwise no intersection

    // clean up pointers
    delete uNormal;
    delete curObj;
    return bg;
}

// hit
bool Trace_Command::hit(const Ray3& ray, double t0, double* t1,
                        const Object_Model** curObj, Vector3* uNormal) const
{
    bool hitOne = false;

    // iterate through all objects to find nearest intersection
    for(auto obj : objList) {
        if(obj->hit(ray, t0, t1, curObj, uNormal)) {
            hitOne = true;
        }
    }
    return hitOne;
}

// hit1
bool Trace_Command::hit1(const Ray3& ray, double t0, double t1) const
{
    // iterate through all objects to find nearest intersection
    for(auto obj : objList) {
        const Object_Model* placeH = nullptr;
        Vector3 placeH2;
        if(obj->hit(ray, t0, &t1, &placeH, &placeH2)) {
            return true;
        }
    }
    return false;
}

// shade
Vector3 Trace_Command::shade(const Vector3& point, const Vector3& d, const Object_Model** curObj,
                             Vector3* uNormal) const
{
    // ambient color
    Vector3 color = (*curObj)->getAmbientC();

    // diffuse calculation
    for(auto light : lightList) {
        // check if in shadow
        Ray3 lightRay{point,(-1) * (light->direction)};
        double bound = std::numeric_limits<double>::infinity(); // initialize to infinity
        if(!hit1(lightRay,EPSILON, bound)) {  // not in shadow
            color += (light->color).pairMult((*curObj)->getReflectedC())
                     * std::max(0., -uNormal->dot((light->direction).normalize()));
        }
    }

    if((*curObj)->getSpecularC() != Vector3() && reflectDepth < 5) {  // has specular property
        Vector3 r = d - 2 * d.dot(*uNormal) * (*uNormal); // reflected ray
        ++reflectDepth;
        color += ((*curObj)->getSpecularC()).pairMult(rayTrace(Ray3{point, r}));
        --reflectDepth;
    }



    // clean up pointers
    delete uNormal;
    delete curObj;
    return color;
}