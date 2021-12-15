#ifndef TIFF_INPUT_COMMAND_H
#define TIFF_INPUT_COMMAND_H

#include "Command.h"
#include <fstream>
#include <map>
#include <set>


/*
 * Struct:      TiffField
 * Description: Struct to hold all parts of a tiff field
 */
struct TiffField {
    unsigned short tag;
    unsigned short type;
    std::string sType;
    short numBytes;  // -1 if unknown
    unsigned long count;
    unsigned long valueOffset;

    std::vector<unsigned long> values;
};

// map to hold valid tag types
// Any: BYTE, ASCII, SHORT, LONG, RATIONAL
const std::map<unsigned short, std::set<std::string>> validTagTypes = {
        {254, {"LONG"}},
        {255, {"SHORT"}},
        {256, {"SHORT", "LONG"}},
        {257, {"SHORT", "LONG"}},
        {258, {"SHORT"}},
        {259, {"SHORT"}},
        {262, {"SHORT"}},
        {263, {"SHORT"}},
        {264, {"SHORT"}},
        {265, {"SHORT"}},
        {266, {"SHORT"}},
        {269, {"ASCII"}},
        {270, {"ASCII"}},
        {271, {"ASCII"}},
        {272, {"ASCII"}},
        {273, {"SHORT", "LONG"}},
        {274, {"SHORT"}},
        {277, {"SHORT"}},
        {278, {"SHORT", "LONG"}},
        {279, {"SHORT", "LONG"}},
        {280, {"SHORT"}},
        {281, {"SHORT"}},
        {282, {"RATIONAL"}},
        {283, {"RATIONAL"}},
        {284, {"SHORT"}},
        {285, {"ASCII"}},
        {286, {"RATIONAL"}},
        {287, {"RATIONAL"}},
        {288, {"LONG"}},
        {289, {"LONG"}},
        {290, {"SHORT"}},
        {291, {"SHORT"}},
        {292, {"LONG"}},
        {293, {"LONG"}},
        {296, {"SHORT"}},
        {297, {"SHORT"}},
        {301, {"SHORT"}},
        {305, {"ASCII"}},
        {306, {"ASCII"}},
        {315, {"ASCII"}},
        {316, {"ASCII"}},
        {317, {"SHORT"}},
        {318, {"RATIONAL"}},
        {319, {"RATIONAL"}},
        {320, {"SHORT"}},
        {321, {"SHORT"}},
        {322, {"SHORT", "LONG"}},
        {323, {"SHORT", "LONG"}},
        {324, {"LONG"}},
        {325, {"SHORT", "LONG"}},
        {332, {"SHORT"}},
        {333, {"ASCII"}},
        {334, {"SHORT"}},
        {336, {"BYTE", "SHORT"}},
        {337, {"ASCII"}},
        {338, {"SHORT"}},
        {339, {"SHORT"}},
        {340, {"Any"}},
        {341, {"Any"}},
        {342, {"SHORT"}},
        {512, {"SHORT"}},
        {513, {"LONG"}},
        {514, {"LONG"}},
        {515, {"SHORT"}},
        {517, {"SHORT"}},
        {518, {"SHORT"}},
        {519, {"LONG"}},
        {520, {"LONG"}},
        {521, {"LONG"}},
        {529, {"RATIONAL"}},
        {530, {"SHORT"}},
        {531, {"SHORT"}},
        {532, {"LONG"}},
        {33432, {"ASCII"}}
};


/*
 * Class:       Tiff_Input_Command
 * Description: Abstract class providing interface for commands needing to read a tiff file
 */
class Tiff_Input_Command : public Command {
public:
    // constructor to initialize the parameter vector
    explicit Tiff_Input_Command(const std::vector<char*> & params);

    // default dtor
    ~Tiff_Input_Command() override = default;

protected:
    /*
     * Function:    tiffParse
     * Description: Parses the input tiff file and returns the field information
     * Arguments:   none
     * Returns:     std::vector<TiffField> - vector holding all of the fields in ascending order of
     *              the tags; null if the file was not a tiff file
     * Pre:         parameters contains 1 file with path relative to the images folder
     */
    std::vector<TiffField> tiffParse() const;

    /*
     * Function:    swapShortBytes
     * Description: Swaps the bytes of a short
     * Arguments:   twoBytes - short to be byte swapped
     * Returns:     none
     */
    void swapShortBytes(char* twoBytes) const;

    /*
     * Function:    swapLongBytes
     * Description: Swaps the bytes of a long
     * Arguments:   twoBytes - long to be byte reversed
     * Returns:     none
     */
    void swapLongBytes(char* fourBytes) const;

    /*
     * Function:    fileReadSwapIf
     * Description: Reads bytes from file and swaps if needed
     * Arguments:   file - file to read data from
     *              varName - variable to read data into
     *              numBytes - number of bytes to read
     *              endian - endianness of the file; default little endian
     * Returns:     none
     * Pre:         numBytes is 2 or 4
     */
    void fileReadSwapIf(std::ifstream &file, char* varName, int numBytes,
                        const std::string &endian) const;
};


#endif //TIFF_INPUT_COMMAND_H
