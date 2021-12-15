#include "Camera_Command.h"
#include "Trace_Command.h"


// constructor
Camera_Command::Camera_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Camera_Command::run() const
{
    if(validNumParam(14, 14, "CAMERA")) {
        double* nParams = new double[14];
        if(paramToNum(nParams)) {
            camera(nParams);
        }
        delete[] nParams;
    }
}

// orthocamera
void Camera_Command::camera(const double nParams[14]) const
{
    Trace_Command::orthoCam = false;
    Trace_Command::cam.eyepoint = Vector3(nParams[0], nParams[1], nParams[2]);
    Trace_Command::cam.gazeDir = Vector3(nParams[3], nParams[4], nParams[5]);
    Trace_Command::cam.up = Vector3(nParams[6], nParams[7], nParams[8]);
    Trace_Command::cam.dist = nParams[9];
    Trace_Command::cam.leftx = nParams[10];
    Trace_Command::cam.lefty = nParams[11];
    Trace_Command::cam.rightx = nParams[12];
    Trace_Command::cam.righty = nParams[13];
}