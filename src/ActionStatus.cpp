/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 21.05.2021
 */

#include <string>
#include "ActionStatus.h"

using namespace std;

string ActionStatus::GetAction() const {
    return action;
}

string ActionStatus::GetMessage() const {
    return message;
}

ActionStatus::State ActionStatus::GetState() const {
    return state;
}
