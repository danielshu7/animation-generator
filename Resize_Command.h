#ifndef RESIZE_COMMAND_H
#define RESIZE_COMMAND_H

#include "Command.h"
#include <GL/glut.h>


#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];

/*
 * Class:       Resize_Command
 * Description: Runs the Resize command
 */
class Resize_Command : public Command {
public:
    // constructor
    explicit Resize_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Resize_Command(const Resize_Command&) = delete;
    const Resize_Command& operator=(const Resize_Command&) = delete;

    // destructor
    ~Resize_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Resize command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    resize
     * Description: Resizes the previously read Tiff file
     * Arguments:   nParams - parameters as doubles
     * Returns:     void
     */
    void resize(const double nParams[2]) const;

    /*
     * Function:    lanczos
     * Description: returns the value of the lanczos filter on the given parameters
     * Arguments:   x - lanczos input
     * Returns:     double - lanczos output
     */
    double lanczos(double x) const;

    /*
     * Function:    sinc
     * Description: returns the value of the standardized sinc function
     * Arguments:   x - sinc input
     * Returns:     double - sinc output
     */
    double sinc(double x) const;

    // friend class to access resize
    friend class Zoom_Command;
};


#endif //RESIZE_COMMAND_H
