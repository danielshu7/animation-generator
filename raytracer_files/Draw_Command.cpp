#include "Draw_Command.h"
#include <iostream>

// constructor
Draw_Command::Draw_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Draw_Command::run() const
{
    if(validNumParam(0, 3, "DRAW")) {
        double* nParams = new double[parameters.size()];
        if(paramToNum(nParams)) {
            draw(nParams);
        }
        delete[] nParams;
    }
}

// draw
void Draw_Command::draw(const double* const nParams) const noexcept
{
    std::cout << "DRAW: ";
    for(int i = 0; i < parameters.size(); ++i) {
        std::cout << nParams[i] << " ";
    }
    for(int i = parameters.size(); i < 3; ++i) {
        std::cout << 0 << " ";
    }
    std::cout << std::endl;
}