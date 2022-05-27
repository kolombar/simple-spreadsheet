/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include <string>
#include "Variable.h"

/**
 * @brief Class representing an absolute value function.
 */
class AbsFunction : public Variable{
public:
    AbsFunction(double param);

    std::unique_ptr<Token> Clone() const override;

    /**
     * Calculates absolute value of the given argument.
     * @return absolute value of the argument
     */
    double Evaluate() const override;
private:
    double argument;
};

