#ifndef PUSH_COMMAND_H
#define PUSH_COMMAND_H

#include "Command.h"

/*
 * Class:       Push_Command
 * Description: Runs the push command
 */
class Push_Command : public Command {
public:
    // constructor
    explicit Push_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Push_Command(const Push_Command&) = delete;
    const Push_Command& operator=(const Push_Command&) = delete;

    // destructor
    ~Push_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Push command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    push
     * Description: Pushes the current transformation matrix onto the stack
     * Arguments:   none
     * Returns:     none
     */
    void push() const;
};


#endif //PUSH_COMMAND_H
