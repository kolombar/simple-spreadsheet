/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 14.05.2021
 */

#pragma once

#include "Command.h"
#include "InteractiveBuffer.h"
#include "KeyboardControls.h"

/**
 * @brief Switches user from command to interactive mode.
 * @details In interactive mode, user can navigate through the spreadsheet, edit cells (i.e. insert new values or delete them), save spreadsheet to a file and load spreadsheet from a file. After switching back to command mode, all changes to the spreadsheet are preserved.
 */
class EditCommand : public Command {
public:
    EditCommand(const std::shared_ptr<Sheet> &newSheet,
                const std::shared_ptr<View> &view);

    /**
     * Executes the command, i.e. switches to interactive mode and takes care of all the actions done by the user in this mode.
     * @param args command arguments
     * @return true if the program should continue
     */
    bool Do(const std::shared_ptr<std::vector<std::string>> &args) override;

private:
    /**
     * Stores interactive actions taken by the user.
     */
    InteractiveBuffer interactiveBuffer;

    /**
     * Available keyboard controls.
     */
    KeyboardControls controls;

    /**
     * Adds new value to the selected cell, i.e. processes input from the user and if possible, sets it to the cell.
     */
    void ProcessCellValue();

    /**
     * Prints spreadsheet layout in interactive mode.
     */
    void Print() const;

    std::string GetCurrentCellCoords() const;

    /**
     * Deletes value of the selected cell.
     */
    void DeleteValue();

    /**
     * Saves spreadsheet to a file. File-type and file-path are provided by the user.
     */
    void SaveToFile() const;

    /**
     * Loads spreadsheet from a file. File-type and file-path are provided by the user.
     */
    void LoadFromFile();
};
