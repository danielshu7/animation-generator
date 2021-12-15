#ifndef POP_COMMAND_H
#define POP_COMMAND_H

#include "Command.h"

/*
 * Class:       Pop_Command
 * Description: Runs the pop command
 */
class Pop_Command : public Command {
public:
    // constructor
    explicit Pop_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Pop_Command(const Pop_Command&) = delete;
    const Pop_Command& operator=(const Pop_Command&) = delete;

    // destructor
    ~Pop_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Pop command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    pop
     * Description: Pops the current transformation matrix from the stack
     * Arguments:   none
     * Returns:     none
     */
    void pop() const;
};


#endif //POP_COMMAND_H
