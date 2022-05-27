/**
* @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
* @date 5/27/21
*/

#include <string>
#include <algorithm>
#include <iostream>
#include "Coords.h"
#include "View.h"

using namespace std;

Coords::Coords(const string &coords) : coords(coords) {
    PrepareCoords();
    ExtractLetterPart();
    ExtractNumericPart();
}

Coords::Coords(const Coords &c) {
    coords = c.coords;
    PrepareCoords();
    ExtractLetterPart();
    ExtractNumericPart();
}

Coords::Coords(int row, int col) : numericRow(row), numericCol(col) {
    SetCoordsFromNumeric();
}

void Coords::PrepareCoords() {
    coords.erase(remove_if(coords.begin(), coords.end(), ::isspace), coords.end());

    auto it = coords.begin();

    while (it != coords.end() && ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))) {
        *it = (char)toupper(*it);
        it++;
    }
}

bool Coords::IsValid() const {
    if (letterPart.empty() || numericPart.empty()) {
        return false;
    }

    if (!(letterPart.size() == 1 && letterPart[0] >= 'A' && letterPart[0] <= 'A' + View::ROWS - 1)) {
        return false;
    }

    int cols = stoi(numericPart);

    if (!(cols >= 1 && cols <= View::COLUMNS)) {
        return false;
    }

    return true;
}

void Coords::ExtractLetterPart() {
    auto it = coords.begin();

    while (it != coords.end() && ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))) {
        it++;
    }

    letterPart = string(coords.begin(), it);
}

void Coords::ExtractNumericPart() {
    auto it = coords.begin();

    while (it != coords.end() && !isdigit(*it)) {
        it++;
    }

    auto numericStart = it;

    while (it != coords.end() && isdigit(*it)) {
        it++;
    }

    numericPart = string(numericStart, it);
}

bool Coords::operator<(const Coords &rhs) const {
    return coords < rhs.coords;
}

bool Coords::operator==(const Coords &rhs) const {
    return coords == rhs.coords;
}

int Coords::GetNumericRow() const {
    return numericRow;
}

int Coords::GetNumericCol() const {
    return numericCol;
}

void Coords::SetNumericRow(int row) {
    numericRow = row;
    SetCoordsFromNumeric();
}

void Coords::SetNumericCol(int col) {
    numericCol = col;
    SetCoordsFromNumeric();
}

void Coords::SetCoordsFromNumeric() {
    coords = "";
    char let = 'A' + numericRow - 1;
    letterPart = string(1, let);
    numericPart = to_string(numericCol);
    coords += letterPart;
    coords += numericPart;
}

std::string Coords::ToString() const {
    return coords;
}

std::string Coords::GetRow() const {
    return letterPart;
}

std::string Coords::GetCol() const {
    return numericPart;
}