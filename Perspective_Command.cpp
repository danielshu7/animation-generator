#include "Perspective_Command.h"
#include "3D.h"
#include <cmath>
#include <GL/glut.h>

// constructor
Perspective_Command::Perspective_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Perspective_Command::run() const
{
    if(validNumParam(4, 4, "PERSPECTIVE")) {
        float* nParams = new float[4];
        if(paramToNum(nParams)) {
            perspective(nParams);
        }
        delete[] nParams;
    }
}

// ortho
void Perspective_Command::perspective(const float nParams[4]) const
{
    perspflag = 1; // set the perspective flag

    float angle = nParams[0];
    float a = nParams[1];
    float n = -nParams[2];
    float f = -nParams[3];

    // set Near and Far
    Near = n;
    Far = f;

    // get window size
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    width = abs(viewport[2]-viewport[0]);
    height = abs(viewport[3]-viewport[1]);

    // calculate matrix entries
    float x = std::tan(angle / 2 * M_PI / 180);
    float delta = (height - 1) / 2;
    float gamma = delta / x;
    float alpha = a * gamma;
    float beta = a * delta;

  /*  perspect = {
            { {alpha, 0.   , 0.     , beta },
              {0.   , gamma, 0.     , delta},
              {0.   , 0.   , 0.     , 0.   },
              {0.   , 0.   , 0.     , 1.   }  },
    };*/

    perspect = {
            { {alpha, 0.   , beta , beta },
              {0.   , gamma, delta, delta},
              {0.   , 0.   , 0.   , 0.},
              {0.   , 0.   , 0.   , 1.}  },
    };
}