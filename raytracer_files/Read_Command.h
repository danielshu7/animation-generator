#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include "Command.h"

// forward declaration for recursive purposes
class Dispatcher;

/*
 * Class:       Read_Command
 * Description: Runs the read command
 */
class Read_Command : Command {
public:
    // constructor
    explicit Read_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Read_Command(const Read_Command&) = delete;
    const Read_Command& operator=(const Read_Command&) = delete;

    // destructor
    ~Read_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Read command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    read
     * Description: Opens the specified file and handles each line of input; prepares for
     *              TiffWrite
     * Arguments:   none
     * Returns:     void
     * Pre:         depth has not reached MAX_DEPTH; parameters contains 1 file with path relative
     *              to the scripts folder or scripts/project4 folder; there should not be files
     *              of the same name in these folders
     */
    void read() const;
};


#endif //READ_COMMAND_H
