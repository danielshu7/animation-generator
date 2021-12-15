#include "Pop_Command.h"
#include "3D.h"
#include <iostream>

// constructor
Pop_Command::Pop_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Pop_Command::run() const
{
    if(validNumParam(0, 0, "POP")) {
        pop();
    }
}

// pop
void Pop_Command::pop() const
{
    if(stack[1] == nullptr) {
        // stack always has at least 1 matrix
        std::cout << "ERROR: Stack only contains one matrix - cannot pop." << std::endl;
        return;
    }

    // delete popped matrix
    delete stack[top];
    stack[top] = nullptr;

    // shift all transforms up the stack
    for(int i = top; i < 49; ++i) {
        stack[i] = stack[i + 1];
    }
    stack[49] = nullptr;
}