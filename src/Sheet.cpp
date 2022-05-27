/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "Sheet.h"

#include <memory>
#include "Parser/MathParser.h"
#include "NumberCell.h"
#include "StringCell.h"
#include "Parser/ParsedResult.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

Sheet::Sheet() : table(std::make_shared<Table>()), parser(table) {}

Sheet &Sheet::AddCell(const Coords &coords, const string &val) {
    auto it = val.begin();

    while (it != val.end() && isspace(*it)) {
        it++;
    }

    if (it != val.end() && *it == '=') {
        unique_ptr<ParsedResult> result = parser.Parse(string(++it, val.end()));
        NumberCell newCell = NumberCell(coords, val, result->GetResult());
        int oldColor = GetCellColor(coords);
        if (oldColor != Cell::DEFAULT_COLOR) {
            newCell.SetDisplayColor(oldColor);
        }
        AddDependencies(coords, result->GetCellReferences());
        if (IsCyclePresent()) {
            RemoveDependencies(coords, result->GetCellReferences());
            throw logic_error("Cycle detected");
        }

        if (!result->GetCellReferences().empty()) {
            if (newCell.GetDisplayColor() == Cell::DEFAULT_COLOR) {
                newCell.AssignRandomColor();
            }
            int newColor = Cell::DEFAULT_COLOR;
            for (auto &dep : cellDependencies[coords]) {
                if (GetCellColor(dep) != Cell::DEFAULT_COLOR) {
                    newColor = GetCellColor(dep);
                    break;
                }
            }

            if (newColor == Cell::DEFAULT_COLOR) {
                newColor = newCell.GetDisplayColor();
                for (auto &dep : cellDependencies[coords]) {
                    SetCellColor(dep, newColor);
                }
            } else {
                newCell.SetDisplayColor(newColor);
            }
        }
        table->AddCell(newCell);
    } else {
        table->AddCell(StringCell(coords, val));
    }

    UpdateCells(coords);

    return *this;
}

void Sheet::AddDependencies(const Coords &coords, const set<Coords> &deps) {
    for (auto &elem : deps) {
        cellDependencies[coords].insert(elem);
    }
}

void Sheet::RemoveDependencies(const Coords &coords, const set<Coords> &deps) {
    for (auto &dep : deps) {
        cellDependencies[coords].erase(dep);
    }
}

bool Sheet::IsCyclePresent() const {
    map<Coords, DfsStatus> dfsTable;

    for (auto &elem : cellDependencies) {
        dfsTable[elem.first] = DfsStatus::FRESH;
    }

    for (auto &elem : dfsTable) {
        if (elem.second == DfsStatus::FRESH) {
            if (DfsScan(elem.first, dfsTable)) {
                return true;
            }
        }
    }

    return false;
}

bool Sheet::DfsScan(const Coords &coords, map<Coords, DfsStatus> &dfsTable) const {
    dfsTable[coords] = DfsStatus::OPEN;

    // the given cell reference does not have any dependencies
    if (cellDependencies.count(coords) == 0) {
        dfsTable[coords] = DfsStatus::CLOSED;
        return false;
    }

    for (auto &dep : cellDependencies.at(coords)) {
        if (dfsTable[dep] == DfsStatus::FRESH) {
            if (DfsScan(dep, dfsTable)) {
                return true;
            }
        } else if (dfsTable[dep] == DfsStatus::OPEN) {
            return true;
        }
    }

    dfsTable[coords] = DfsStatus::CLOSED;
    return false;
}

string Sheet::GetDisplayValue(const Coords &coords) const {
    return table->GetCellDisplayValue(coords);
}

void Sheet::UpdateCells(const Coords &coords) {
    set<Coords> cellsToBeUpdated;

    for (auto &elem : cellDependencies) {
        if (elem.second.count(coords) != 0) {
            cellsToBeUpdated.insert(elem.first);
        }
    }

    for (auto &elem : cellsToBeUpdated) {
        string expr = table->GetCellOrigValue(elem);
        AddCell(elem, expr);
    }
}

Sheet &Sheet::DeleteCell(const Coords &coords) {
    string origValue = GetOriginalValue(coords);
    table->DelCell(coords);
    cellDependencies.erase(coords);
    try {
        UpdateCells(coords);
    } catch (const invalid_argument &e) {
        AddCell(coords, origValue);
        throw;
    }
    return *this;
}

std::string Sheet::GetOriginalValue(const Coords &coords) const {
    return table->GetCellOrigValue(coords);
}

Table::const_iterator Sheet::GetCellsBeginIterator() const {
    return table->GetCellsBeginIterator();
}

Table::const_iterator Sheet::GetCellsEndIterator() const {
    return table->GetCellsEndIterator();
}

Sheet &Sheet::Clear() {
    table->Clear();
    cellDependencies.clear();
    return *this;
}

double Sheet::GetNumericValue(const Coords &coords) const {
    return table->GetCellNumericValue(coords);
}

int Sheet::GetCellColor(const Coords &coords) const {
    return table->GetCellColor(coords);
}

void Sheet::SetCellColor(const Coords &coords, int newColor) const {
    table->SetCellColor(coords, newColor);
}
