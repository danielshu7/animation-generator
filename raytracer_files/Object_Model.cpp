#include "Object_Model.h"

// ctor initializes ambientC, reflectedC
Object_Model::Object_Model(double a1, double a2, double a3, double r1, double r2, double r3)
        : ambientC(a1, a2, a3)
        , reflectedC(r1, r2, r3)
        , specularC()
{}

// getAmbientC
const Vector3& Object_Model::getAmbientC() const
{
    return ambientC;
}

// getReflectedC
const Vector3& Object_Model::getReflectedC() const
{
    return reflectedC;
}

// getSpecularC
const Vector3& Object_Model::getSpecularC() const
{
    return specularC;
}