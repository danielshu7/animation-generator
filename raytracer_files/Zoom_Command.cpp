#include "Zoom_Command.h"
#include "Resize_Command.h"


// constructor
Zoom_Command::Zoom_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Zoom_Command::run() const
{
    if(validNumParam(1, 1, "ZOOM")) {
        // duplicate parameter
        std::vector<char*> newParams;
        newParams.push_back(parameters[0]);
        newParams.push_back(parameters[0]);

        Resize_Command rsCmd(newParams);
        rsCmd.run();
    }
}