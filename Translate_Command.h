#ifndef TRANSLATE_COMMAND_H
#define TRANSLATE_COMMAND_H

#include "Command.h"

/*
 * Class:       Translate_Command
 * Description: Runs the translate command
 */
class Translate_Command : public Command {
public:
    // constructor
    explicit Translate_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Translate_Command(const Translate_Command&) = delete;
    const Translate_Command& operator=(const Translate_Command&) = delete;

    // destructor
    ~Translate_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Translate command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    translate
     * Description: translates the vector
     * Arguments:   nParams - x, y, and z distances to translate by
     * Returns:     none
     */
    void translate(const float nParams[3]) const;
};


#endif //README_MD_TRANSLATE_COMMAND_H
