#ifndef PERSPECTIVE_COMMAND_H
#define PERSPECTIVE_COMMAND_H

#include "Command.h"

/*
 * Class:       Perspective_Command
 * Description: Runs the perspective command
 */
class Perspective_Command : public Command {
public:
    // constructor
    explicit Perspective_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Perspective_Command(const Perspective_Command&) = delete;
    const Perspective_Command& operator=(const Perspective_Command&) = delete;

    // destructor
    ~Perspective_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Perspective command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    perspective
     * Description: Use perspective projection
     * Arguments:   nParams - contains angle, aspect ratio, near and far values
     * Returns:     none
     */
    void perspective(const float nParams[4]) const;
};


#endif //PERSPECTIVE_COMMAND_H
