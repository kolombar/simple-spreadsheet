/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Variable.h"

/**
 * @brief Class representing a sinus function.
 */
class SinFunction : public Variable {
public:
    explicit SinFunction(double param);

    std::unique_ptr<Token> Clone() const override;

    /**
     * Calculates the sinus value of the given argument.
     * @return sinus value of the argument
     */
    double Evaluate() const override;
private:
    double argument;
};

