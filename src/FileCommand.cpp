/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 05.05.2021
 */

#include "FileCommand.h"
#include "DelimitedFile.h"

#include <utility>

using namespace std;

FileCommand::FileCommand(const std::shared_ptr<Sheet> &newSheet, const std::shared_ptr<View> &view,
                         const std::string &command) : Command(newSheet,
                                                               view, command) {
    CreateFileRegister();
}

void FileCommand::CreateFileRegister() {
    registeredFiles["tsv"] = [](const std::shared_ptr<Sheet> &sheet) { return DelimitedFile(sheet, '\t').Clone(); };
    registeredFiles["csv"] = [](const std::shared_ptr<Sheet> &sheet) { return DelimitedFile(sheet, ',').Clone(); };
}
