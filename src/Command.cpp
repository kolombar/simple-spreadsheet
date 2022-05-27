/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <algorithm>
#include <iostream>
#include "Command.h"

using namespace std;

void Command::SetOKStatus() {
    view->SetCommandState({commandStatusName, ActionStatus::State::OK, ""});
}

void Command::SetWrongArgsStatus() {
    view->SetCommandState({commandStatusName, ActionStatus::State::ERROR, "Wrong number of args."});
}

void Command::SetWrongCoordsStatus() {
    view->SetCommandState({commandStatusName, ActionStatus::State::ERROR, "Wrong coordinates."});
}

void Command::SetCustomErrorStatus(const std::string &message) {
    view->SetCommandState({commandStatusName, ActionStatus::State::ERROR, message});
}