/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include "Command.h"

#include <utility>
#include "Sheet.h"
#include "View.h"

/**
 * @brief Shows values of all cells or of a one particular cell (depends on the arguments provided by the user). Mathematical expressions are not evaluated.
 * @details The user can specify coordinates of the cell, which value should be displayed. Otherwise values of all cells will be displayed. If more than one argument is provided, error is reported and the command is ignored.
 */
class ShowCommand : public Command {
public:
    ShowCommand(const std::shared_ptr<Sheet> &newSheet,
                const std::shared_ptr<View> &view) : Command(newSheet, view, "Show cell expressions") {};

    /**
     * Executes the command, i.e. displayes cell values.
     * @param args arguments provided by the user
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> &args) override;

};

