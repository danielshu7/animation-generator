#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H

#include "Command.h"

/*
 * Class:       Draw_Command
 * Description: Runs the draw command
 */
class Draw_Command : public Command {
public:
    // constructor
    explicit Draw_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Draw_Command(const Draw_Command&) = delete;
    const Draw_Command& operator=(const Draw_Command&) = delete;

    // destructor
    ~Draw_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Draw command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    draw
     * Description: Prints the parameters of a draw command
     * Arguments:   nParams - parameters as doubles
     * Returns:     void
     * Pre:         nParams is not null
     */
    void draw(const double* const nParams)  const noexcept;
};


#endif //DRAW_COMMAND_H
