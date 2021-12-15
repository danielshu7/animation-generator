#include "Ortho_Command.h"
#include "3D.h"
#include <GL/glut.h>

// constructor
Ortho_Command::Ortho_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Ortho_Command::run() const
{
    if(validNumParam(6, 6, "ORTHO")) {
        float* nParams = new float[6];
        if(paramToNum(nParams)) {
            ortho(nParams);
        }
        delete[] nParams;
    }
}

// ortho
void Ortho_Command::ortho(const float nParams[6]) const
{
    perspflag = 0; // set the perspective flag

    float l = nParams[0];
    float r = nParams[1];
    float b = nParams[2];
    float t = nParams[3];
    float n = -nParams[4];
    float f = -nParams[5];

    // set Near and Far
    Near = n;
    Far = f;

    // get window size
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    width = abs(viewport[2]-viewport[0]);
    height = abs(viewport[3]-viewport[1]);

    // calculate matrix entries
    float alpha = (width - 1) / (r - l);
    float beta = - alpha * l;
    float gamma = (height - 1) / (t - b);
    float delta = - gamma * b;
    float epsilon = 1 / (f - n);
    float zeta = - epsilon * n;

    orth = {
            { {alpha, 0.   , 0.     , beta },
              {0.   , gamma, 0.     , delta},
              {0.   , 0.   , epsilon, zeta },
              {0.   , 0.   , 0.     , 1.   }  },
    };
}