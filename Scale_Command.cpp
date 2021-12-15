#include "Scale_Command.h"
#include "3D.h"

// constructor
Scale_Command::Scale_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Scale_Command::run() const
{
    if(validNumParam(3, 3, "SCALE")) {
        float* nParams = new float[3];
        if(paramToNum(nParams)) {
            scale(nParams);
        }
        delete[] nParams;
    }
}

// scale
void Scale_Command::scale(const float nParams[3]) const
{
    matrix_unit scaleM = {
            { {nParams[0], 0.        , 0.        , 0.},
              {0.        , nParams[1], 0.        , 0.},
              {0.        , 0.        , nParams[2], 0.},
              {0.        , 0.        , 0.        , 1.}  },
    };
    matrix_unit res;
    Mult_mat(stack[top], &scaleM, &res);
    Copy_mat(&res, stack[top]);
}