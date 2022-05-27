/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Variable.h"

/**
 * @brief Class representing a cosinus function.
 */
class CosFunction : public Variable {
public:
    CosFunction(double param);

    std::unique_ptr<Token> Clone() const override;

    /**
     * Calculates cosinus value for the given argument.
     * @return cosinus of the argument
     */
    double Evaluate() const override;
private:
    double argument;
};

