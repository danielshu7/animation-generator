#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <string>
#include <vector>

// forward declaration
class Read_Command;   // recursion
class Vertex_Command; // prepWrite only at depth 1
class Trace_Command; // prepWrite only at depth 1


// max depth of nested Dispatcher reads; initial Dispatcher is at depth 0
const int MAX_DEPTH = 6;


/*
 * Class: Dispatcher
 * Description: Event handler for all keyboard inputs.  Proper syntax for inputs is a command and
 *              optional parameters.  The command and first parameter should be separated by
 *              whitespace.  Parameters should be separated by whitespace or commas.  There may be
 *              whitespace before the command.  The last parameter may be followed by whitespace
 *              or commas.  Commands and parameters should not include whitespace or commas.
 */
class Dispatcher {
public:
    /*
     * Function:    Constructor
     * Description: Initializes the Dispatcher and parses the line of input
     */
    explicit Dispatcher(char* line);

    // Don't allow copy or assignment as there should never be a reason to use them
    Dispatcher(const Dispatcher&) = delete;
    const Dispatcher& operator=(const Dispatcher&) = delete;

    // Destructor
    ~Dispatcher() = default;

    /*
     * Function:    dispatch
     * Description: Selects the appropriate command to run
     * Arguments:   none
     * Returns:     void
     */
    void dispatch() const;

private:
    // members
    std::string cmd;
    std::vector<char*> parameters;

    // static member to hold the depth of reads that are currently running
    static int depth;

    // friend class to give access to depth
    friend class Read_Command;
    friend class Vertex_Command;
    friend class Trace_Command;
};



#endif //DISPATCHER_H
