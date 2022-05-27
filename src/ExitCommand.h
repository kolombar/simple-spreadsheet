/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 14.05.2021
 */

#pragma once

#include "View.h"
#include "Command.h"

/**
 * @brief Exits the program.
 * @details Upon entering this command, spreadsheet is immediately exited. The command does not taky any arguments - if the user provides any, error is reported and the command is ignored.
 */
class ExitCommand : public Command {
public:
    ExitCommand(const std::shared_ptr<Sheet> &newSheet,
    const std::shared_ptr<View> &view) : Command(newSheet, view, "Exit program") {};

    /**
     * Executes the command, i.e. exits the program.
     * @param args arguments provided by the user
     * @return true if the program should continue, false otherwise
     */
    bool Do(const std::shared_ptr<std::vector<std::string>>& args) override;

};
