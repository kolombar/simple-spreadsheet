/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include "SetCommand.h"

using namespace std;

bool SetCommand::Do(const shared_ptr<vector<string>> &args) {
    if (args->size() == 2) {
        Coords coords = args->operator[](0);
        string origValue = sheet->GetOriginalValue(coords);
        if (coords.IsValid()) {
            try {
                sheet->AddCell(coords, args->operator[](1));
                SetOKStatus();
            } catch (const invalid_argument &i) {
                sheet->AddCell(coords, origValue);
                SetCustomErrorStatus(i.what());
            } catch (const logic_error &e) {
                SetCustomErrorStatus("Cycle detected.");
            }
        } else {
            SetWrongCoordsStatus();
        }
    } else {
        SetWrongArgsStatus();
    }

    return true;
}
