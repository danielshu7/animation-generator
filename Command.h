#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

/*
 * Class:       Command
 * Description: Abstract class providing interface for all commands.
 */
class Command {
public:
    // constructor to initialize the parameter vector
    explicit Command(const std::vector<char*> & params);

    // default dtor
    virtual ~Command() = default;

    /*
     * Function:    run
     * Description: Checks conditions; then runs the command
     * Arguments:   none
     * Returns:     none
     */
    virtual void run() const = 0;

protected:
    /*
     * Function:    validNumParam
     * Description: Checks if the number of parameters is within the acceptable range (for the
     *              given command)
     * Arguments:   min - the minimum allowable number of parameters
     *              max - the maximum allowable number of parameters
     *              cmd - the name of the command
     * Returns:     bool - true if number of parameters is acceptable, false otherwise
     */
    bool validNumParam(int min, int max, const std::string & cmd) const noexcept;

    /*
     * Function:    paramToNum
     * Description: Checks if the parameters are numeric and returns them as doubles
     * Arguments:   nParams - an empty array to store the converted parameters
     * Returns:     bool - false if conversion fails, true otherwise
     * Pre:         nParams is not null
     */
    virtual bool paramToNum(double* nParams) const noexcept;

    virtual bool paramToNum(float* nParams) const noexcept;

    // member parameters
    std::vector<char*> parameters;
};


#endif //COMMAND_H
