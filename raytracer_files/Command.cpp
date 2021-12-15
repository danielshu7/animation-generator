#include "Command.h"
#include <cerrno>
#include <cstdlib>
#include <iostream>

// constructor
Command::Command(const std::vector<char*> & params) : parameters(params)
{}

// validNumParam
bool Command::validNumParam(int min, int max, const std::string & cmd) const noexcept
{
    int numParam = parameters.size();
    if(numParam < min) {
        std::cout << "ERROR: Too few parameters for \"" << cmd << "\" (" << numParam << ")." <<
                  std::endl;
        return false;
    }
    else if(numParam> max) {
        std::cout << "ERROR: Too many parameters for \"" << cmd << "\" (" << numParam << ")." <<
                  std::endl;
        return false;
    }
    return true;
}

// paramToNum (double)
bool Command::paramToNum(double* nParams) const noexcept
{
    errno = 0;
    for(int i = 0; i < parameters.size(); ++i) {
        char* end;
        nParams[i] = std::strtod(parameters[i], &end);

        if(*end != '\0') {
            // enters when the parameter cannot be converted to a numeric value
            std::cout << "ERROR: \"" << parameters[i] << "\" is not numeric." << std::endl;
            return false;
        }
        else if(errno == ERANGE) {
            // enters when the parameter is out of range
            std::cout << "ERROR: \"" << parameters[i] << "\" is out of range." << std::endl;
            errno = 0;
            return false;
        }
    }
    return true;
}

// paramToNum (float)
bool Command::paramToNum(float* nParams) const noexcept
{
    errno = 0;
    for(int i = 0; i < parameters.size(); ++i) {
        char* end;
        nParams[i] = std::strtod(parameters[i], &end);

        if(*end != '\0') {
            // enters when the parameter cannot be converted to a numeric value
            std::cout << "ERROR: \"" << parameters[i] << "\" is not numeric." << std::endl;
            return false;
        }
        else if(errno == ERANGE) {
            // enters when the parameter is out of range
            std::cout << "ERROR: \"" << parameters[i] << "\" is out of range." << std::endl;
            errno = 0;
            return false;
        }
    }
    return true;
}