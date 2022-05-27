/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "DelimitedFile.h"
#include <fstream>
#include "View.h"
#include "Command.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

std::unique_ptr<File> DelimitedFile::Clone() const {
    return unique_ptr<File>(new DelimitedFile(*this));
}

File &DelimitedFile::Save(const std::string &path) {
    auto beg = sheet->GetCellsBeginIterator();
    auto end = sheet->GetCellsEndIterator();

    ofstream f(path);

    if (!f.is_open()) {
        throw FileOpenError();
    }

    f << "rows" << delimiter << View::ROWS << endl;
    f << "cols" << delimiter << View::COLUMNS << endl;

    while (beg != end) {
        if (!beg->second->GetOrigValue().empty()) {
            f << beg->second->GetCoords() << delimiter << beg->second->GetOrigValue() << endl;
        }
        beg++;
    }
    f.flush();
    f.close();
    return *this;
}

File &DelimitedFile::Load(const std::string &path) {
    bool isInputValid = true;
    ifstream f(path);

    if (!f.is_open()) {
        throw FileOpenError();
    }

    map<Coords, string> cellsToAdd;

    int oldNumberOfRows = View::ROWS;
    int oldNumberOfCols = View::COLUMNS;

    try {
        ProcessSpreadsheetSize(f);
    } catch (const InvalidInputError &e) {
        View::ROWS = oldNumberOfRows;
        View::COLUMNS = oldNumberOfCols;
        throw;
    }

    for (string line; getline(f, line);) {
        if (line.empty()) {
            continue;
        }

        auto it = line.begin();

        auto coordsStart = it;

        while (it != line.end() && !IsDelimiter(*it)) {
            it++;
        }

        if (it == line.end()) {
            View::ROWS = oldNumberOfRows;
            View::COLUMNS = oldNumberOfCols;
            throw InvalidInputError();
        }

        Coords coords(string(coordsStart, it));

        it++;

        auto valueStart = it;

        string value(valueStart, line.end());

        while (it != line.end() && !IsDelimiter(*it)) {
            it++;
        }

        if (it != line.end()) {
            isInputValid = false;
            break;
        }

        if (coords.IsValid()) {
            cellsToAdd[coords] = value;
        } else {
            isInputValid = false;
            break;
        }
    }

    if (isInputValid) {
        auto newSheet = std::make_unique<Sheet>();
        try {
            for (auto &elem : cellsToAdd) {
                newSheet->AddCell(elem.first, elem.second);
            }
        } catch (const logic_error &e) {
            View::ROWS = oldNumberOfRows;
            View::COLUMNS = oldNumberOfCols;
            throw InvalidInputError();
        }

        sheet->Clear();
        *sheet = *newSheet;
    } else {
        View::ROWS = oldNumberOfRows;
        View::COLUMNS = oldNumberOfCols;
        throw InvalidInputError();
    }

    f.close();

    return *this;
}

bool DelimitedFile::IsDelimiter(char c) const {
    return c == delimiter;
}

void DelimitedFile::ProcessSpreadsheetSize(std::ifstream &f) const {
    int maxRows = 'Z' - 'A' + 1;
    int parsedNumberOfRows = ProcessDimension(f, "rows");
    if (parsedNumberOfRows > maxRows) {
        throw InvalidInputError();
    }
    View::ROWS = parsedNumberOfRows;
    View::COLUMNS = ProcessDimension(f, "cols");

    if (View::SELECTED_CELL.GetNumericRow() > View::ROWS) {
        View::SELECTED_CELL.SetNumericRow(View::ROWS);
    }

    if (View::SELECTED_CELL.GetNumericCol() > View::COLUMNS) {
        View::SELECTED_CELL.SetNumericCol(View::COLUMNS);
    }
}

int DelimitedFile::ProcessDimension(ifstream &f, const std::string &dimName) const {
    string input;
    getline(f, input);

    auto it = input.begin();
    auto rowStart = it;

    while (it != input.end() && !IsDelimiter(*it)) {
        it++;
    }

    if (it == input.end()) {
        throw InvalidInputError();
    }

    string row(rowStart, it);

    row.erase(remove_if(row.begin(), row.end(), ::isspace), row.end());
    std::transform(row.begin(), row.end(), row.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (row != dimName) {
        throw InvalidInputError();
    }

    string value(++it, input.end());

    for (int i = 0; i < (int) value.size(); i++) {
        if (!isdigit(value[i])) {
            throw InvalidInputError();
        }
    }

    return stoi(value);
}
