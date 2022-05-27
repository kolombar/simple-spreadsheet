/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "Cell.h"

constexpr int Cell::DEFAULT_COLOR;

bool Cell::operator<(const Cell &rhs) const {
    return coords < rhs.coords;
}

Coords Cell::GetCoords() const {
    return coords;
}

double Cell::GetNumericValue() const {
    return numericValue;
}

std::string Cell::GetOrigValue() const {
    return origValue;
}

int Cell::GetDisplayColor() const {
    return displayColor;
}

void Cell::SetDisplayColor(int newColor) {
    displayColor = newColor;
}

void Cell::AssignRandomColor() {
    int rangeStart = 17;
    int rangeEnd = 231;
    displayColor = rangeStart + ( rand() % ( rangeEnd - rangeStart + 1 ) );
}