#include "LookAt_Command.h"
#include "3D.h"

// constructor
LookAt_Command::LookAt_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void LookAt_Command::run() const
{
    if(validNumParam(9, 9, "LOOKAT")) {
        float* nParams = new float[9];
        if(paramToNum(nParams)) {
            lookAt(nParams);
        }
        delete[] nParams;
    }
}

// lookAt
void LookAt_Command::lookAt(const float nParams[9]) const
{
    gtLookAt(nParams[0], nParams[1], nParams[2], nParams[3], nParams[4],
             nParams[5], nParams[6], nParams[7], nParams[8]);
}