/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include "Table.h"
#include "Parser/MathParser.h"
#include <map>

/**
 * @brief Main class representing spreadsheet.
 * @details It takes care of adding new cells to the spreadsheet, deleting existing cells, detecting cycles among cell references, updating cell values, and providing information about the state of the spreadsheet.
 */
class Sheet {
public:
    Sheet();

    /**
     * Adds a new cell to the spreadsheet, or updates value of an existing one.
     * @param coords coordinates of the cell
     * @param val value to be inserted
     * @return Sheet
     */
    Sheet & AddCell(const Coords &coords, const std::string &val);

    /**
     * Deletes the cell specified by the given coordinates.
     * @param coords coordinates of the cell to be deleted
     * @return Sheet
     */
    Sheet & DeleteCell(const Coords &coords);

    /**
     * Returns a value of the cell specified by the coordinates that should be displayed in the spreadsheet.
     * @param coords coordinates of the cell whose display value should be returned
     * @return display value of the specified cell
     */
    std::string GetDisplayValue(const Coords &coords) const;

    /**
     * Returns an original value (i.e. a value entered by the user) of the cell specified by the coordinates.
     * @param coords coordinates of the cell whose value should be returned
     * @return original (i.e. user provided) value of the cell
     */
    std::string GetOriginalValue(const Coords &coords) const;

    /**
     * Returns a numeric value of the cell specified by the coordinates. Cells holding string values are evaluated to zero.
     * @param coords coordinates of the cell whose numeric value should be returned
     * @return numeric value of the cell
     */
    double GetNumericValue(const Coords &coords) const;

    Table::const_iterator GetCellsBeginIterator() const;

    Table::const_iterator GetCellsEndIterator() const;

    /**
     * Clears the spreadsheet, i.e. deletes values of all cells.
     * @return Sheet
     */
    Sheet & Clear();

    int GetCellColor(const Coords &coords) const;

    void SetCellColor(const Coords &coords, int newColor) const;

    friend class SheetTests;

private:
    std::shared_ptr<Table> table;

    std::map<Coords, std::set<Coords>> cellDependencies;

    MathParser parser;

    enum class DfsStatus {
        FRESH, OPEN, CLOSED
    };

    /**
     * Adds dependencies (i.e. references to other cells represented by their coordinates) for a cell specified by the coordinates
     * @param coords coordinates of the cell whose dependencies should be added
     * @param deps dependencies (i.e. references to other cells) to be added
     */
    void AddDependencies(const Coords &coords, const std::set<Coords> &deps);

    /**
     * Removes specified dependencies (i.e. references to other cells) for the provided cell
     * @param coords coordinates of the cell whose dependencies should be removed
     * @param deps dependencies to be removed
     */
    void RemoveDependencies(const Coords &coords, const std::set<Coords> &deps);

    /**
     * Checks whether there are any cyclical references among cells.
     * @return true if a cycle is detected
     */
    bool IsCyclePresent() const;

    bool DfsScan(const Coords &coords, std::map<Coords, DfsStatus> &dfsTable) const;

    /**
     * Updates cells values based on changed dependencies.
     * @param coords coordinates of the changed cell
     */
    void UpdateCells(const Coords &coords);
};

