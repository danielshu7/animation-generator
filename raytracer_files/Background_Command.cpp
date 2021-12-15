#include "Background_Command.h"
#include "Trace_Command.h"
#include <iostream>

// constructor
Background_Command::Background_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Background_Command::run() const
{
    if(validNumParam(3, 3, "BACKGROUND")) {
        double* nParams = new double[3];
        if(paramToNum(nParams)) {
            // clamp rgb values to [0, 1]
            if(nParams[0] < 0) nParams[0] = 0;
            else if(nParams[0] > 1) nParams[0] = 1;

            if(nParams[1] < 0) nParams[1] = 0;
            else if(nParams[1] > 1) nParams[1] = 1;

            if(nParams[2] < 0) nParams[2] = 0;
            else if(nParams[2] > 1) nParams[2] = 1;

            background(nParams);
        }
        delete[] nParams;
    }
}

// background
void Background_Command::background(const double nParams[3]) const
{
    for (int i = 0; i < checkImageHeight; i++) {
        for (int j = 0; j < checkImageWidth; j++) {
            checkImage[i][j][0] = (GLubyte) (nParams[0] * 255);
            checkImage[i][j][1] = (GLubyte) (nParams[1] * 255);
            checkImage[i][j][2] = (GLubyte) (nParams[2] * 255);
        }
    }
    display();

    // set background rgb vector in Trace_Command
    Trace_Command::bg = Vector3(nParams[0], nParams[1], nParams[2]);
}