#ifndef SPHERE_COMMAND_H
#define SPHERE_COMMAND_H

#include "Command.h"

/*
 * Class:       Sphere_Command
 * Description: Runs the sphere command; creates Sphere model
 */
class Sphere_Command : public Command {
public:
    // constructor
    explicit Sphere_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Sphere_Command(const Sphere_Command&) = delete;
    const Sphere_Command& operator=(const Sphere_Command&) = delete;

    // destructor
    ~Sphere_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Sphere command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;


private:
    /*
     * Function:    sphere
     * Description: Sets up sphere object model
     * Arguments:   nParams - radius, center, ambient color, reflected color, specular color(def 0)
     * Returns:     void
     */
    void sphere(const double* const nParams) const;
};


#endif //SPHERE_COMMAND_H
