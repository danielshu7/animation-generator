#ifndef BOX_COMMAND_H
#define BOX_COMMAND_H

#include "Command.h"

/*
 * Class:       Box_Command
 * Description: Runs the box command; creates Box model
 */
class Box_Command : public Command {
public:
    // constructor
    explicit Box_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Box_Command(const Box_Command&) = delete;
    const Box_Command& operator=(const Box_Command&) = delete;

    // destructor
    ~Box_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Box command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    box
     * Description: Sets up 3D box object model
     * Arguments:   nParams - lower-left bottom corner, upper-right top corner, ambient color,
     *                  reflected color
     * Returns:     void
     */
    void box(const double nParams[12]) const;
};


#endif //MD_BOX_COMMAND_H
