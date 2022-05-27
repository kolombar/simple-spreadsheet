/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include <string>
#include "Variable.h"

/**
 * @brief Class representing a numeric token, i.e. a token with (mainly) numeric value.
 */
class NumberToken : public Variable {
public:
    explicit NumberToken(std::string &expr) : Variable(expr), value(0) {};

    explicit NumberToken(const double val) : Variable(), value(val) {};

    std::unique_ptr<Token> Clone() const override;

    /**
     * Gets the numeric value of the token.
     * @return the numeric value
     */
    double Evaluate() const override;
private:
    double value;
};

