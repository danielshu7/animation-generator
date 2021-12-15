#ifndef TRIANGLE_COMMAND_H
#define TRIANGLE_COMMAND_H

#include "Command.h"

/*
 * Class:       Triangle_Command
 * Description: Runs the triangle command; creates Triangle model
 */
class Triangle_Command : public Command {
public:
    // constructor
    explicit Triangle_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Triangle_Command(const Triangle_Command&) = delete;
    const Triangle_Command& operator=(const Triangle_Command&) = delete;

    // destructor
    ~Triangle_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Triangle command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    triangle
     * Description: Sets up triangle object model
     * Arguments:   nParams - vertices, ambient color, reflected color
     * Returns:     void
     */
    void triangle(const double nParams[15]) const;
};


#endif //TRIANGLE_COMMAND_H
