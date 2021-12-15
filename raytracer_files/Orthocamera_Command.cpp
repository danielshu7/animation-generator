#include "Orthocamera_Command.h"
#include "Trace_Command.h"


// constructor
Orthocamera_Command::Orthocamera_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Orthocamera_Command::run() const
{
    if(validNumParam(0, 0, "ORTHOCAMERA")) {
        orthocamera();
    }
}

// orthocamera
void Orthocamera_Command::orthocamera() const
{
    Trace_Command::orthoCam = true;
}