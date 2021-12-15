#include "Push_Command.h"
#include "3D.h"
#include <iostream>

// constructor
Push_Command::Push_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Push_Command::run() const
{
    if(validNumParam(0, 0, "PUSH")) {
        push();
    }
}

// push
void Push_Command::push() const
{
    if(stack[49] != nullptr) {
        // stack max capacity is 50
        std::cout << "ERROR: Stack is full - cannot push onto it." << std::endl;
        return;
    }

    // shift all transforms down the stack
    for(int i = 48; i >= top; --i) {
        stack[i + 1] = stack[i];
    }

    // duplicate former top
    matrix_unit* tmp = new matrix_unit;
    Copy_mat(stack[top], tmp);
    stack[top] = tmp;
}