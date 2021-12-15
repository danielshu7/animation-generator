#ifndef TIFFWRITE_COMMAND_H
#define TIFFWRITE_COMMAND_H

#include "Command.h"
#include <GL/glut.h>
#include <set>

#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];


// set to hold all possible required tags
const std::set<unsigned short> reqTags = {256, 257, 258, 259, 262, 273,
                                          277, 278, 279, 282, 283, 296};


// forward declaration
class Screen_Command;

/*
 * Class:       TiffWrite_Command
 * Description: Runs the TiffWrite command
 */
class TiffWrite_Command : public Command {
public:
    // constructor
    explicit TiffWrite_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    TiffWrite_Command(const TiffWrite_Command&) = delete;
    const TiffWrite_Command& operator=(const TiffWrite_Command&) = delete;

    // destructor
    ~TiffWrite_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the TiffWrite command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    tiffWrite
     * Description: Creates a Tiff file in the images folder based on the previously read Tiff file
     * Arguments:   nParams - last 4 parameters as unsigned long
     * Returns:     void
     * Pre:         nParams contains the coordinates of the lower left and upper right corners
     */
    void tiffWrite(const unsigned long* const nParams) const;

    /*
     * Function:    paramToNum
     * Description: Checks if the last 4 parameters are numeric and returns them as doubles
     * Arguments:   nParams - an empty array to store the converted parameters
     * Returns:     bool - false if conversion fails, true otherwise
     * Pre:         nParams is not null
     */
    bool paramToNum(double nParams[4]) const noexcept override;

    /*
     * Function:    prepWrite
     * Description: Static method that pulls data from screen to array and prepares field struct
     * Arguments:   none
     * Returns:     none
     * Pre:         width, height have been set by a projection command (Ortho/Perspective)
     */
    static void prepWrite();

    // friend classes to access prepWrite
    friend class Vertex_Command;
    friend class Read_Command;
    friend class Reset_Command;
    friend class Trace_Command;
    friend class Clear_Command;
    friend class Screen_Command;
};


#endif //TIFFWRITE_COMMAND_H
