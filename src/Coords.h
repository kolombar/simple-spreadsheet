/**
* @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
* @date 5/27/21
*/

#pragma once

/**
 * @brief A class representing cell coordinates.
 * @details Coordinates consist of a letter and a number. Letter represents row and number stands for column. Coordinates are valid only if they are in this form and if the provided row and column are in the range of current spreadsheet. When creating a new instance, every coordinates are normalized, i.e. spaces are removed and letters are cast to upppercase.
 */
class Coords {
public:
    Coords(const std::string &coords);

    Coords(const Coords &c);

    Coords(int row, int col);

    /**
     * Checks whether coordinates are valid, i.e. row and columns are within the range of current spredsheet.
     * @return true if coordinates are valid
     */
    bool IsValid() const;

    bool operator < (const Coords &rhs) const;

    bool operator == (const Coords &rhs) const;

    friend std::ostream & operator << (std::ostream &os, const Coords & coords) {
        os << coords.coords;
        return os;
    }

    int GetNumericRow() const;

    void SetNumericRow(int row);

    int GetNumericCol() const;

    void SetNumericCol(int col);

    /**
     * Returns coordinates in string form.
     * @return coordinates as a string
     */
    std::string ToString() const;

    std::string GetRow() const;

    std::string GetCol() const;

private:
    std::string coords;

    std::string letterPart;

    std::string numericPart;

    int numericRow;

    int numericCol;

    /**
     * Extracts letter representing row and assigns it to @var letterPart.
     */
    void ExtractLetterPart();

    /**
     * Extracts number representing column and assigns it to @var numericPart.
     */
    void ExtractNumericPart();

    /**
     * Normalizes coordinates, i.e. removes white-spaces and casts letters to uppercase.
     */
    void PrepareCoords();

    /**
     * Creates a coordinates string from numeric representation of row and column.
     */
    void SetCoordsFromNumeric();
};



