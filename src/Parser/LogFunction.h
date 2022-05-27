/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Variable.h"

/**
 * @brief Class representing a logarithmic function.
 */
class LogFunction : public Variable{
public:
    LogFunction(double param);

    std::unique_ptr<Token> Clone() const override;

    /**
     * Calculates logarithm of the given argument. Throws an exception if the argument is equal to or smaller than zero.
     * @return logarithm of the argument
     */
    double Evaluate() const override;
private:
    double argument;
};
