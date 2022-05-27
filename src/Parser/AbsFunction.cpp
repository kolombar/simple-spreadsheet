/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "AbsFunction.h"
#include <math.h>

AbsFunction::AbsFunction(double param) : argument(param) {}

std::unique_ptr<Token> AbsFunction::Clone() const {
    return std::unique_ptr<Token>(new AbsFunction(*this));
}

double AbsFunction::Evaluate() const {
    return fabs(argument);
}