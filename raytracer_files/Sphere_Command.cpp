#include "Sphere_Command.h"
#include "Trace_Command.h"
#include "Sphere.h"

// constructor
Sphere_Command::Sphere_Command(const std::vector<char*> & params)
    : Command(params)
{}

// run
void Sphere_Command::run() const
{
    if(validNumParam(10, 13, "SPHERE")) {
        double* nParams = new double[parameters.size()];
        if(paramToNum(nParams)) {
            sphere(nParams);
        }
        delete[] nParams;
    }
}


// sphere
void Sphere_Command::sphere(const double* const nParams) const
{
    // create sphere
    Vector3 spec;
    for(int i = 10; i < parameters.size(); ++i) {
        spec[i - 10] = nParams[i];
    }
    Sphere* ptr = new Sphere(nParams[0],
                             nParams[1], nParams[2], nParams[3],
                             nParams[4], nParams[5], nParams[6],
                             nParams[7], nParams[8], nParams[9],
                             spec);

    // add to object list
    Trace_Command::objList.push_back(ptr);
}

