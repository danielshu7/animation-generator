#ifndef ORTHOCAMERA_COMMAND_H
#define ORTHOCAMERA_COMMAND_H

#include "Command.h"

/*
 * Class:       Orthocamera_Command
 * Description: Runs the orthocamera command
 */
class Orthocamera_Command : public Command {
public:
    // constructor
    explicit Orthocamera_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Orthocamera_Command(const Orthocamera_Command&) = delete;
    const Orthocamera_Command& operator=(const Orthocamera_Command&) = delete;

    // destructor
    ~Orthocamera_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Orthocamera command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    orthocamera
     * Description: Sets to orthocamera perspective
     * Arguments:   none
     * Returns:     void
     */
    void orthocamera()  const;
};


#endif //ORTHOCAMERA_COMMAND_H
