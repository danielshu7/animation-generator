#include "Move_Command.h"
#include <iostream>

// constructor
Move_Command::Move_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Move_Command::run() const
{
    if(validNumParam(0, 3, "MOVE")) {
        double* nParams = new double[parameters.size()];
        if(paramToNum(nParams)) {
            move(nParams);
        }
        delete[] nParams;
    }
}

// move
void Move_Command::move(const double* const nParams) const noexcept
{
    std::cout << "MOVE: ";
    for(int i = 0; i < parameters.size(); ++i) {
        std::cout << nParams[i] << " ";
    }
    for(int i = parameters.size(); i < 3; ++i) {
        std::cout << 0 << " ";
    }
    std::cout << std::endl;
}