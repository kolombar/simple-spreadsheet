/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include <string>
#include <memory>
#include "Coords.h"

/**
 * @brief A base class representing a single cell in spreadsheet.
 * @details The base class provides interface for individual types of spreadsheet cells. Each cell has coordinates which defines its position in spreadsheet, a string value entered by the user, a numeric value and an associated color. The color is set based on cell dependencies, i.e. if a group of cells depends on each other, they all share the same color.
 */
class Cell {
public:
    Cell(const std::string &coords) : coords(coords), origValue(""), numericValue(0), displayColor(DEFAULT_COLOR) {};

    Cell(const std::string &coords, std::string val) : coords(coords), origValue(move(val)), numericValue(0), displayColor(DEFAULT_COLOR) {};

    Cell(const std::string &coords, std::string val, double numVal) : coords(coords), origValue(move(val)), numericValue(numVal), displayColor(DEFAULT_COLOR) {};

    Cell(const Coords &coords) : coords(coords), origValue(""), numericValue(0), displayColor(DEFAULT_COLOR) {};

    Cell(const Coords &coords, std::string val) : coords(coords), origValue(move(val)), numericValue(0), displayColor(DEFAULT_COLOR) {};

    Cell(const Coords &coords, std::string val, double numVal) : coords(coords), origValue(move(val)), numericValue(numVal), displayColor(DEFAULT_COLOR) {};

    virtual ~Cell() = default;

    virtual std::unique_ptr<Cell> Clone() const = 0;

    bool operator <(const Cell & rhs) const;

    /**
     * Gets a value of the cell that should be displayed in the spreadsheet.
     * @return value that should be displayed in the spredsheet
     */
    virtual std::string GetDisplayValue() const = 0;

    Coords GetCoords() const;

    double GetNumericValue() const;

    std::string GetOrigValue() const;

    int GetDisplayColor() const;

    void SetDisplayColor(int newColor);

    /**
     * Assigns a random color to a cell in case the cell needs a color and it does not have one yet.
     */
    void AssignRandomColor();

    static constexpr int DEFAULT_COLOR = 15;

protected:
    /**
     * Cell coordinates that determine location of the cell in spreadsheet.
     */
    Coords coords;

    /**
     * Original value entered by the user.
     */
    std::string origValue;

    /**
     * Calculated numeric value.
     */
    double numericValue;

    /**
     * Associated color. If one cell holds a reference to another cell, they share the same color.
     */
    int displayColor;
};

