#ifndef ZOOM_COMMAND_H
#define ZOOM_COMMAND_H

#include "Command.h"

/*
 * Class:       Zoom_Command
 * Description: Runs the Zoom command
 */
class Zoom_Command : public Command {
public:
    // constructor
    explicit Zoom_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Zoom_Command(const Zoom_Command&) = delete;
    const Zoom_Command& operator=(const Zoom_Command&) = delete;

    // destructor
    ~Zoom_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Zoom command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;
};


#endif //ZOOM_COMMAND_H
