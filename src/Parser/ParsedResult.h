/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include <string>
#include <set>
#include "../Coords.h"

/**
 * @brief Class representing the result of parsing a mathematical expression.
 * @details The result stores the numeric value of the parsing as well as all found cell references.
 */
class ParsedResult {
public:
    ParsedResult & SetResult(double res);

    double GetResult() const;

    /**
     * Returns all cell references found during parsing.
     * @return set of cell references (represented by their coordinates)
     */
    const std::set<Coords> & GetCellReferences() const;

    ParsedResult & AddDependency(const Coords & dep);

private:
    double result;

    std::set<Coords> cellReferences;
};

