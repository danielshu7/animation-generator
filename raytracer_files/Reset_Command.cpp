#include "Reset_Command.h"
#include "3D.h"
#include "Pop_Command.h"
#include "TiffWrite_Command.h"
#include <GL/glut.h>

// constructor
Reset_Command::Reset_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Reset_Command::run() const
{
    if(validNumParam(0, 0, "RESET")) {
        reset();
    }
}

// reset
void Reset_Command::reset() const
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glFlush();

    // clear stack
    Pop_Command pCmd(parameters);
    while(stack[top + 1] != nullptr) {
        pCmd.run();
    }

    Copy_mat(const_cast<matrix_unit*>(&I), stack[top]);

    // resets what TiffWrite will write too (black screen)
    TiffWrite_Command::prepWrite();
}