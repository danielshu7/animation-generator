#include "Ilight_Command.h"
#include "Trace_Command.h"

// constructor
Ilight_Command::Ilight_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Ilight_Command::run() const
{
    if(validNumParam(6, 6, "ILIGHT")) {
        double* nParams = new double[6];
        if(paramToNum(nParams)) {
            ilight(nParams);
        }
        delete[] nParams;
    }
}


// ilight
void Ilight_Command::ilight(const double nParams[6]) const {
    // create ilight
    Ilight* ptr = new Ilight{Vector3(nParams[0], nParams[1], nParams[2]),
                             Vector3(nParams[3], nParams[4], nParams[5])};

    // add to ilight list
    Trace_Command::lightList.push_back(ptr);
}