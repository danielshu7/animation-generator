#ifndef TIFFSTAT_COMMAND_H
#define TIFFSTAT_COMMAND_H

#include "Tiff_Input_Command.h"

/*
 * Class:       TiffStat_Command
 * Description: Runs the TiffStat command
 */
class TiffStat_Command : public Tiff_Input_Command {
public:
    // constructor
    // opens ../docs/tagnames to fill the tag map
    explicit TiffStat_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    TiffStat_Command(const TiffStat_Command&) = delete;
    const TiffStat_Command& operator=(const TiffStat_Command&) = delete;

    // destructor
    ~TiffStat_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the TiffStat command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    tiffStat
     * Description: Opens the specified tiff file and prints out the field data
     * Arguments:   none
     * Returns:     void
     * Pre:         parameters contains 1 tiff file with path relative to the images folder
     */
    void tiffStat() const;

    // map to hold tag/tagname conversions
    std::map<unsigned short, std::string> tagMap;
};


#endif //TIFFSTAT_COMMAND_H
