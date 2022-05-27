/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 14.05.2021
 */

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "ExitCommand.h"

using namespace std;

bool ExitCommand::Do(const shared_ptr<vector<string>>& args) {
    if (args->empty()) {
        return false;
    }

    SetWrongArgsStatus();
    return true;
}
