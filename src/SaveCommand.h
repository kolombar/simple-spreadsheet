/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <utility>
#include "Sheet.h"
#include "View.h"
#include "FileCommand.h"

/**
 * @brief Saves spreadsheet to a file.
 * @details The user can specify format of the file (optional, default is TSV) and path to the file (mandatory). If any of the arguments is not valid or it is not possible to write to specified file, error is reported and the command is ignored.
 */
class SaveCommand : public FileCommand {
public:
    SaveCommand(const std::shared_ptr<Sheet> &newSheet,
                const std::shared_ptr<View> &view) : FileCommand(newSheet, view, "Save to file") {};

    /**
     * Executes the command, i.e. saves spreadsheet to a file.
     * @param args arguments provided by the user
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> & args) override;
};

