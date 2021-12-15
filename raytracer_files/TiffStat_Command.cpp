#include "TiffStat_Command.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include <sstream>

// constructor
TiffStat_Command::TiffStat_Command(const std::vector<char*> & params) : Tiff_Input_Command(params)
{
    std::ifstream file("docs/tagnames");
    if (!file) {
        // enters if an error occurred while opening the file
        std::cout << "ERROR: \"tagnames\" file could not be opened" << std::endl;
        throw;
    }
    else {
        unsigned short curTag;
        std::string curName;
        while(file >> curTag) {
            file >> curName;
            tagMap.emplace(curTag, curName);
        }
    }
    file.close();
}

// run
void TiffStat_Command::run() const
{
    if(validNumParam(1,1, "TIFFSTAT")) {
        tiffStat();
    }
}

// tiffStat
void TiffStat_Command::tiffStat() const
{
    std::vector<TiffField> fields = tiffParse();
    if(fields.empty()) {
        // reaches here if something went wrong with opening/reading the file
        return;
    }

    // print the field data
    std::cout << "Number of TIFF fields = " << fields.size() << std::endl;
    for(int i = 0; i < fields.size(); ++i) {
        std::cout << "Tag  " << std::setw(5) << std::left << fields[i].tag;
        std::cout << std::setw(26) << std::right;
        if(tagMap.find(fields[i].tag) == tagMap.end()) {
            // if tag not in tagMap, then it is unknown
            std::cout << "UnknownTag";
        }
        else {
            // otherwise we print the tag name
            std::cout << tagMap.at(fields[i].tag);
        }

        std::cout << " " << std::setw(10) << std::left << fields[i].sType;
        std::cout << std::setw(5) << std::right << "Count ";
        std::cout << std::setw(5) << std::left << fields[i].count;

        std::stringstream toPrint;
        if(fields[i].type <= 5) {
            // print value if not unknown type
            toPrint << " Value:       ";
            if(fields[i].type == 5) {
                // rationals take 2 longs each
                for(unsigned long j = 0; j < fields[i].count * 2; j += 2) {
                    unsigned long num = fields[i].values[j];
                    long denom = fields[i].values[j+1];
                    if(num % denom == 0) {
                        toPrint << num / denom << "\t";
                    }
                    else {
                        toPrint << fields[i].values[j] << " / " << fields[i].values[j+1] << "\t";
                    }
                }
            }
            else if(fields[i].type == 2) {
                // ascii's need conversion
                for(long j = 0; j < fields[i].count; ++j) {
                    char c = (char) fields[i].values[j];
                    toPrint << c;
                }
            }
            else {
                for(long j = 0; j < fields[i].count; ++j) {
                    toPrint << fields[i].values[j] << " ";
                }
            }
        }

        if(toPrint.str().size() <= 70 && !toPrint.str().empty()) {
            // if not to long or empty, print the entire value
            std::cout << toPrint.str();
        }
        else {
            // otherwise print valueOffset (isn't 0 because value can't fit in 4 bytes)
            std::cout << " ValueOffset: " << fields[i].valueOffset;
        } // print nothing in any other case
        std::cout << std::endl;
    }

}
