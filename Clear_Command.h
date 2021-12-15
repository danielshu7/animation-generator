#ifndef CLEAR_COMMAND_H
#define CLEAR_COMMAND_H

#include "Command.h"

/*
 * Class:       Clear_Command
 * Description: Runs the clear command
 */
class Clear_Command : public Command {
public:
    // constructor
    explicit Clear_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Clear_Command(const Clear_Command&) = delete;
    const Clear_Command& operator=(const Clear_Command&) = delete;

    // destructor
    ~Clear_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Clear command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    clear
     * Description: Clears the screen, light and object lists; resets background color; prepares
     *              TiffWrite on the black screen
     * Arguments:   none
     * Returns:     none
     */
    void clear() const;
};


#endif //CLEAR_COMMAND_H
