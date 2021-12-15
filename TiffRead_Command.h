#ifndef TIFFREAD_COMMAND_H
#define TIFFREAD_COMMAND_H

#include "Tiff_Input_Command.h"
#include <GL/glut.h>

#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];
extern void display(void);

/*
 * Struct:      TiffData
 * Description: Struct to hold all parsed data of TIFF file.  Default little endian. Default
 *              ifdAddress immediately after image file header
 */
struct TiffData {
    char endian[3] = "II";
    const short magicNum = 42;
    unsigned long ifdAddress = 0x00000008;

    std::vector<TiffField> fields;
    std::string type;
};

/*
 * Class:       TiffRead_Command
 * Description: Runs the TiffRead command
 */
class TiffRead_Command : public Tiff_Input_Command {
public:
    // constructor
    explicit TiffRead_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    TiffRead_Command(const TiffRead_Command&) = delete;
    const TiffRead_Command& operator=(const TiffRead_Command&) = delete;

    // destructor
    ~TiffRead_Command() override = default;

    /*
     * Function:    run
     * Description: Checks parameters; then runs the TiffRead command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

    // static member to hold the data of the last read TIFF file
    static TiffData lastReadTiff;
private:
    /*
     * Function:    tiffRead
     * Description: Opens the specified tiff file, checks conditions, and attempts to displays it
     *              in the window; warns if a tag has unexpected value
     * Arguments:   none
     * Returns:     void
     * Pre:         parameters contains 1 tiff file with path relative to the images folder
     */
    void tiffRead() const;
};


#endif //TIFFREAD_COMMAND_H
