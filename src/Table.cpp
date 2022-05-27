/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "Table.h"
#include "NumberCell.h"
#include <memory>
#include <iostream>

using namespace std;

Table &Table::AddCell(const Cell &cell) {
    Coords coords = cell.GetCoords();
    if (ContainsCell(coords)) {
        cells.erase(coords);
    }
    cells[coords] = cell.Clone();
    return *this;
}

bool Table::ContainsCell(const Coords &coords) const {
    if (cells.empty()) {
        return false;
    }

    for (auto &elem : cells) {
        if (elem.second->GetCoords() == coords) {
            return true;
        }
    }
    return false;
}

double Table::GetCellNumericValue(const Coords &coords) const {
    for (auto &cell : cells) {
        if (cell.second->GetCoords() == coords) {
            return cell.second->GetNumericValue();
        }
    }

    return 0;
}

std::string Table::GetCellDisplayValue(const Coords &coords) const {
    if (ContainsCell(coords)) {
        auto findVal = cells.find(coords);
        return findVal->second->GetDisplayValue();
    }
    return "";
}

std::string Table::GetCellOrigValue(const Coords &coords) const {
    if (ContainsCell(coords)) {
        auto findVal = cells.find(coords);
        return findVal->second->GetOrigValue();
    }
    return "";
}

Table & Table::DelCell(const Coords &coords) {
    if (ContainsCell(coords)) {
        cells.erase(coords);
    }

    return *this;
}

Table::const_iterator Table::GetCellsBeginIterator() const {
    return cells.begin();
}

Table::const_iterator Table::GetCellsEndIterator() const {
    return cells.end();
}

Table & Table::Clear() {
    cells.clear();
    return *this;
}

int Table::GetCellColor(const Coords & coords) const {
    if (ContainsCell(coords)) {
        return cells.find(coords)->second->GetDisplayColor();
    }

    return Cell::DEFAULT_COLOR;
}

void Table::SetCellColor(const Coords &coords, int newColor) const {
    if (ContainsCell(coords)) {
        cells.find(coords)->second->SetDisplayColor(newColor);
    }
}
