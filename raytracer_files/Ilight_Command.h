#ifndef ILIGHT_COMMAND_H
#define ILIGHT_COMMAND_H

#include "Command.h"
#include "Vector3.h"

// forward declaration
class Trace_Command;

/*
 * Struct:      Ilight
 * Description: struct representing light at infinity
 */
struct Ilight {
    Vector3 color;
    Vector3 direction;
};


/*
 * Class:       Ilight_Command
 * Description: Runs the ilight command; creates a light at infinity
 */
class Ilight_Command : public Command {
public:
    // constructor
    explicit Ilight_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Ilight_Command(const Ilight_Command&) = delete;
    const Ilight_Command& operator=(const Ilight_Command&) = delete;

    // destructor
    ~Ilight_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Ilight command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    ilight
     * Description: Sets up light at infinity model
     * Arguments:   nParams - rgb color, direction
     * Returns:     void
     */
    void ilight(const double nParams[6]) const;
};


#endif //ILIGHT_COMMAND_H
