/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <memory>
#include <vector>
#include "Sheet.h"
#include "View.h"
#include "File.h"
#include "Command.h"

/**
 * @brief Runs the spreadsheet and process input commands.
 * @details This class takes care of the interaction between user and spreadsheet. It sets up the spreadsheet, either by loading it from a file or by manually providing spreadsheet dimensions. Then it processes individual commands provided by the user.
 */
class Application {
public:
    Application() : sheet(std::make_shared<Sheet>()), view(new View(sheet)) {};

    /**
     * Starts the spreadsheet.
     * @return Application
     */
    Application & Run();

private:
    std::shared_ptr<Sheet> sheet;

    std::shared_ptr<View> view;

    std::map<std::string, std::shared_ptr<Command>> commandsRegister;

    /**
     * Creates a register of all available commands.
     * @return Application
     */
    Application & CreateCommandsRegister();

    /**
     * Processes commands from the user.
     */
    void ProcessAction();

    /**
     * Processes input provided by the user. It parses the input in command and correspoding arguments.
     * @param input input from the user
     * @param command parsed command
     * @param args parsed arguments
     */
    static void ProcessInput(const std::string &input, std::string &command, std::shared_ptr<std::vector<std::string>> & args);

    /**
     * Processes number of rows provided manually by the user.
     * @param input user input
     */
    static void ProcessNumberOfRows(std::string &input);

    /**
     * Processes number of coluns provided manually by the user.
     * @param input user input
     */
    static void ProcessNumberOfColumns(std::string &input);

    /**
     * Displays the spreadsheet.
     */
    void DisplayView() const;

    /**
     * Processes user input regarding loading spreadsheet from a file.
     * @param input user input
     * @return true if the provided input is valid
     */
    static bool ProcessLoadOption(std::string &input);

    /**
     * Enables to set spreadsheet configuration manually.
     */
    void SetConfManually();

    /**
     * Enables to load spreadsheet from a file.
     */
    void SetConfFromFile();
};
