/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include <string>
#include "Cell.h"

/**
 * @brief A class representing a numeric cell.
 * @details Numeric cells store numbers and mathematical expressions. Every expression is parsed and evaluated, and only its numerical value is displayed in the spreadsheet.
 */
class NumberCell : public Cell {
public:
    explicit NumberCell(const std::string &coords) : Cell(coords) {};

    NumberCell(const std::string &coords, const std::string &origVal) : Cell(coords, origVal) {};

    NumberCell(const std::string &coords, const std::string &origVal, double val) : Cell(coords, origVal, val) {};

    explicit NumberCell(const Coords &coords) : Cell(coords) {};

    NumberCell(const Coords &coords, const std::string &origVal) : Cell(coords, origVal) {};

    NumberCell(const Coords &coords, const std::string &origVal, double val) : Cell(coords, origVal, val) {};

    std::unique_ptr<Cell> Clone() const override;

    /**
     * Returns the value that should be displayed in spreadsheet (i.e. some number).
     * @return value that should be displayed in spreadsheet
     */
    std::string GetDisplayValue() const override;
};

