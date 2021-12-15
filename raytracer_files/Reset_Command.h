#ifndef RESET_COMMAND_H
#define RESET_COMMAND_H

#include "Command.h"

/*
 * Class:       Reset_Command
 * Description: Runs the reset command
 */
class Reset_Command : public Command {
public:
    // constructor
    explicit Reset_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Reset_Command(const Reset_Command&) = delete;
    const Reset_Command& operator=(const Reset_Command&) = delete;

    // destructor
    ~Reset_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Reset command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    reset
     * Description: Clears the screen and matrix stack; prepares TiffWrite on the black screen
     * Arguments:   none
     * Returns:     none
     */
    void reset() const;
};


#endif //RESET_COMMAND_H
