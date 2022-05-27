/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <memory>
#include <utility>
#include "Sheet.h"
#include "ActionStatus.h"

/**
 * @brief A class that takes care of displaying output.
 * @details It prints the spreadsheet itself and also the status bar of the last taken action. Moreover, it holds information about which cell is currently selected in interactive mode.
 */
class View {
public:
    View();

    View(const std::shared_ptr<Sheet> &newSheet) : sheet(newSheet) {};

    /**
     * Prints the spreadsheet.
     * @param highlightSelectedCell true only in interactive mode - the currently selected cell is then highlighted
     * @return View
     */
    View & PrintTable(bool highlightSelectedCell = false);

    /**
     * Prints the table displaying status of the last taken action.
     * @return View
     */
    const View & PrintStatusTable() const;

    /**
     * Sets status of the last action.
     * @param newState new status
     * @return View
     */
    View & SetCommandState(const ActionStatus & newState);

    ActionStatus GetCommandState() const;

    /**
     * Number of columns in the spreadsheet.
     */
    static int COLUMNS;

    /**
     * Number of rows in the spreadsheet.
     */
    static int ROWS;

    /**
     * Currently selected cell in interactive mode.
     */
    static Coords SELECTED_CELL;

    /**
     * Default spreadsheet size (in case user does not provide any).
     */
    static constexpr int DEFAULT_TABLE_SIZE = 5;
private:
    std::shared_ptr<Sheet> sheet;

    ActionStatus state;

    /**
     * Size of the cells.
     */
    const int CELL_SIZE = 7;

    /**
     * Size of the text that should be displayed.
     */
    const int OUTPUT_VIEW_SIZE = 5;

    int cellHighlightColor = 37;

    /**
     * Prints table borders.
     * @param underlinesToPrint size of borders to be printed
     * @param col column that is currently being printed
     */
    void PrintUnderline(int underlinesToPrint, int col) const;

    /**
     * Prints colored table borders.
     * @param underlinesToPrint size of borders to be printed
     */
    void PrintColoredUnderline(int underlinesToPrint) const;

    /**
     * Prints a particular cell.
     * @param spacesToPrint number of spaces to be printed on the left- and right-side of the cell value
     * @param displayValue cell value to be printed
     * @param displayColor cell color
     */
    void FillCell(int spacesToPrint, std::string displayValue, int displayColor) const;

    void PrintRowIndex(char letterToPrint) const;

    void PrintColIndex(int idx) const;

    /**
     * Prints a vertical line separating cells.
     * @param selectedColPrint columns of the currently selected cell (in interactive mode)
     * @param col column currently being printed
     */
    void PrintVLine(int selectedColPrint, int col) const;

    /**
     * Prints a particular cell in the status bar.
     * @param spacesToPrint spaces to be printed before and after the content
     * @param text text to be printed
     */
    void PrintStateCell(int spacesToPrint, const std::string & text) const;

    /**
     * Prints a cell displaying either success or failure of the last command.
     * @param spacesToPrint spaces to be printed before and after status indicator
     */
    void PrintCommandStateCell(int spacesToPrint) const;
};

