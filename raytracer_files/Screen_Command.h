#ifndef SCREEN_COMMAND_H
#define SCREEN_COMMAND_H

#include "Command.h"

//forward declaration
class TiffWrite_Command;

/*
 * Class:       Screen_Command
 * Description: Runs the screen command
 */
class Screen_Command : public Command {
public:
    // constructor
    explicit Screen_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Screen_Command(const Screen_Command&) = delete;
    const Screen_Command& operator=(const Screen_Command&) = delete;

    // destructor
    ~Screen_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Screen command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    screen
     * Description: Sets the size of the screen/window; preps tiffwrite
     * Arguments:   nParams - width and length as doubles
     * Returns:     void
     */
    void screen(const double nParams[2])  const;

    // static screen dimensions
    static long screenWidth;
    static long screenHeight;

    // friend class
    friend class TiffWrite_Command;
    friend class Trace_Command;
};


#endif //SCREEN_COMMAND_H
