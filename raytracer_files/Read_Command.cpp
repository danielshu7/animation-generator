#include "Read_Command.h"
#include "Dispatcher.h"
#include "TiffWrite_Command.h"
#include <iostream>
#include <fstream>
#include <cstring>

// constructor
Read_Command::Read_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Read_Command::run() const
{
    if(validNumParam(1,1, "READ")) {
        read();
    }
}

// read
void Read_Command::read() const
{
    std::string filename = parameters[0];
    std::string filename1, filename2;
    filename1 = "scripts/" + filename;
    filename2 = "scripts/project4/" + filename;

    // open the file
    std::ifstream file1(filename1.c_str());
    std::ifstream file2(filename2.c_str());
    if (file1 && file2) {
        // enters if an error occurred while opening the file
        std::cout << "ERROR: The file \"" << filename << "\" was found in scripts and "
                                                         "scripts/project4" << std::endl;
        return;
    }
    else {
        // pointer to whichever file was opened
        std::ifstream* fileOpened;
        if(file1) {
            fileOpened = &file1;
        }
        else if(file2) {
            fileOpened = &file2;
        }
        else {
            // enters if an error occurred while opening the file
            std::cout << "ERROR: The file \"" << filename << "\" could not be opened." << std::endl;
            return;
        }

        // increment depth each time we process a new file
        ++Dispatcher::depth;

        // process the file line by line
        std::string line;
        while(std::getline(*fileOpened, line)) {
            // ignore comments
            line = line.substr(0, line.find('#'));

            // ignore empty lines
            if (line.length() == 0) {
                continue;
            }

            // initialize a new Dispatcher with the line of input as a c string
            char* ln = (char*) malloc(line.length() + 1);
            strcpy(ln, line.c_str());
            Dispatcher dispatcher(ln);
            dispatcher.dispatch();
            free(ln);
        }

        // close the appropriate file
        fileOpened->close();

        // decrement depth each time we finish processing a new file
        --Dispatcher::depth;

        // prepWrite
        TiffWrite_Command::prepWrite();
    }
}
