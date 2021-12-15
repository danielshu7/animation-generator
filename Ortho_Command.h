#ifndef ORTHO_COMMAND_H
#define ORTHO_COMMAND_H

#include "Command.h"

/*
 * Class:       Ortho_Command
 * Description: Runs the ortho command
 */
class Ortho_Command : Command {
public:
    // constructor
    explicit Ortho_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Ortho_Command(const Ortho_Command&) = delete;
    const Ortho_Command& operator=(const Ortho_Command&) = delete;

    // destructor
    ~Ortho_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Ortho command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    ortho
     * Description: Use orthographic projection
     * Arguments:   nParams - coordinates of left, bottom, near corner and right, top, far corner
     * Returns:     none
     */
    void ortho(const float nParams[6]) const;
};


#endif //ORTHO_COMMAND_H
