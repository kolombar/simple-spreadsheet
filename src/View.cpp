/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <memory>
#include "View.h"

using namespace std;

int View::ROWS = 0;

int View::COLUMNS = 0;

Coords View::SELECTED_CELL = Coords(1, 1);

View &View::PrintTable(bool highlightSelectedCell) {
    if (!highlightSelectedCell) {
        cellHighlightColor = 37;
    } else {
        cellHighlightColor = 31;
    }
    int rowsToPrint = ROWS * 2 + 1;
    char letterToPrint = 'A' - 1;
    int selectedRowPrint = SELECTED_CELL.GetNumericRow() * 2;
    int selectedColPrint = SELECTED_CELL.GetNumericCol();
    bool printUnderlines = false;
    for (int row = 0; row < rowsToPrint; row++) {
        for (int col = 0; col <= COLUMNS; col++) {
            int spacesToPrint = (int) to_string(col).size() + CELL_SIZE * 2;
            if (printUnderlines) {
                if (((selectedRowPrint - 1) == row || (selectedRowPrint + 1) == row)) {
                    PrintColoredUnderline(spacesToPrint + 1);
                } else {
                    PrintUnderline(spacesToPrint + 1, col);
                }
                continue;
            }
            Coords coords = string(1, letterToPrint).append(to_string(col));
            string displayValue = sheet->GetDisplayValue(coords);
            int displayColor = sheet->GetCellColor(coords);

            if (col > 0 && row > 0 && !displayValue.empty()) {
                FillCell(spacesToPrint, displayValue, displayColor);
                PrintVLine(selectedColPrint, col);
                continue;
            }

            if (col == 0 && row != 0) {
                PrintRowIndex(letterToPrint);
                PrintVLine(selectedColPrint, col);
                continue;
            }

            if (col > 0 && row == 0) {
                PrintColIndex(col);
                PrintVLine(selectedColPrint, col);
                continue;
            }

            while (spacesToPrint) {
                cout << " ";
                spacesToPrint--;
            }
            PrintVLine(selectedColPrint, col);
        }
        printUnderlines = !printUnderlines;
        if (!printUnderlines) {
            letterToPrint++;
        }
        cout << endl;
    }

    cout << endl;
    return *this;
}

void View::PrintUnderline(int underlinesToPrint, int col) const {
    while (underlinesToPrint) {
        if (underlinesToPrint == 1 &&
            (col == SELECTED_CELL.GetNumericCol() || col + 1 == SELECTED_CELL.GetNumericCol())) {
            cout << "\u001b[" << cellHighlightColor << ";1m" << "+" << "\033[0m";
        } else if (underlinesToPrint == 1) {
            cout << "+";
        } else {
            cout << "-";
        }

        underlinesToPrint--;
    }
}

void View::PrintColoredUnderline(int underlinesToPrint) const {
    while (underlinesToPrint) {
        if (underlinesToPrint == 1) {
            cout << "\u001b[" << cellHighlightColor << ";1m" << "+" << "\033[0m";
        } else {
            cout << "\u001b[" << cellHighlightColor << ";1m" << "-" << "\033[0m";
        }

        underlinesToPrint--;
    }
}

void View::FillCell(int spacesToPrint, string displayValue, int displayColor) const {
    bool isTrimmed = false;
    if ((int)displayValue.size() > OUTPUT_VIEW_SIZE) {
        isTrimmed = true;
        displayValue = displayValue.substr(0, OUTPUT_VIEW_SIZE);
    }

    int whiteSpaces = ceil((spacesToPrint - (int) displayValue.size()) / 2);
    int printedTotal = 0;
    for (int j = 0; j < whiteSpaces; j++) {
        cout << " ";
        printedTotal++;
    }

    cout << "\u001b[38;5;" << displayColor << ";1m" << displayValue << "\033[0m";
    printedTotal += (int) displayValue.size();
    int cntPrintedDots = 0;
    for (int j = 0; j < whiteSpaces; j++) {
        if (isTrimmed && cntPrintedDots < 3) {
            cout << "\u001b[38;5;" << displayColor << ";1m" << "." << "\033[0m";
            cntPrintedDots++;
        } else {
            cout << " ";
        }
        printedTotal++;
    }
    if (printedTotal < spacesToPrint) {
        for (int j = 0; j < spacesToPrint - printedTotal; j++) {
            cout << " ";
        }
    }
}

void View::PrintRowIndex(char letterToPrint) const {
    for (int j = 0; j < CELL_SIZE; j++) {
        cout << " ";
    }

    if (letterToPrint == SELECTED_CELL.GetRow()[0]) {
        cout << "\u001b[" << cellHighlightColor << ";1m" << letterToPrint << "\033[0m";
    } else {
        cout << letterToPrint;
    }

    for (int j = 0; j < CELL_SIZE; j++) {
        cout << " ";
    }

}

void View::PrintColIndex(int idx) const {
    for (int j = 0; j < CELL_SIZE; j++) {
        cout << " ";
    }

    if (idx == SELECTED_CELL.GetNumericCol()) {
        cout << "\u001b[" << cellHighlightColor << ";1m" << idx << "\033[0m";
    } else {
        cout << idx;
    }

    for (int j = 0; j < CELL_SIZE; j++) {
        cout << " ";
    }

}

void View::PrintVLine(int selectedColPrint = -1, int col = 0) const {
    if (col == selectedColPrint || col == selectedColPrint - 1) {
        cout << "\u001b[" << cellHighlightColor << ";1m" << "|" << "\033[0m";
    } else {
        cout << "|";
    }
}

View &View::SetCommandState(const ActionStatus &newState) {
    state = newState;
    return *this;
}

ActionStatus View::GetCommandState() const {
    return state;
}

const View &View::PrintStatusTable() const {
    int rowsToPrint = 5;
    int colsToPrint = 3;
    int rowsCnt = 0;
    bool printUnderlines = true;
    cout << "\u001b[4m" << "LAST ACTION STATUS BAR" << "\033[0m" << endl << endl;
    for (int row = 1; row <= rowsToPrint; row++) {
        if (!printUnderlines) {
            rowsCnt++;
        }
        for (int col = 1; col <= colsToPrint; col++) {
            int spacesToPrint = 10 + CELL_SIZE * 2;
            if (printUnderlines) {
                if (col == 1) {
                    cout << "+";
                }
                PrintUnderline(spacesToPrint + 1, -1);
                continue;
            }

            if (col == 1 && rowsCnt == 1) {
                PrintVLine();
                PrintStateCell(spacesToPrint, "ACTION");
                PrintVLine();
                continue;
            }

            if (col == 2 && rowsCnt == 1) {
                PrintStateCell(spacesToPrint, "STATUS");
                PrintVLine();
                continue;
            }

            if (col == 3 && rowsCnt == 1) {
                PrintStateCell(spacesToPrint, "MESSAGE");
                PrintVLine();
                continue;
            }

            if (col == 1 && rowsCnt == 2) {
                PrintVLine();
                PrintStateCell(spacesToPrint, state.GetAction());
                PrintVLine();
                continue;
            }

            if (col == 2 && rowsCnt == 2) {
                PrintCommandStateCell(spacesToPrint);
                PrintVLine();
                continue;
            }

            if (col == 3 && rowsCnt == 2) {
                PrintStateCell(spacesToPrint, state.GetMessage());
                PrintVLine();
                continue;
            }

            while (spacesToPrint) {
                cout << " ";
                spacesToPrint--;
            }
            PrintVLine(-10, col);
        }
        printUnderlines = !printUnderlines;
        cout << endl;
    }

    return *this;
}

void View::PrintStateCell(int spacesToPrint, const std::string &text) const {
    int printSize = (spacesToPrint - (int) text.size()) / 2;
    for (int i = 0; i < printSize; i++) {
        cout << " ";
    }
    spacesToPrint -= printSize;
    cout << text;
    spacesToPrint -= (int) text.size();
    for (int i = 0; i < printSize; i++) {
        cout << " ";
    }
    spacesToPrint -= printSize;

    while (spacesToPrint) {
        cout << " ";
        spacesToPrint--;
    }
}

void View::PrintCommandStateCell(int spacesToPrint) const {
    int printSize = (spacesToPrint - 1) / 2;
    for (int i = 0; i < printSize; i++) {
        cout << " ";
    }
    spacesToPrint -= printSize;

    if (!state.GetAction().empty()) {
        if (state.GetState() == ActionStatus::State::OK) {
            cout << "\u001b[38;5;40m" << "\u2713" << "\033[0m";
        } else {
            cout << "\u001b[38;5;160m" << "X" << "\033[0m";
        }
    } else {
        cout << " ";
    }

    spacesToPrint -= 1;
    for (int i = 0; i < printSize; i++) {
        cout << " ";
    }
    spacesToPrint -= printSize;

    while (spacesToPrint) {
        cout << " ";
        spacesToPrint--;
    }
}