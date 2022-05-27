/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 05.05.2021
 */

#pragma once

#include "Command.h"
#include "File.h"

/**
 * @brief Provides interface from commands that work with files.
 */
class FileCommand : public Command {
public:
    FileCommand(const std::shared_ptr<Sheet> &newSheet,
                const std::shared_ptr<View> &view,
                const std::string &command);
protected:
    typedef std::unique_ptr<File> (*func)(const std::shared_ptr<Sheet> &sheet);

    /**
     * A register with available file formats.
     */
    std::map<std::string, func> registeredFiles;

    /**
     * Creates a register with all available file formats.
     */
    void CreateFileRegister();
};


