#ifndef ROTATE_COMMAND_H
#define ROTATE_COMMAND_H

#include "Command.h"

/*
 * Class:       Rotate_Command
 * Description: Runs the rotate command
 */
class Rotate_Command : public Command {
public:
    // constructor
    explicit Rotate_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Rotate_Command(const Rotate_Command&) = delete;
    const Rotate_Command& operator=(const Rotate_Command&) = delete;

    // destructor
    ~Rotate_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Rotate command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    rotate
     * Description: rotate the vector about an axis passing through the origin
     * Arguments:   nParams - degree of rotation (counterclockwise); x, y, z directions of axis
     * Returns:     none
     */
    void rotate(const float nParams[4]) const;
};


#endif //ROTATE_COMMAND_H
