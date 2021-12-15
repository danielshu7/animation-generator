#ifndef SCALE_COMMAND_H
#define SCALE_COMMAND_H

#include "Command.h"

/*
 * Class:       Scale_Command
 * Description: Runs the scale command
 */
class Scale_Command : public Command {
public:
    // constructor
    explicit Scale_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Scale_Command(const Scale_Command&) = delete;
    const Scale_Command& operator=(const Scale_Command&) = delete;

    // destructor
    ~Scale_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Scale command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    scale
     * Description: scales the vector
     * Arguments:   nParams - x, y, and z scale factors
     * Returns:     none
     */
    void scale(const float nParams[3]) const;
};


#endif //README_MD_SCALE_COMMAND_H
