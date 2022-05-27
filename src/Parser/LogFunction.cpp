/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "LogFunction.h"
#include <math.h>

using namespace std;

LogFunction::LogFunction(double param) : argument(param) {}

unique_ptr<Token> LogFunction::Clone() const {
    return unique_ptr<Token>(new LogFunction(*this));
}

double LogFunction::Evaluate() const {
    return log(argument);
}