#ifndef LOOKAT_COMMAND_H
#define LOOKAT_COMMAND_H

#include "Command.h"

/*
 * Class:       LookAt_Command
 * Description: Runs the lookat command
 */
class LookAt_Command : public Command {
public:
    // constructor
    explicit LookAt_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    LookAt_Command(const LookAt_Command&) = delete;
    const LookAt_Command& operator=(const LookAt_Command&) = delete;

    // destructor
    ~LookAt_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Lookat command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    lookAt
     * Description: change the camera point of view
     * Arguments:   nParams - x,y,z coordinates of the new position, the point to look (dir),
     *                        and the orientation of upwards
     * Returns:     none
     */
    void lookAt(const float nParams[9]) const;
};


#endif //LOOKAT_COMMAND_H
