/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "View.h"

/**
 * @brief A base class representing available commands.
 * @details The class provides interface for particular commands available to the user. It also enables child commands to set the status of last taken action in a unified way.
 */
class Command {
public:
    explicit Command(std::shared_ptr<Sheet> sheet, std::shared_ptr<View> view, const std::string &command) : sheet(
            std::move(sheet)), view(std::move(view)), commandStatusName(command) {};

    virtual ~Command() = default;

    /**
     * Executes the command.
     * @param args command arguments provided by the user.
     * @return true if the program should continue
     */
    virtual bool Do(const std::shared_ptr<std::vector<std::string>> &args) = 0;

protected:
    std::shared_ptr<Sheet> sheet;

    std::shared_ptr<View> view;

    std::string commandStatusName;

    /**
     * Sets ERROR status for last taken action because of wrong number of arguments provided by the user.
     */
    void SetWrongArgsStatus();

    /**
     * Sets OK status for the last taken action.
     */
    void SetOKStatus();

    /**
     * Sets ERROR status for the last taken action because of invalid cell coordinates provided by the user.
     */
    void SetWrongCoordsStatus();

    /**
     * Enables child commands to set ERROR status for the last taken action with a custom error message.
     * @param message error message
     */
    void SetCustomErrorStatus(const std::string &message);
};

