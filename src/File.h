/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 03.05.2021
 */

#pragma once

#include <string>
#include <utility>
#include "Sheet.h"

/**
 * @brief Interface for working with files.
 * @details A spreadsheet should be allowed to be saved to a file or loaded from a file.
 */
class File {
public:
    explicit File(const std::shared_ptr<Sheet> &newSheet) : sheet(newSheet) {};

    virtual ~File() = default;

    /**
     * Saves spreadsheet to a file.
     * @param path path to the file
     * @return File
     */
    virtual File & Save (const std::string &path) = 0;

    /**
     * Loads spreadsheet from a file.
     * @param path path to the file
     * @return File
     */
    virtual File & Load (const std::string &path) = 0;

    virtual std::unique_ptr<File> Clone() const = 0;

    /**
     * @brief Exception thrown if the content of a file is not valid.
     */
    class InvalidInputError : public std::exception {
    public:
        const char * what() const noexcept override { return whatMessage.c_str(); }
    private:
        std::string whatMessage = "Input is not valid.";
    };

    /**
     * @brief Exception thrown if the file cannot be opened.
     */
    class FileOpenError : public std::exception {
    public:
        const char * what() const noexcept override { return whatMessage.c_str(); }
    private:
        std::string whatMessage = "Cannot open the file.";
    };

protected:
    std::shared_ptr<Sheet> sheet;
};

