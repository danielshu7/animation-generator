#ifndef VERTEX_COMMAND_H
#define VERTEX_COMMAND_H

#include "Command.h"

// forward declaration
class Dispatcher;

/*
 * Class:       Vertex_Command
 * Description: Runs the vertex command
 */
class Vertex_Command : public Command {
public:
    // constructor
    explicit Vertex_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Vertex_Command(const Vertex_Command&) = delete;
    const Vertex_Command& operator=(const Vertex_Command&) = delete;

    // destructor
    ~Vertex_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Vertex command
     * Arguments:   none
     * Returns:     none
     * Pre:         A projection type has been set (Ortho or Perspective)
     */
    void run() const override;

private:
    /*
     * Function:    vertex
     * Description: Draws a line between pairs of points; prepares for TiffWrite if not called
     *              from a nested read file
     * Arguments:   nParams - coordinates of vertex
     * Returns:     none
     */
    void vertex(const float nParams[3]) const;
};


#endif //VERTEX_COMMAND_H
