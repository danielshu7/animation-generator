#include "Clear_Command.h"
#include "Trace_Command.h"
#include "TiffWrite_Command.h"
#include <GL/glut.h>


// constructor
Clear_Command::Clear_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Clear_Command::run() const
{
    if(validNumParam(0, 0, "CLEAR")) {
        clear();
    }
}

// clear
void Clear_Command::clear() const
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glFlush();
    Trace_Command::bg = Vector3(0, 0, 0); // reset background to black

    // clear object list
    for(auto ptr : Trace_Command::objList) {
        delete ptr;
        ptr = nullptr;
    }
    Trace_Command::objList.clear();

    // clear light list
    for(auto ptr : Trace_Command::lightList) {
        delete ptr;
        ptr = nullptr;
    }
    Trace_Command::lightList.clear();

    // resets what TiffWrite will write too (black screen)
    TiffWrite_Command::prepWrite();
}