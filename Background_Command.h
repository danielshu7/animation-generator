#ifndef BACKGROUND_COMMAND_H
#define BACKGROUND_COMMAND_H

#include "Command.h"
#include <GL/glut.h>

#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];
extern void display(void);

/*
 * Class:       Background_Command
 * Description: Runs the background command
 */
class Background_Command : public Command {
public:
    // constructor
    explicit Background_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Background_Command(const Background_Command&) = delete;
    const Background_Command& operator=(const Background_Command&) = delete;

    // destructor
    ~Background_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Background command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    background
     * Description: Sets the background color; clamps rgb values to [0, 1] range
     * Arguments:   nParams - rgb values of background
     * Returns:     void
     */
    void background(const double nParams[3])  const;
};


#endif //BACKGROUND_COMMAND_H
