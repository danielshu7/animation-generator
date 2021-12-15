#include "TiffRead_Command.h"
#include <iostream>
#include <climits>


// constructor
TiffRead_Command::TiffRead_Command(const std::vector<char*> & params) : Tiff_Input_Command(params)
{}

// run
void TiffRead_Command::run() const
{
    std::cout << "Reading ";
    if(validNumParam(1,1, "TIFFREAD")) {
        tiffRead();
    }
}

// tiffRead
void TiffRead_Command::tiffRead() const
{
    std::vector<TiffField> fields = tiffParse();
    if(fields.empty()) {
        // reaches here if something went wrong with opening/reading the file
        return;
    }

    // convert container into a map
    std::map<unsigned short, std::vector<unsigned long>> tagValues;
    for(int i = 0; i < fields.size(); ++i) {
        tagValues.emplace(fields[i].tag, fields[i].values);
    }

    // gather and check relevant data
    const unsigned short PhotometricInterpretation = tagValues.at(262)[0];
    if(PhotometricInterpretation > 2) {
        // not grayscale or RGB: not supported
        std::cout << "ERROR: Reading this TIFF file is not supported (not Grayscale or RGB)."
                << std::endl;
        return;
    }

    const unsigned short PlanarConfiguration = (tagValues.find(284) == tagValues.end())
                                                ? 1 // by default
                                                : tagValues[284][0];
    if(PlanarConfiguration != 1) {
        // only supports Chunky format
        std::cout << "ERROR: Baseline TIFF reader only supports Chunky format." << std::endl;
        return;
    }

    const unsigned short Compression = (tagValues.find(259) == tagValues.end())
                                        ? 1 // 1 by default
                                        : tagValues[259][0];
    if(Compression != 1) {
        // only supports uncompressed format
        std::cout << "ERROR: Reading compressed TIFF files is not supported." << std::endl;
        return;
    }

    const unsigned long ImageLength = tagValues.at(257)[0];
    const unsigned long ImageWidth = tagValues.at(256)[0];
    if(ImageLength > 1024 || ImageWidth > 1024) {
        // only supports max dimensions of 1024 x 1024
        std::cout << "ERROR: Max image dimensions are 1024 x 1024." << std::endl;
        return;
    }

    const unsigned short SamplesPerPixel = (tagValues.find(277) == tagValues.end())
                                            ? 1  // 1 by default
                                            : tagValues[277][0];
    if(SamplesPerPixel > 3) {
        // does not support extra samples per pixel
        std::cout << "ERROR: Only supports up to 3 samples per pixel." << std::endl;
        return;
    }

    if(tagValues.find(339) != tagValues.end()) {
        // checks SampleFormat tag
        for(unsigned short i = 0; i < SamplesPerPixel; ++i) {
            if(tagValues[339][i] != 1) {
                std::cout << "ERROR: Only supports pixel data as unsigned integers." << std::endl;
                return;
            }
        }
    }

    const std::vector<unsigned long> BitsPerSample = (tagValues.find(258) == tagValues.end())
                                                        ? std::vector<unsigned long>
                                                                (SamplesPerPixel, 1)
                                                        : tagValues[258];

    bool grayscale = PhotometricInterpretation < 2
                        && SamplesPerPixel == 1
                        && (BitsPerSample[0] == 4 || BitsPerSample[0] == 8);
    bool RGB = PhotometricInterpretation == 2
                && SamplesPerPixel == 3
                && (BitsPerSample[0] == 8 && BitsPerSample[1] == 8 && BitsPerSample[2] == 8);
    if(!(grayscale || RGB)) {
        // not either supported type
        std::cout << "ERROR: Only supports standard Grayscale and RGB Tiff files." << std::endl;
        return;
    }


    // data locations
    const unsigned long RowsPerStrip = (tagValues.find(278) == tagValues.end())
                                        ? ULONG_MAX  // 2^32 - 1 by default (max unsigned long)
                                        : tagValues[278][0];
    const unsigned long StripsPerImage = (ImageLength + RowsPerStrip - 1) / RowsPerStrip;
    const std::vector<unsigned long> StripOffsets = tagValues.at(273);
    const std::vector<unsigned long> StripByteCounts = tagValues.at(279);

    //reshape window
//    glutReshapeWindow(ImageWidth, ImageLength);

    // open file to read image data
    std::string filename = parameters[0];
    std::cout << filename << "..." << std::endl;
    filename = "images/" + filename;

    std::ifstream file;
    file.open (filename.c_str(), std::ios::binary );
    if(!file) {
        // enters if an error occurred while opening the file
        std::cout << "ERROR: The file \"" << filename << "\" could not be opened." << std::endl;
        return;
    }
    else {
        unsigned long sampleNum = 0;  // current number of the sample
        for(unsigned long i = 0; i < StripsPerImage; ++i) {
            // iterate through each strip
            file.seekg(StripOffsets[i], std::ios::beg);  // move to beginning of strip

            for(unsigned long j = 0; j < StripByteCounts[i]; ++j) {
                // iterate through each byte of data in the strip
                unsigned short val = 0;
                file.read((char*) &val, 1);

                if (grayscale) {
                    // deal with grayscale image
                    unsigned long row = ImageLength - sampleNum / ImageWidth - 1;
                    unsigned long col = sampleNum % ImageWidth;
                    if(BitsPerSample[0] == 4) {
                        // first 4 bits
                        unsigned short trueVal = val >> 4;
                        trueVal *= 17;
                        if(PhotometricInterpretation == 0) {
                            trueVal = 255 - trueVal;
                        } // otherwise already fine
                        checkImage[row][col][0] = trueVal;
                        checkImage[row][col][1] = trueVal;
                        checkImage[row][col][2] = trueVal;

                        // calculate row/col of next pixel
                        ++sampleNum;
                        row = ImageLength - sampleNum / ImageWidth - 1;
                        col = sampleNum % ImageWidth;


                        // next 4 bits
                        trueVal = val & 0xF;
                        trueVal *= 17;
                        if(PhotometricInterpretation == 0) {
                            trueVal = 255 - trueVal;
                        } // otherwise already fine
                        checkImage[row][col][0] = trueVal;
                        checkImage[row][col][1] = trueVal;
                        checkImage[row][col][2] = trueVal;
                    }
                    else { // BitsPerSample is 8
                        if(PhotometricInterpretation == 0) {
                            val = 255 - val;
                        } // otherwise val is already fine
                        checkImage[row][col][0] = val;
                        checkImage[row][col][1] = val;
                        checkImage[row][col][2] = val;
                    }
                }
                else {
                    // deal with RGB image
                    unsigned long row = ImageLength - (sampleNum / 3) / ImageWidth - 1;
                    unsigned long col = (sampleNum / 3) % ImageWidth;
                    checkImage[row][col][sampleNum % 3] = val;
                }
                ++sampleNum;
            }
        }
        display();
        file.close();

        // store fields data in lastReadTiff if everything was successful
        lastReadTiff.fields = fields;
        lastReadTiff.type = grayscale ? "Grayscale" : "RGB";

        std::cout << "Done reading." << std::endl;
    }
}
