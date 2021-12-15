#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"

/*
 * Class:       Move_Command
 * Description: Runs the move command
 */
class Move_Command : public Command {
public:
    // constructor
    explicit Move_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Move_Command(const Move_Command&) = delete;
    const Move_Command& operator=(const Move_Command&) = delete;

    // destructor
    ~Move_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Move command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    move
     * Description: Prints the parameters of a move command
     * Arguments:   nParams - parameters as doubles
     * Returns:     void
     * Pre:         nParams is not null
     */
    void move(const double* const nParams) const noexcept;
};


#endif //MOVE_COMMAND_H
