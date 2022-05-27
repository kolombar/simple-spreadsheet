/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include "Command.h"
#include "Sheet.h"
#include "View.h"

/**
 * @brief A command that deletes the given cell.
 * @details This command accepts one argument - coordinates of the cell that should be deleted.
 */
class DelCommand : public Command {
public:
    DelCommand(const std::shared_ptr<Sheet> &newSheet,
               const std::shared_ptr<View> &view) : Command(newSheet, view, "Delete value") {};

    /**
     * Executes the command, i.e. deletes the given cell.
     * @param args command arguments
     * @return true if the execution was successful
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> & args) override;

};