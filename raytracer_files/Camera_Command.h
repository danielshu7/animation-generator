#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "Command.h"

/*
 * Class:       Camera_Command
 * Description: Runs the camera command
 */
class Camera_Command :public Command {
public:
    // constructor
    explicit Camera_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Camera_Command(const Camera_Command&) = delete;
    const Camera_Command& operator=(const Camera_Command&) = delete;

    // destructor
    ~Camera_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Camera command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    camera
     * Description: Sets to pinhole camera perspective
     * Arguments:   none
     * Returns:     void
     */
    void camera(const double nParams[14])  const;
};


#endif //CAMERA_COMMAND_H
