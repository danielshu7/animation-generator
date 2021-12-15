#include "Tiff_Input_Command.h"
#include <iostream>
#include <cstring>


// constructor
Tiff_Input_Command::Tiff_Input_Command(const std::vector<char*> & params) : Command(params)
{
}

// tiffParse
std::vector<TiffField> Tiff_Input_Command::tiffParse() const
{
    char endian[3];
    short magicNum; // 2 byte quantity
    unsigned long ifdAddress; // 4 byte quantity
    unsigned short ifdCount; // 2 byte quantity

    std::vector<TiffField> fields; // vector of tiff fields to return

    std::string filename = parameters[0];
    filename = "images/" + filename;

    std::ifstream file;
    file.open (filename.c_str(), std::ios::binary );
    if(!file) {
        // enters if an error occurred while opening the file
        std::cout << "ERROR: The file \"" << filename << "\" could not be opened." << std::endl;
    }
    else {
        // read endianness and magic number
        file.seekg (0, std::ios::beg);
        file.read (endian,2);
        endian[2] = '\0';
        fileReadSwapIf(file, (char*) &magicNum, 2, endian);

        if(magicNum != 42) {
            // reaches here if file is not a tiff file; return empty fields
            std::cout << "ERROR: The file \"" << filename << "\" is not a TIFF file." << std::endl;
            return fields;
        }

        fileReadSwapIf(file, (char*) &ifdAddress, 4, endian);
        file.seekg(ifdAddress, std::ios::beg);
        fileReadSwapIf(file, (char*) &ifdCount, 2, endian);

        for(unsigned short i = 0; i < ifdCount; ++i) {
            // iterate through each field
            TiffField tf;
            fileReadSwapIf(file, (char*) &tf.tag, 2, endian);

            fileReadSwapIf(file, (char*) &tf.type, 2, endian);
            fileReadSwapIf(file, (char*) &tf.count, 4, endian);

            unsigned long val = 0, address = 0;
            if(tf.type == 1 || tf.type == 2) {
                // byte or ascii type
                tf.type == 1 ? tf.sType = "BYTE" : tf.sType = "ASCII";
                tf.numBytes = 1;

                if(tf.count > 4) {
                    fileReadSwapIf(file, (char*) &tf.valueOffset, 4, endian);

                    // save current address and then move to location of the values
                    address = file.tellg();
                    file.seekg(tf.valueOffset, std::ios::beg);
                }
                else {
                    // move address marker to start of next field
                    address = file.tellg();
                    address += 4;
                }

                for(unsigned long j = 0; j < tf.count; ++j) {
                    // read and store each value
                    file.read((char*) &val, 1);
                    tf.values.push_back(val);
                }
            }
            else if(tf.type == 3) {
                // short type
                tf.sType = "SHORT";
                tf.numBytes = 2;

                if(tf.count > 2) {
                    fileReadSwapIf(file, (char*) &tf.valueOffset, 4, endian);

                    // save current address and then move to location of the values
                    address = file.tellg();
                    file.seekg(tf.valueOffset, std::ios::beg);
                }
                else {
                    // move address marker to start of next field
                    address = file.tellg();
                    address += 4;
                }

                for(unsigned long j = 0; j < tf.count; ++j) {
                    // read and store each value
                    fileReadSwapIf(file, (char*) &val, 2, endian);
                    tf.values.push_back(val);
                }
            }
            else if(tf.type == 4) {
                // long type
                tf.sType = "LONG";
                tf.numBytes = 4;

                if(tf.count > 1) {
                    fileReadSwapIf(file, (char*) &tf.valueOffset, 4, endian);

                    // save current address and then move to location of the values
                    address = file.tellg();
                    file.seekg(tf.valueOffset, std::ios::beg);
                }
                else {
                    // move address marker to start of next field
                    address = file.tellg();
                    address += 4;
                }

                for(unsigned long j = 0; j < tf.count; ++j) {
                    // read and store each value
                    fileReadSwapIf(file, (char*) &val, 4, endian);
                    tf.values.push_back(val);
                }
            }
            else if(tf.type == 5) {
                // rational type
                tf.sType = "RATIONAL";
                tf.numBytes = 8;

                fileReadSwapIf(file, (char*) &tf.valueOffset, 4, endian);

                // save current address and then move to location of the values
                address = file.tellg();
                file.seekg(tf.valueOffset, std::ios::beg);

                for(unsigned long j = 0; j < tf.count * 2; ++j) {
                    // read and store each value
                    fileReadSwapIf(file, (char*) &val, 4, endian);
                    tf.values.push_back(val);
                }
            }
            else {
                // invalid type
                tf.sType = "UNKNOWN";
                tf.numBytes = -1;

                // just read in the value offset
                fileReadSwapIf(file, (char*) &tf.valueOffset, 4, endian);
            }

            if(validTagTypes.find(tf.tag) != validTagTypes.end() &&
                    *validTagTypes.at(tf.tag).begin() != "Any" &&
                    validTagTypes.at(tf.tag).find(tf.sType) == validTagTypes.at(tf.tag).end()
                    ) {
                // if tag is known and does not match expected type, print warning message
                std::cout << "WARNING: Tag " << tf.tag << " is not expected to be type " << tf.sType
                          << ". The image may not be processed properly." << std::endl;
            }
            // push the tiff field data onto our vector
            fields.push_back(tf);

            // moves to location of next field
            file.seekg(address);
        }
        file.close();
    }
    return fields;
}

// swapShortBytes
void Tiff_Input_Command::swapShortBytes(char* twoBytes) const
{
    unsigned char* tmp = (unsigned char*) twoBytes;
    unsigned int i;

    i = tmp[1];
    tmp[1] = tmp[0];
    tmp[0] = i;
}

// swapLongBytes
void Tiff_Input_Command::swapLongBytes(char* fourBytes) const
{
    unsigned char* tmp = (unsigned char*) fourBytes;
    unsigned int i;

    // swap outside bytes
    i = tmp[3];
    tmp[3] = tmp[0];
    tmp[0] = i;

    // swap inside bytes
    i = tmp[2];
    tmp[2] = tmp[1];
    tmp[1] = i;
}

// fileReadSwapIf
void Tiff_Input_Command::fileReadSwapIf(std::ifstream &file, char* varName, int numBytes,
                                        const std::string &endian) const
{
    file.read(varName, numBytes);
    if(endian != "II") {
        // if not little endian, need to byte swap
        if(numBytes == 2) {
            swapShortBytes(varName);
        }
        else {
            swapLongBytes(varName);
        }
    }
}
