/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Sheet.h"
#include "Command.h"
#include "View.h"

/**
 * @brief Sets a value for the specified cell.
 * @details The user has to specify which cell should be modified by providing its coordinates. As a second argument new value for the cell should be provided. If the value start with an equality sign (=), it is considered to be a mathematical expression and is treated accordingly (i.e. parsed and evaluated).
 */
class SetCommand : public Command {
public:
    SetCommand(const std::shared_ptr<Sheet> &newSheet,
               const std::shared_ptr<View> &view) : Command(newSheet, view, "Set value") {};

    /**
     * Executes the command, i.e. sets a new value for the selected cell
     * @param args arguments provided by the user
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> & args) override;

};

