/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include <limits>
#include "ShowCommand.h"

using namespace std;

bool ShowCommand::Do(const shared_ptr<vector<string>> &args) {
    if (args->empty()) {
        auto beg = sheet->GetCellsBeginIterator();
        auto end = sheet->GetCellsEndIterator();
        while (beg != end) {
            cout << beg->second->GetCoords() << ": " << beg->second->GetOrigValue() << endl;
            beg++;
        }
        cout << "(press ENTER to continue)";
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        SetOKStatus();
    } else if (args->size() == 1) {
        Coords cellCoords = args->operator[](0);
        if (cellCoords.IsValid()) {
            cout << cellCoords << ": ";
            cout << sheet->GetOriginalValue(cellCoords) << endl;
            cout << "(press ENTER to continue)";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            SetOKStatus();
        } else {
            SetWrongCoordsStatus();
        }
    } else {
        SetWrongArgsStatus();
    }

    return true;
}
