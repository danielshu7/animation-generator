#include "Translate_Command.h"
#include "3D.h"

// constructor
Translate_Command::Translate_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Translate_Command::run() const
{
    if(validNumParam(3, 3, "TRANSLATE")) {
        float* nParams = new float[3];
        if(paramToNum(nParams)) {
            translate(nParams);
        }
        delete[] nParams;
    }
}

// translate
void Translate_Command::translate(const float nParams[3]) const
{
    if(nParams[0] == 0 && nParams[1] == 0 && nParams[2] == 0) return; // nothing to do

    matrix_unit trans = {
            { {1., 0., 0., nParams[0]},
              {0., 1., 0., nParams[1]},
              {0., 0., 1., nParams[2]},
              {0., 0., 0., 1.        }  },
    };
    matrix_unit res;
    Mult_mat(stack[top], &trans, &res);
    Copy_mat(&res, stack[top]);
}