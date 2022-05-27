/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 14.05.2021
 */

#include <iostream>
#include <limits>
#include "EditCommand.h"
#include "SetCommand.h"
#include "DelCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"

using namespace std;

EditCommand::EditCommand(const std::shared_ptr<Sheet> &newSheet, const std::shared_ptr<View> &view) : Command(newSheet,
                                                                                                              view,
                                                                                                              "Interactive mode") {
    controls = KeyboardControls{array<char, 9>{'w', 'd', 's', 'a', '\n', 'q', 'r', 'k', 'l'}};
}

bool EditCommand::Do(const std::shared_ptr<std::vector<std::string>> &args) {
    if (args->empty()) {
        SetOKStatus();
        Print();
        interactiveBuffer.Start();
        bool interact = true;
        while (interact) {
            KeyboardDirection direction = interactiveBuffer.Retrieve(controls);
            int row = View::SELECTED_CELL.GetNumericRow();
            int col = View::SELECTED_CELL.GetNumericCol();

            switch (direction) {
                case KeyboardDirection::UP:
                    if (row > 1) {
                        View::SELECTED_CELL.SetNumericRow(row - 1);
                    }
                    break;
                case KeyboardDirection::DOWN:
                    if (row < View::ROWS) {
                        View::SELECTED_CELL.SetNumericRow(row + 1);
                    }
                    break;
                case KeyboardDirection::LEFT:
                    if (col > 1) {
                        View::SELECTED_CELL.SetNumericCol(col - 1);
                    }
                    break;
                case KeyboardDirection::RIGHT:
                    if (col < View::COLUMNS) {
                        View::SELECTED_CELL.SetNumericCol(col + 1);
                    }
                    break;
                case KeyboardDirection::EDIT:
                    interactiveBuffer.Stop();
                    ProcessCellValue();
                    interactiveBuffer.Start();
                    break;
                case KeyboardDirection::NONE:
                    continue;
                case KeyboardDirection::QUIT:
                    interact = false;
                    break;
                case KeyboardDirection::DELETE:
                    DeleteValue();
                    break;
                case KeyboardDirection::SAVE:
                    interactiveBuffer.Stop();
                    SaveToFile();
                    interactiveBuffer.Start();
                    break;
                case KeyboardDirection::LOAD:
                    interactiveBuffer.Stop();
                    LoadFromFile();
                    interactiveBuffer.Start();
                    break;
            }
            Print();
        }
        interactiveBuffer.Stop();

    } else {
        SetWrongArgsStatus();
    }

    return true;
}

void EditCommand::ProcessCellValue() {
    cout << "ENTER VALUE:" << endl;
    string input;
    getline(cin, input);
    SetCommand(sheet, view).Do(make_shared<vector<string>>(vector<string>{View::SELECTED_CELL.ToString(), input}));
}

void EditCommand::Print() const {
    string expression;
    string originalValue = sheet->GetOriginalValue(View::SELECTED_CELL);
    string displayValue = sheet->GetDisplayValue(View::SELECTED_CELL);

    if (originalValue != displayValue) {
        expression = originalValue;
    }

    system("clear");
    cout << endl;
    cout << "You are in INTERACTIVE mode." << endl;
    cout << endl << "\u001b[4m" << "HELP" << "\033[0m" << endl << endl;
    cout
            << "w - move up, a - move left, s - move down, d - move right, r - delete value, k - save to file, l - load from file, q - quit"
            << endl << endl;
    view->PrintStatusTable();
    cout << endl;
    cout << "\u001b[4m" << "CURRENT CELL" << "\033[0m" << endl;
    cout << "    " << "expression: " << expression << endl;
    cout << "    " << "value: " << displayValue << endl << endl;
    view->PrintTable(true);
}

void EditCommand::DeleteValue() {
    DelCommand(sheet, view).Do(make_shared<vector<string>>(vector<string>{View::SELECTED_CELL.ToString()}));
}

void EditCommand::SaveToFile() const {
    cout << "ENTER FILE TYPE (TSV - default, CSV):" << endl;
    string fileType;
    getline(cin, fileType);
    cout << "ENTER PATH TO FILE:" << endl;
    string path;
    getline(cin, path);
    SaveCommand(sheet, view).Do(make_shared<vector<string>>(vector<string>{fileType, path}));
}

void EditCommand::LoadFromFile() {
    cout << "ENTER FILE TYPE (TSV - default, CSV):" << endl;
    string fileType;
    getline(cin, fileType);
    cout << "ENTER PATH TO FILE:" << endl;
    string path;
    getline(cin, path);
    LoadCommand(sheet, view).Do(make_shared<vector<string>>(vector<string>{fileType, path}));
}
