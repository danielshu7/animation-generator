#include "Color_Command.h"
#include <iostream>

// constructor
Color_Command::Color_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Color_Command::run() const
{
    if(validNumParam(3, 3, "COLOR")) {
        double* nParams = new double[parameters.size()];
        if(paramToNum(nParams)) {
            color(nParams);
        }
        delete[] nParams;
    }
}

// color
void Color_Command::color(const double nParams[3]) const noexcept
{
    std::cout << "COLOR: " << nParams[0] << ", " << nParams[1] << ", " << nParams[2] << std::endl;
}