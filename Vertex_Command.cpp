#include "Vertex_Command.h"
#include "3D.h"
#include "TiffWrite_Command.h"
#include "Dispatcher.h"

// constructor
Vertex_Command::Vertex_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Vertex_Command::run() const
{
    if(validNumParam(3, 3, "VERTEX")) {
        float* nParams = new float[3];
        if(paramToNum(nParams)) {
            vertex(nParams);
        }
        delete[] nParams;
    }
}

// vertex
void Vertex_Command::vertex(const float nParams[3]) const
{
    gtVertex3f(nParams[0], nParams[1], nParams[2]);

    if(Dispatcher::depth == 1) {
        // prepWrite only if depth is 1 (i.e. not in a nested read file)
        TiffWrite_Command::prepWrite();
    }
}