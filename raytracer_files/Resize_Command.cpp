#include "Resize_Command.h"
#include "TiffRead_Command.h"
#include <iostream>
#include <cmath>

#define tiffData TiffRead_Command::lastReadTiff

GLubyte tmpImage[checkImageHeight][checkImageWidth][3];

// constructor
Resize_Command::Resize_Command(const std::vector<char*> & params) : Command(params)
{}

// run
void Resize_Command::run() const
{
    if(tiffData.fields.empty()) {
        // no tiff file has been read in
        std::cout << "ERROR: Please read in a TIFF file first." << std::endl;
        return;
    }


    if(validNumParam(2, 2, "RESIZE")) {
        double* nParams = new double[2];
        if(paramToNum(nParams)) {
            resize(nParams);
        }
        delete[] nParams;
    }
}

// resize
void Resize_Command::resize(const double nParams[2]) const
{
    unsigned long oldWidth;
    unsigned long oldLength;
    int index;
    // get length and width
    for(unsigned short i = 0; i < tiffData.fields.size(); ++i) {
        TiffField field = tiffData.fields[i];
        if (field.tag == 256) {
            // Image Width
            oldWidth = field.values[0];
            index = i;
        } else if (field.tag == 257) {
            // Image Length
            oldLength = field.values[0];
        }
    }

    double xScale = std::abs(nParams[0]);
    double yScale = std::abs(nParams[1]);
    unsigned long newWidth = std::floor(xScale * oldWidth);
    unsigned long newLength = std::floor(yScale * oldLength);

    // scale x dir
    if(oldWidth != newWidth || nParams[0] < 0) {
        if(newWidth <= 0 || newWidth > 1024) {
            std::cout << "ERROR: Invalid width scale amount." << std::endl;
            return;
        }

        double M = std::min(xScale, (double) 1);
        for(unsigned long i = 0; i < oldLength; ++i) {
            for(unsigned long n = 0; n < newWidth; ++n) {
                double rIntensity = 0;
                double gIntensity = 0;
                double bIntensity = 0;
                for(unsigned long k = 0; k < oldWidth; ++k) {
                    double filter = lanczos(M * ((n / xScale) - k));
                    rIntensity += checkImage[i][k][0] * filter;
                    gIntensity += checkImage[i][k][1] * filter;
                    bIntensity += checkImage[i][k][2] * filter;
                }

                rIntensity *= M;
                gIntensity *= M;
                bIntensity *= M;

                // clamp the intensities
                rIntensity = std::max((double) 0, rIntensity);
                rIntensity = std::min((double) 255, rIntensity);
                gIntensity = std::max((double) 0, gIntensity);
                gIntensity = std::min((double) 255, gIntensity);
                bIntensity = std::max((double) 0, bIntensity);
                bIntensity = std::min((double) 255, bIntensity);

                // store new intensities
                if(nParams[0] > 0) {
                    // positive
                    tmpImage[i][n][0] = rIntensity;
                    tmpImage[i][n][1] = gIntensity;
                    tmpImage[i][n][2] = bIntensity;
                }
                else {
                    // if negative, need to reflect
                    tmpImage[i][newWidth - n - 1][0] = rIntensity;
                    tmpImage[i][newWidth - n - 1][1] = gIntensity;
                    tmpImage[i][newWidth - n - 1][2] = bIntensity;
                }
            }
        }

        // copy array
        for(int i = 0; i < oldLength; ++i) {
            for(int j = 0; j < newWidth; ++j) {
                checkImage[i][j][0] = tmpImage[i][j][0];
                checkImage[i][j][1] = tmpImage[i][j][1];
                checkImage[i][j][2] = tmpImage[i][j][2];
            }
        }
    }

    // scale y dir
    if(oldLength != newLength || nParams[1] < 0) {
        if(newLength <= 0 || newLength > 1024) {
            std::cout << "ERROR: Invalid length scale amount." << std::endl;
            return;
        }

        double M = std::min(yScale, (double) 1);
        for(unsigned long i = 0; i < newWidth; ++i) {
            for(unsigned long n = 0; n < newLength; ++n) {
                double rIntensity = 0;
                double gIntensity = 0;
                double bIntensity = 0;
                for(unsigned long k = 0; k < oldLength; ++k) {
                    double filter = lanczos(M * ((n / yScale) - k));
                    rIntensity += checkImage[k][i][0] * filter;
                    gIntensity += checkImage[k][i][1] * filter;
                    bIntensity += checkImage[k][i][2] * filter;
                }

                rIntensity *= M;
                gIntensity *= M;
                bIntensity *= M;

                // clamp the intensities
                rIntensity = std::max((double) 0, rIntensity);
                rIntensity = std::min((double) 255, rIntensity);
                gIntensity = std::max((double) 0, gIntensity);
                gIntensity = std::min((double) 255, gIntensity);
                bIntensity = std::max((double) 0, bIntensity);
                bIntensity = std::min((double) 255, bIntensity);

                // store new intensities
                if(nParams[1] > 0) {
                    // positive
                    tmpImage[n][i][0] = rIntensity;
                    tmpImage[n][i][1] = gIntensity;
                    tmpImage[n][i][2] = bIntensity;
                }
                else {
                    // if negative, need to reflect
                    tmpImage[newLength - n - 1][i][0] = rIntensity;
                    tmpImage[newLength - n - 1][i][1] = gIntensity;
                    tmpImage[newLength - n - 1][i][2] = bIntensity;
                }
            }
        }

        // copy array
        for(int i = 0; i < newLength; ++i) {
            for(int j = 0; j < newWidth; ++j) {
                checkImage[i][j][0] = tmpImage[i][j][0];
                checkImage[i][j][1] = tmpImage[i][j][1];
                checkImage[i][j][2] = tmpImage[i][j][2];
            }
        }
    }

    // rewrite altered fields
    tiffData.fields[index].values[0] = newWidth;
    tiffData.fields[index + 1].values[0] = newLength;

//    glutReshapeWindow(newWidth, newLength);

    std::cout << "Width: " << newWidth << ", Length: " << newLength << std::endl;
}

// lanczos
double Resize_Command::lanczos(double x) const
{
    if(x < 2 && x > -2) {
        return sinc(x) * sinc(x / 2);
    }
    return 0;
}

// sinc
double Resize_Command::sinc(double x) const
{
    if(x == 0) {
        return 1;
    }
    return std::sin(M_PI * x) / (M_PI * x);
}
