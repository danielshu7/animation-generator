#include "Rotate_Command.h"
#include "3D.h"
#include <cmath>

// constructor
Rotate_Command::Rotate_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Rotate_Command::run() const
{
    if(validNumParam(4, 4, "ROTATE")) {
        float* nParams = new float[4];
        if(paramToNum(nParams)) {
            rotate(nParams);
        }
        delete[] nParams;
    }
}

// rotate
void Rotate_Command::rotate(const float nParams[4]) const
{
    if(nParams[0] == 0) return; // nothing to do

    float magnitude = std::sqrt(std::pow(nParams[1], 2) + std::pow(nParams[2], 2)
            + std::pow(nParams[3], 2));
    float cx = nParams[1] / magnitude;
    float cy = nParams[2] / magnitude;
    float cz = nParams[3] / magnitude;
    float d = std::sqrt(std::pow(cy, 2) + std::pow(cz, 2));

    float cos = std::cos(nParams[0] * M_PI / 180);
    float sin = std::sin(nParams[0] * M_PI / 180);

    // rotation about x-axis
    matrix_unit Rx = {
            { {1., 0.    , 0.    , 0.},
              {0., cz / d,-cy / d, 0.},
              {0., cy / d, cz / d, 0.},
              {0., 0.    , 0.    , 1.}  },
    };

    // rotation about y-axis
    matrix_unit Ry = {
            { {d , 0.,-cx, 0.},
              {0., 1., 0., 0.},
              {cx, 0., d , 0.},
              {0., 0., 0., 1.}  },
    };

    // rotation about z-axis
    matrix_unit Rz = {
            { {cos,-sin, 0., 0.},
              {sin, cos, 0., 0.},
              {0. , 0. , 1., 0.},
              {0. , 0. , 0., 1.}  },
    };

    // inverse rotation about y-axis
    matrix_unit RyInv = {
            { { d , 0., cx, 0.},
              { 0., 1., 0., 0.},
              {-cx, 0., d , 0.},
              { 0., 0., 0., 1.}  },
    };

    // inverse rotation about x-axis
    matrix_unit RxInv = {
            { {1., 0.    , 0.    , 0.},
              {0., cz / d, cy / d, 0.},
              {0.,-cy / d, cz / d, 0.},
              {0., 0.    , 0.    , 1.}  },
    };

    // multiply all transforms: C <- C * RxInv * RyInv * Rz * Ry * Rx
    matrix_unit res, res1;
    Mult_mat(stack[top], &RxInv, &res);
    Mult_mat(&res, &RyInv, &res1);
    Mult_mat(&res1, &Rz, &res);
    Mult_mat(&res, &Ry, &res1);
    Mult_mat(&res1, &Rx, &res);
    Copy_mat(&res, stack[top]);
}