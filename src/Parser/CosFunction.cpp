/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "CosFunction.h"
#include <math.h>

CosFunction::CosFunction(double param) : argument(param) {}

std::unique_ptr<Token> CosFunction::Clone() const {
    return std::unique_ptr<Token>(new CosFunction(*this));
}

double CosFunction::Evaluate() const {
    return cos(argument);
}