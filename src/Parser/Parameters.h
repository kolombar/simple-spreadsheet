/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 28.04.2021
 */

#pragma once

#include <vector>
#include <string>
#include "../Table.h"

/**
 * @brief Parameters of function tokens.
 * @details They can be either numbers or more complex expressions containing other functions, cell references etc. All parameters have to be separated by a comma. After getting all parameters they are parsed the same way as any other expression (i.e. using MathParser)
 */
class Parameters {
public:
    Parameters() = default;

    explicit Parameters(std::string parameters, const std::shared_ptr<Table>& table);

    /**
     * Returns a set of all cell references found in the parameters.
     * @return set of cell references
     */
    std::set<Coords> GetCellReferences() const;

    /**
     * Gets a parameter on the given position.
     * @param pos position of the parameter
     * @return parameter on the given position
     */
    double GetParam(int pos) const;
private:
    std::vector<double> params;

    std::set<Coords> cellReferences;
};
