/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#include <iostream>
#include <algorithm>
#include "SaveCommand.h"
#include "DelimitedFile.h"

using namespace std;

bool SaveCommand::Do(const shared_ptr<vector<string>> &args) {
    if (args->size() == 1) {
        string path = args->operator[](0);
        unique_ptr<File> file = registeredFiles["tsv"](sheet);
        try {
            file->Save(path);
            SetOKStatus();
        } catch (const File::FileOpenError &e) {
            SetCustomErrorStatus("Cannot open the file.");
        }
    } else if (args->size() == 2) {
        string fileType = args->operator[](0);
        transform(fileType.begin(), fileType.end(), fileType.begin(), ::tolower);
        string path = args->operator[](1);

        if (fileType.empty()) {
            fileType = "tsv";
        }

        if (registeredFiles.count(fileType) == 0) {
            SetCustomErrorStatus("Unknown fileformat.");
            return true;
        }

        unique_ptr<File> file = registeredFiles[fileType](sheet);
        try {
            file->Save(path);
            SetOKStatus();
        } catch (const File::FileOpenError &e) {
            SetCustomErrorStatus("Cannot open the file.");
        }
    } else {
        SetWrongArgsStatus();
    }

    return true;
}
