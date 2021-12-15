#include "Box_Command.h"
#include "Trace_Command.h"
#include "Box.h"

// constructor
Box_Command::Box_Command(const std::vector<char*> & params)
        : Command(params)
{}

// run
void Box_Command::run() const
{
    if(validNumParam(12, 12, "BOX")) {
        double* nParams = new double[12];
        if(paramToNum(nParams)) {
            box(nParams);
        }
        delete[] nParams;
    }
}


// box
void Box_Command::box(const double nParams[12]) const {
    // create triangle
    Box *ptr = new Box(nParams[0], nParams[1], nParams[2],
                       nParams[3], nParams[4], nParams[5],
                       nParams[6], nParams[7], nParams[8],
                       nParams[9], nParams[10], nParams[11]);

    // add to object list
    Trace_Command::objList.push_back(ptr);
}