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
 * @brief Loads spreadsheet from a file.
 * @details The user can provide at most two arguments for the command - first is the format of file to be loaded (if no format is specified, default is TSV) and second is the path to the file (this argument is mandatory).
 */
class LoadCommand : public FileCommand {
public:
    LoadCommand(const std::shared_ptr<Sheet> &newSheet,
                const std::shared_ptr<View> &view) : FileCommand(newSheet, view, "Load from file") {};

    /**
     * Executes the command, i.e. load spreadsheet from a file or throws an exception if spreadsheet cannot be loaded.
     * @param args arguments provided by the user
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> & args) override;

};

