/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "SinFunction.h"
#include "MathParser.h"
#include <math.h>

SinFunction::SinFunction(double param) : argument(param) {}

std::unique_ptr<Token> SinFunction::Clone() const {
    return std::unique_ptr<Token>(new SinFunction(*this));
}

double SinFunction::Evaluate() const {
    return sin(argument);
}
