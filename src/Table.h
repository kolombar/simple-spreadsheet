/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include <string>
#include <set>
#include <map>
#include "Cell.h"

/**
 * @brief A table (container) of cells.
 * @details Stores all cells in the spreadsheet and provides interface for interacting with then.
 */
class Table {
public:
    /**
     * Adds a new cell.
     * @param cell cell to be added
     * @return @class Table
     */
    Table & AddCell(const Cell & cell);

    /**
     * Deletes the cell specified by the coordinates.
     * @param coords coordinates of the cell to be deleted
     * @return @class Table
     */
    Table & DelCell(const Coords &coords);

    using const_iterator = std::map<Coords, std::unique_ptr<Cell>>::const_iterator;

    /**
     * Returns a numeric value of the cell (string cells are evaluated to 0)
     * @param coords coordinates of the cell whose value is to be returned
     * @return value of the specified cell
     */
    double GetCellNumericValue(const Coords &coords) const;

    /**
     * Returns a value of the cell that should be displayed in the spreadsheet.
     * @param coords coordinates of the cell whose value is to be returned
     * @return display value of the specified cell
     */
    std::string GetCellDisplayValue(const Coords &coords) const;

    /**
     * Checks whether there is already a cell created on specified coordinates.
     * @param coords coordinates of the cell whose existence is to be checked
     * @return true if the cell exists
     */
    bool ContainsCell(const Coords & coords) const;

    /**
     * Returns original (i.e. user-provided) value of the cell.
     * @param coords coordinates of the cell whose value is to be returned
     * @return original value of the cell
     */
    std::string GetCellOrigValue(const Coords &coords) const;

    const_iterator GetCellsBeginIterator() const;

    const_iterator GetCellsEndIterator() const;

    /**
     * Deletes all cells.
     * @return @class Table
     */
    Table & Clear();

    int GetCellColor(const Coords &coords) const;

    void SetCellColor(const Coords &coords, int newColor) const;

private:
    std::map<Coords, std::unique_ptr<Cell>> cells;
};

