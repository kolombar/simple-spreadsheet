/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.05.2021
 */

#pragma once

#include "File.h"

/**
 * @brief A file-type with a delimiter (such as TSV file or CSV file).
 * @details
 */
class DelimitedFile : public File {
public:
    DelimitedFile(const std::shared_ptr<Sheet> &sheet, char delim) : File(sheet), delimiter(delim) {};

    std::unique_ptr<File> Clone() const override;

    /**
     * Saves spreadsheet to a file specified by the path using the delimiter.
     * @param path path to the file
     * @return DelimitedFile
     */
    File & Save (const std::string &path) override;

    /**
     * Loads spreadsheet from a file specified by the path using the delimiter.
     * @param path path to the file
     * @return DelimitedFile
     */
    File & Load (const std::string &path) override;

private:
    char delimiter;

    /**
     * Checks whether given character is a delimiter of the file.
     * @param c character to be checked
     * @return true if the character is a delimiter
     */
    bool IsDelimiter(char c) const;

    /**
     * Processes spreadsheet's size (i.e. the number of rows and columns) from the given file.
     * @param f stream to read the file from
     */
    void ProcessSpreadsheetSize(std::ifstream &f) const;

    /**
     * Processes either spreadsheet's number of rows or number of columns, i.e. extracts this value from a file.
     * @param f stream to read the file from
     * @param dimName name of the dimension to be extracted
     * @return value of the extracted dimension (i.e. either the number of rows or columns)
     */
    int ProcessDimension(std::ifstream &f, const std::string &dimName) const;
};
