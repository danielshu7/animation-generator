#include "Triangle_Command.h"
#include "Trace_Command.h"
#include "Triangle.h"

// constructor
Triangle_Command::Triangle_Command(const std::vector<char*> & params)
        : Command(params)
{}

// run
void Triangle_Command::run() const
{
    if(validNumParam(15, 15, "TRIANGLE")) {
        double* nParams = new double[15];
        if(paramToNum(nParams)) {
            triangle(nParams);
        }
        delete[] nParams;
    }
}


// triangle
void Triangle_Command::triangle(const double nParams[15]) const
{
    // create triangle
    Triangle* ptr = new Triangle(nParams[0], nParams[1], nParams[2],
                                 nParams[3], nParams[4], nParams[5],
                                 nParams[6], nParams[7], nParams[8],
                                 nParams[9], nParams[10], nParams[11],
                                 nParams[12], nParams[13], nParams[14]);

    // add to object list
    Trace_Command::objList.push_back(ptr);
}