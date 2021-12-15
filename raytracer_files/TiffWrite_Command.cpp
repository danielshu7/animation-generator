#include "TiffWrite_Command.h"
#include "TiffRead_Command.h"
#include "3D.h"
#include "Screen_Command.h"
#include <iostream>
#include <cerrno>
#include <fstream>
#include <algorithm>
#include <cmath>

#define tiffData TiffRead_Command::lastReadTiff

// constructor
TiffWrite_Command::TiffWrite_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void TiffWrite_Command::run() const
{
    if(tiffData.fields.empty()) {
        // no tiff file has been read in
        std::cout << "ERROR: Please read in a TIFF file first." << std::endl;
        return;
    }

    std::cout << "Writing ";
    if(validNumParam(1, 5, "TIFFWRITE")) {
        double* nParams = new double[4];
        if(paramToNum(nParams)) {
            // convert to unsigned longs
            unsigned long* iParams = new unsigned long[4];
            for(int i = 0; i < 4; ++i) {
                iParams[i] = (unsigned long) nParams[i];
            }
            tiffWrite(iParams);
            delete[] iParams;
        }
        delete[] nParams;
    }
}

// tiffWrite
void TiffWrite_Command::tiffWrite(const unsigned long* const nParams) const
{
    // first create a map of all the necessary fields (ignore defaults) and determine their values
    std::map<unsigned short, TiffField> reqFields;
    unsigned long StripsPerImage;  // strips per to use for num of strip offsets & strip byte counts
    for(unsigned short i = 0; i < tiffData.fields.size(); ++i) {
        TiffField field = tiffData.fields[i];
        if(reqTags.find(field.tag) != reqTags.end()) {
            // found a required tag
            if(field.tag == 277 && tiffData.type == "Grayscale") {
                // skip Samples Per Pixel if grayscale
                continue;
            }

            if(field.tag == 256) {
                // change Image Width
                field.values[0] = nParams[2] - nParams[0] + 1;
            }
            else if(field.tag == 257) {
                // change Image Length
                field.values[0] = nParams[3] - nParams[1] + 1;
            }
            else if(field.tag == 278) {
                // determine rows per strip; target 8 kB per strip but can't fall below 1
                unsigned long value = std::max(8000 / reqFields[256].values[0], (unsigned long) 1);

                if(tiffData.type == "RGB") {
                    value = std::max(value / 3, (unsigned long) 1);
                }
                else if(reqFields[258].values[0] == 4) {
                    value *= 2;
                } // value already fine if grayscale with 8 bits per sample
                field.values[0] = value;
            }
            else if(field.tag == 279) {
                // determine strip byte counts
                field.type = 3;
                field.sType = "SHORT";
                field.numBytes = 2;

                StripsPerImage = (reqFields[257].values[0] + reqFields[278].values[0] - 1)
                                    / reqFields[278].values[0];
                field.count = StripsPerImage;
                field.values.clear();

                unsigned long value = reqFields[278].values[0] * reqFields[256].values[0];
                if(tiffData.type == "RGB") {
                    value *= 3;
                }
                else if(reqFields[258].values[0] == 4) {
                    value /= 2;
                } // value already fine if grayscale with 8 bits per sample
                for(unsigned long j = 0; j < StripsPerImage - 1; ++j) {
                    field.values.push_back(value);
                }


                // determine last strip
                const unsigned long rowsLastStrip = reqFields[257].values[0]
                                                    % reqFields[278].values[0];
                if(rowsLastStrip == 0) {
                    // last strip is same as the others
                    field.values.push_back(value);
                }
                else {
                    // otherwise less rows than others means different byte count
                    value = rowsLastStrip * reqFields[256].values[0];
                    if(tiffData.type == "RGB") {
                        value *= 3;
                    }
                    else if(reqFields[258].values[0] == 4) {
                        value /= 2;
                    } // value already fine if grayscale with 8 bits per sample
                    field.values.push_back(value);
                } // otherwise nothing to do
            } // for others, just copy
            // note: keeps types the same except for strip byte counts
            reqFields.emplace(field.tag, field);
        }  // skip otherwise
    }


    // configure strip offsets; simply place data immediately after the ifd
    unsigned long fieldCount = reqFields.size();
    unsigned long nextAvailAddress = 8 + 2 + fieldCount * 12 + 4; // image header is 8, ifdCount 2,
                                                    // each field is 12, 4 bytes at end for next ifd
    reqFields[273].type = 4;  // just use LONG
    reqFields[273].sType = "LONG";
    reqFields[273].numBytes = 4;
    reqFields[273].count = StripsPerImage;
    reqFields[273].values.clear();
    for(unsigned long i = 0; i < reqFields[273].count; ++i) {
        reqFields[273].values.push_back(nextAvailAddress);
        nextAvailAddress += reqFields[279].values[i];
    }


    // determine all offsets
    for(auto iter = reqFields.begin(); iter != reqFields.end(); ++iter)
    {
        if(iter->first == 256 || iter->first == 257 || iter->first == 278) {
            continue; // already done for ImageWidth, ImageLength, RowsPerStrip
        }
        else { // everything else depends on whether the value fits in valueOffset
            unsigned long totValSize = iter->second.count * iter->second.numBytes;
            if(totValSize > 4) {
                // value doesn't fit in valueOffset
                iter->second.valueOffset = nextAvailAddress;
                nextAvailAddress += totValSize;
            }  // otherwise the values will be in valueOffset
        }
    }


    // start writing the data to the file
    std::string filename = parameters[0];
    std::cout << filename << "..." << std::endl;
    filename = "images/" + filename;

    std::ofstream file;
    file.open(filename.c_str(), std::ios::binary | std::ofstream::trunc);

    if(!file) {
        // enters if an error occurred while opening the file
        std::cout << "ERROR: The file \"" << filename << "\" could not be created and opened."
                << std::endl;
        return;
    }
    else {
        // write header
        file.write(tiffData.endian, 2);
        file.write((char*) &tiffData.magicNum, 2);
        file.write((char*) &tiffData.ifdAddress,4);
        file.seekp(tiffData.ifdAddress, std::ios::beg);
        unsigned short ifdCount = reqFields.size();

        // write ifd and values
        file.write((char*) &ifdCount, 2);
        for(auto iter = reqFields.begin(); iter != reqFields.end(); ++iter)
        {
            file.write((char*) &(iter->second.tag), 2);
            file.write((char*) &(iter->second.type), 2);
            file.write((char*) &(iter->second.count), 4);

            unsigned long address = 0;
            if(iter->second.count * iter->second.numBytes > 4) {
                // value doesn't fit in valueOffset
                file.write((char*) &(iter->second.valueOffset), 4);

                // save current address and then move to location to write the values
                address = file.tellp();
                file.seekp(iter->second.valueOffset, std::ios::beg);
            }
            else {
                // move address marker to start of next field
                address = file.tellp();
                address += 4;
            }

            // write all the values
            for(unsigned long i = 0; i < iter->second.count; ++i) {
                if(iter->second.type == 5) {
                    // rationals are special
                    file.write((char*) &(iter->second.values[i * 2]), 4);
                    file.write((char*) &(iter->second.values[i * 2 + 1]), 4);
                }
                else {
                    file.write((char*) &(iter->second.values[i]), iter->second.numBytes);
                }
            }

            // moves to location of next field to write
            file.seekp(address);
        }


        // write address offset of next IFD, 0000 in this case
        unsigned long nextIFD = 0;
        file.write((char*) &nextIFD, 4);

        // write image data found in strip offsets
        unsigned long sampleNum = 0;  // current number of the sample
        for(unsigned long i = 0; i < StripsPerImage; ++i) {
            for(unsigned long j = 0; j < reqFields[279].values[i]; ++j) {
                // iterate through each byte of data in the strip
                unsigned short val = 0;

                if (tiffData.type == "Grayscale") {
                    // deal with grayscale image
                    unsigned long row = nParams[3] - sampleNum / reqFields[256].values[0];
                    unsigned long col = nParams[0] + sampleNum % reqFields[256].values[0];

                    val = checkImage[row][col][0];
                    if(reqFields[262].values[0] == 0) {
                        val = 255 - val;
                    } // otherwise val doesn't need to be flipped
                    if(reqFields[258].values[0] == 4) {
                        // first 4 bits
                        val /= 17;
                        val = val << 4;

                        // calculate row/col of next pixel
                        ++sampleNum;
                        row = nParams[3] - sampleNum / reqFields[256].values[0];
                        col = nParams[0] + sampleNum % reqFields[256].values[0];

                        // next 4 bits
                        unsigned short secVal = checkImage[row][col][0];
                        if(reqFields[262].values[0] == 0) {
                            secVal = 255 - secVal;
                        } // otherwise secVal doesn't need to be flipped
                        secVal /= 17;
                        val += secVal;
                    } // otherwise BitsPerSample is 8 and nothing else to do
                }
                else {
                    // deal with RGB image
                    unsigned long row = nParams[3] - (sampleNum / 3) / reqFields[256].values[0];
                    unsigned long col = nParams[0] + (sampleNum / 3) % reqFields[256].values[0];
                    val = checkImage[row][col][sampleNum % 3];
                }
                file.write((char*) &val, 1);
                ++sampleNum;
            }
        }
        file.close();

        std::cout << "Done writing." << std::endl;
    }
}

// paramToNum
bool TiffWrite_Command::paramToNum(double nParams[4]) const noexcept
{
    unsigned long width, length;

    for(unsigned short i = 0; i < tiffData.fields.size(); ++i) {
        if (tiffData.fields[i].tag == 256) {
            width = tiffData.fields[i].values[0];
        }
        else if(tiffData.fields[i].tag == 257) {
            length = tiffData.fields[i].values[0];
            break;
        }
    }

    errno = 0;
    for(int i = 1; i < parameters.size(); ++i) {
        char* end;
        nParams[i - 1] = std::strtod(parameters[i], &end);

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
        else if(nParams[i - 1] < 0) {
            std::cout << "ERROR: Coordinates cannot be negative." << std::endl;
            return false;
        }
        else if(nParams[i - 1] != std::floor(nParams[i - 1])) {
            std::cout << "ERROR: Coordinates must be an integral." << std::endl;
            return false;
        }
    }


    for(int i = parameters.size(); i < 3; ++i) {
        nParams[i - 1] = 0;  // first 2 coordinate values are default 0
    }

    if(parameters.size() < 5) {
        if(parameters.size() <= 3) {
            nParams[2] = width - 1; // default max width
        }
        nParams[3] = length - 1; // default max length
    }

    // upper bound range checking
    if(nParams[0] >= width || nParams[2] >= width|| nParams[1] >= length || nParams[3] >= length) {
        std::cout << "ERROR: Coordinate out of image size range." << std::endl;
        return false;
    }

    return true;
}

// prepWrite
void TiffWrite_Command::prepWrite()
{
    if(Screen_Command::screenHeight < 0 || Screen_Command::screenWidth < 0) {
        // get window size
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        width = abs(viewport[2]-viewport[0]);
        height = abs(viewport[3]-viewport[1]);
    }
    else {
        width = Screen_Command::screenWidth;
        height = Screen_Command::screenHeight;
    }


    // width and height of screen
    unsigned long w = width;
    unsigned long l = height;

    // read pixels from screen to array
  /*  for(unsigned long i = 0; i < l; ++i) {
        glReadPixels(0,i, w, 1, GL_RGB, GL_UNSIGNED_BYTE, checkImage[i]);
    }*/

    // create fields structure
    std::vector<TiffField> fields;
    // width
    TiffField tf = {256, 4, "LONG", 4, 1, 0, {w}};
    fields.push_back(tf);

    // height
    tf = {257, 4, "LONG", 4, 1, 0, {l}};
    fields.push_back(tf);

    // Bits per Sample
    tf = {258, 3, "SHORT", 2, 3, 0, {8, 8, 8}};
    fields.push_back(tf);

    // Compression
    tf = {259, 3, "SHORT", 2, 1, 0, {1}};
    fields.push_back(tf);

    // Photometric Interpretation
    tf = {262, 3, "SHORT", 2, 1, 0, {2}};
    fields.push_back(tf);

    // Strip Offsets - details later
    tf.tag = 273;
    fields.push_back(tf);

    // Samples per Pixel
    tf = {277, 3, "SHORT", 2, 1, 0, {3}};
    fields.push_back(tf);

    // Rows per Strip - details later
    tf = {278, 4, "LONG", 4, 1, 0, {0}};
    fields.push_back(tf);

    // Strip Byte Counts - details later
    tf.tag = 279;
    fields.push_back(tf);

    // X Res
    tf = {282, 5, "RATIONAL", 8, 1, 0, {96, 1}};
    fields.push_back(tf);

    // Y Res - same as X Res
    tf.tag = 283;
    fields.push_back(tf);

    // Resolution Unit
    tf = {296, 3, "SHORT", 2, 1, 0, {2}};
    fields.push_back(tf);

    // pass into static tiff data struct
    tiffData.fields = fields;
    tiffData.type = "RGB";
}
