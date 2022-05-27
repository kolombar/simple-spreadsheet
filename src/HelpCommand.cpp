/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include <limits>
#include "HelpCommand.h"

using namespace std;

HelpCommand::HelpCommand(const std::shared_ptr<Sheet> &sheet, const std::shared_ptr<View> &view) : Command(sheet, view,
                                                                                                           "Help") {
    FillHelpMap();
}

bool HelpCommand::Do(const shared_ptr<vector<string>> &args) {
    if (args->empty()) {
        PrintHelpTable();
        cout << "(press ENTER to continue)";
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        SetOKStatus();
    } else {
        SetWrongArgsStatus();
    }

    return true;
}

void HelpCommand::FillHelpMap() {
    helpMap["SET \"<cell>\" \"<expr>\""] = "sets cell's value to the given expression";
    helpMap["DEL \"<cell>\""] = "deletes cell's value";
    helpMap["SHOW"] = "prints values of all cells (math expressions are not evaluated)";
    helpMap["SHOW \"<cell>\""] = "prints value of the given cell (math expressions are not evaluated)";
    helpMap["PRINT"] = "prints values of all cells (math expressions are evaluated)";
    helpMap["PRINT \"<cell>\""] = "prints value of the given cell (math expressions are evaluated)";
    helpMap["SAVE \"<fileformat>\" \"<filepath>\""] = "saves current spreadsheet to the specified file (supported formats are TSV and CSV, TSV is the default)";
    helpMap["LOAD \"<fileformat>\" \"<filepath>\""] = "loads spreadsheet from the specified file (supported formats are TSV and CSV, TSV is the default)";
    helpMap["EDIT"] = "switches to interactive mode";
    helpMap["EXIT"] = "exits the program";
}

pair<int, int> HelpCommand::GetHelpDimensions() const {
    int maxCommand = 0;
    int maxDescription = 0;
    for (const auto &elem : helpMap) {
        int commandSize = (int) elem.first.size();
        int descriptionSize = (int) elem.second.size();
        if (commandSize > maxCommand) {
            maxCommand = commandSize;
        }

        if (descriptionSize > maxDescription) {
            maxDescription = descriptionSize;
        }
    }

    return {maxCommand, maxDescription};
}

void HelpCommand::PrintHelpTable() const {
    pair<int, int> tableDimensions = GetHelpDimensions();

    int firstColSize = tableDimensions.first + 4;
    int secondColSize = tableDimensions.second + 4;

    int rowsToPrint = ((int) helpMap.size() + 1) * 2 + 1;
    int colsToPrint = 2;

    bool printUnderlines = true;

    auto it = helpMap.begin();
    int rowsCnt = 0;
    bool isHeaderPrinted = false;

    for (int row = 1; row <= rowsToPrint; row++) {
        if (!printUnderlines) {
            rowsCnt++;
        }

        if (rowsCnt == 1 && !isHeaderPrinted) {
            PrintHeader(firstColSize, secondColSize);
            isHeaderPrinted = true;
        } else {
            for (int col = 1; col <= colsToPrint; col++) {
                if (printUnderlines) {
                    if (col == 1) {
                        cout << "\u001b[38;5;" << HELP_COLOR << ";1m";
                        cout << "+";
                        cout << "\033[0m";
                        PrintUnderline(firstColSize);
                    } else {
                        PrintUnderline(secondColSize);
                    }
                } else {
                    if (col == 1) {
                        string command = it->first;
                        cout << "\u001b[38;5;" << HELP_COLOR << ";1m";
                        cout << "|";
                        cout << "\033[0m";
                        PrintHelpCell(firstColSize - 1, command);
                    } else {
                        string description = it->second;
                        PrintHelpCell(secondColSize - 1, description);
                    }
                }
            }
            if (!printUnderlines) {
                it++;
            }
        }

        printUnderlines = !printUnderlines;
        cout << endl;
    }
}

void HelpCommand::PrintHelpCell(int spacesToPrint, const std::string &text) const {
    int printSize = (spacesToPrint - (int)text.size() - 1);
    cout << " " << text;
    spacesToPrint -= (int) text.size();
    spacesToPrint--;
    for (int i = 0; i < printSize; i++) {
        cout << " ";
    }
    spacesToPrint -= printSize;

    while (spacesToPrint) {
        cout << " ";
        spacesToPrint--;
    }

    cout << "\u001b[38;5;" << HELP_COLOR << ";1m";
    cout << "|";
    cout << "\033[0m";
}

void HelpCommand::PrintUnderline(int underlinesToPrint) const {
    cout << "\u001b[38;5;" << HELP_COLOR << ";1m";
    while (underlinesToPrint) {
        if (underlinesToPrint == 1) {
            cout << "+";
        } else {
            cout << "-";
        }

        underlinesToPrint--;
    }

    cout << "\033[0m";
}

void HelpCommand::PrintHeader(int firstColSize, int secondColSize) const {
    int colsToPrint = 2;
    vector<string> headers = {"COMMAND", "DESCRIPTION"};
    vector<int> sizes = {firstColSize - 1, secondColSize - 1};
    cout << "\u001b[38;5;" << HELP_COLOR << ";1m";

    cout << "|";
    for (int col = 0; col < colsToPrint; col++) {
        string text = headers[col];
        int spacesToPrint = sizes[col];
        int printSize = (spacesToPrint - (int)text.size() - 1);
        cout << " " << text;
        spacesToPrint -= (int) text.size();
        spacesToPrint--;
        for (int i = 0; i < printSize; i++) {
            cout << " ";
        }
        spacesToPrint -= printSize;

        while (spacesToPrint) {
            cout << " ";
            spacesToPrint--;
        }
        cout << "|";
    }

    cout << "\u001b[38;5;" << HELP_COLOR << ";1m";
}
