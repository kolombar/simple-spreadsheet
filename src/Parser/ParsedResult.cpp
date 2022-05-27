/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "ParsedResult.h"

ParsedResult & ParsedResult::SetResult(double res) {
    result = res;
    return *this;
}

double ParsedResult::GetResult() const {
    return result;
}

ParsedResult & ParsedResult::AddDependency(const Coords &dep) {
    cellReferences.insert(dep);
    return *this;
}

const std::set<Coords> & ParsedResult::GetCellReferences() const {
    return cellReferences;
}