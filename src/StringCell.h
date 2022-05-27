/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include "Cell.h"

#include <utility>

/**
 * @brief A class representing a cell holding a string value.
 */
class StringCell : public Cell {
public:
    StringCell(const std::string &coords, const std::string &val) : Cell(coords, val) {};

    StringCell(const Coords &coords, const std::string &val) : Cell(coords, val) {};

    std::unique_ptr<Cell> Clone() const override;

    /**
     * Returns a value that should be displayed in the spreadsheet.
     * @return value that should be displayed in the spreadsheet
     */
    std::string GetDisplayValue() const override;
};

