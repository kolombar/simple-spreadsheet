/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 02.05.2021
 */

#include "Application.h"
#include "SetCommand.h"
#include "DelCommand.h"
#include "ShowCommand.h"
#include "HelpCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"
#include "PrintCommand.h"
#include "View.h"
#include "ExitCommand.h"
#include "EditCommand.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

Application &Application::Run() {
    CreateCommandsRegister();
    ProcessAction();
    return *this;
}

Application &Application::CreateCommandsRegister() {
    commandsRegister["SET"] = unique_ptr<Command>(new SetCommand(sheet, view));
    commandsRegister["DEL"] = unique_ptr<Command>(new DelCommand(sheet, view));
    commandsRegister["SHOW"] = unique_ptr<Command>(new ShowCommand(sheet, view));
    commandsRegister["HELP"] = unique_ptr<Command>(new HelpCommand(sheet, view));
    commandsRegister["SAVE"] = unique_ptr<Command>(new SaveCommand(sheet, view));
    commandsRegister["LOAD"] = unique_ptr<Command>(new LoadCommand(sheet, view));
    commandsRegister["PRINT"] = unique_ptr<Command>(new PrintCommand(sheet, view));
    commandsRegister["EXIT"] = unique_ptr<Command>(new ExitCommand(sheet, view));
    commandsRegister["EDIT"] = unique_ptr<Command>(new EditCommand(sheet, view));

    return *this;
}

void Application::ProcessAction() {
    string input;

    system("clear");
    cout << endl << "\u001b[4m" << "SPREADSHEET SETUP" << "\033[0m" << endl;
    cout << endl << "Do you want to load spreadsheet from file? (y/n)" << endl;
    getline(cin, input);
    bool shouldLoadFromFile = ProcessLoadOption(input);

    if (shouldLoadFromFile) {
        SetConfFromFile();
    } else {
        SetConfManually();
    }

    cout << endl << "Setup finished. Press ENTER to continue to spreadsheet.";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

    view->SetCommandState({});

    DisplayView();

    cout << "ENTER COMMAND:" << endl;
    while (getline(cin, input)) {
        string command;
        shared_ptr<vector<string>> args = make_shared<vector<string>>();
        ProcessInput(input, command, args);

        if (commandsRegister.count(command) != 0) {
            bool shouldContinue;
            try {
               shouldContinue  = commandsRegister[command]->Do(args);
            } catch (...) {
                cout << "Uncaught fatal error has occured. Aborting." << endl;
                shouldContinue = false;
            }


            if (!shouldContinue) {
                return;
            }
        } else {
            view->SetCommandState({"Enter command", ActionStatus::State::ERROR, "Unknown command"});
        }

        DisplayView();
        cout << "ENTER COMMAND:" << endl;
    }
}

void Application::ProcessInput(const string &input, string &command, shared_ptr<vector<string>> &args) {
    stringstream ss(input);
    string buffer;
    bool isCommandParsed = false;
    bool isBetweenArgs = false;

    while (getline(ss, buffer, '"')) {

        if (!isCommandParsed) {
            isCommandParsed = true;
            buffer.erase(remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
            command = buffer;
            continue;
        }

        if (!isBetweenArgs) {
            args->push_back(buffer);
        }

        isBetweenArgs = !isBetweenArgs;
    }

    // normalize (command to uppercase)
    transform(command.begin(), command.end(), command.begin(), ::toupper);
}

void Application::ProcessNumberOfRows(std::string &input) {
    if (input.empty()) {
        View::ROWS = View::DEFAULT_TABLE_SIZE;
        cout << "Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
        return;
    }

    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    for (auto it = input.begin(); it != input.end(); it++) {
        if (!isdigit(*it)) {
            View::ROWS = View::DEFAULT_TABLE_SIZE;
            cout << "Invalid value. Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
            return;
        }
    }

    int maxRows = 'Z' - 'A' + 1;
    int rows = stoi(input);
    if (rows < 1) {
        View::ROWS = View::DEFAULT_TABLE_SIZE;
        cout << "Invalid value. Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
        return;
    } else if (rows > maxRows) {
        View::ROWS = View::DEFAULT_TABLE_SIZE;
        cout << "Value too large (max is " << maxRows << "). Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
        return;
    } else {
        View::ROWS = rows;
    }
}

void Application::ProcessNumberOfColumns(std::string &input) {
    if (input.empty()) {
        View::COLUMNS = View::DEFAULT_TABLE_SIZE;
        cout << "Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
        return;
    }

    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    for (auto it = input.begin(); it != input.end(); it++) {
        if (!isdigit(*it)) {
            View::COLUMNS = View::DEFAULT_TABLE_SIZE;
            cout << "Invalid value. Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
            return;
        }
    }

    int cols = stoi(input);
    if (cols < 1) {
        View::COLUMNS = View::DEFAULT_TABLE_SIZE;
        cout << "Invalid value. Setting default: " << View::DEFAULT_TABLE_SIZE << endl;
    } else {
        View::COLUMNS = cols;
    }
}

void Application::DisplayView() const {
    system("clear");
    cout << endl;
    cout << "You are in COMMAND mode." << endl << endl;
    cout << "Type HELP to see available commands and their description." << endl << endl;

    view->PrintStatusTable();
    cout << endl << endl << endl;

    view->PrintTable();
}

bool Application::ProcessLoadOption(std::string &input) {
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

    if (input == "y" || input == "Y") {
        return true;
    } else if (input == "n" || input == "N") {
        return false;
    } else {
        cout << "Unknown response. Default is 'n'." << endl;
        return false;
    }
}

void Application::SetConfManually() {
    string input;
    cout << endl << "Set spreadsheet configuration manually." << endl << endl;
    cout << endl << "Number of rows:" << endl;
    getline(cin, input);
    ProcessNumberOfRows(input);

    cout << endl << "Number of columns:" << endl;
    getline(cin, input);
    ProcessNumberOfColumns(input);
}

void Application::SetConfFromFile() {
    string input;
    vector<string> loadArguments;
    cout << endl << "Enter file type (tsv - default, csv):" << endl;
    getline(cin, input);
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    loadArguments.push_back(input);
    cout << endl << "Enter file path:" << endl;
    getline(cin, input);
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    loadArguments.push_back(input);
    commandsRegister["LOAD"]->Do(make_shared<vector<string>>(loadArguments));

    if (view->GetCommandState().GetState() == ActionStatus::State::ERROR) {
        cout << endl << "Load not succesful:" << endl << view->GetCommandState().GetMessage() << endl;
        cout << endl << "Retry load? (y/n)" << endl;
        getline(cin, input);
        if (ProcessLoadOption(input)) {
            SetConfFromFile();
        } else {
            SetConfManually();
        }
    }
}