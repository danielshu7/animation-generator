#ifndef COLOR_COMMAND_H
#define COLOR_COMMAND_H

#include "Command.h"

/*
 * Class:       Color_Command
 * Description: Runs the color command
 */
class Color_Command : public Command {
public:
    // constructor
    explicit Color_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Color_Command(const Color_Command&) = delete;
    const Color_Command& operator=(const Color_Command&) = delete;

    // destructor
    ~Color_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Color command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    color
     * Description: Prints the parameters of a color command
     * Arguments:   nParams - parameters as doubles
     * Returns:     void
     * Pre:         nParams is not null
     */
    void color(const double nParams[3]) const noexcept;
};


#endif //COLOR_COMMAND_H
