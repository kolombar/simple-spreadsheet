/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <memory>
#include <utility>
#include "Sheet.h"
#include "View.h"
#include "Command.h"

/**
 * @brief Prints help, i.e. description of all available commands.
 * @details Help command does not take any arguments. If the user provides any, error is reported and the command is ignored.
 */
class HelpCommand : public Command {
public:
    HelpCommand(const std::shared_ptr<Sheet> &sheet,
                const std::shared_ptr<View> &view);

    /**
     * Executes the command, i.e. prints help.
     * @param args arguments provided by the user
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> &args) override;

private:
    /**
     * Stores descriptions of available commands.
     */
    std::map<std::string, std::string> helpMap;

    /**
     * Sets values (descriptions) to the help map.
     */
    void FillHelpMap();

    /**
     * Determines how big should be the table with help.
     * @return width of the first column and width of the second column, respectively
     */
    std::pair<int, int> GetHelpDimensions() const;

    /**
     * Prints the table with help (i.e. description of available commands).
     */
    void PrintHelpTable() const;

    /**
     * Prints a signle cell in the help table.
     * @param spacesToPrint number of spaces to be printed after the text
     * @param text text to be printed
     */
    void PrintHelpCell(int spacesToPrint, const std::string &text) const;

    /**
     * Prints underlines.
     * @param spacesToPrint number of underlines to print
     */
    void PrintUnderline(int spacesToPrint) const;

    /**
     * Prints table header.
     * @param firstColSize size of the first column header
     * @param secondColSize size of the second column header
     */
    void PrintHeader(int firstColSize, int secondColSize) const;

    /**
     * Color of the help table.
     */
    static constexpr int HELP_COLOR = 210;
};

