/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include "DelCommand.h"

using namespace std;

bool DelCommand::Do(const shared_ptr<vector<string>> &args) {
    if (args->size() == 1) {
        Coords coords = args->operator[](0);
        if (coords.IsValid()) {
            try {
                sheet->DeleteCell(coords);
            } catch (const invalid_argument &e) {
                SetCustomErrorStatus(e.what());
                return true;
            }
            SetOKStatus();
        } else {
            SetWrongCoordsStatus();
        }
    } else {
        SetWrongArgsStatus();
    }

    return true;
}
