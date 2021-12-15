#include "Screen_Command.h"
#include "TiffWrite_Command.h"
#include <GL/glut.h>

// constructor
Screen_Command::Screen_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Screen_Command::run() const
{
    if(validNumParam(2, 2, "SCREEN")) {
        double* nParams = new double[2];
        if(paramToNum(nParams)) {
            screen(nParams);
        }
        delete[] nParams;
    }
}

// screen
void Screen_Command::screen(const double nParams[2]) const
{
    //reshape window
//    glutReshapeWindow(nParams[0], nParams[1]);
    screenWidth = nParams[0];
    screenHeight = nParams[1];
    TiffWrite_Command::prepWrite();
}
