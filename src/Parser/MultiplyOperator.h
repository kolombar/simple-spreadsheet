/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Operator.h"

/**
 * @brief Class representing multiplication.
 */
class MultiplyOperator : public Operator{
public:
    MultiplyOperator() : Operator(OperatorPriority::HIGH) {};

    /**
     * Multiplies the two operands.
     * @return result of the multiplication
     */
    double Evaluate() const override;

    std::unique_ptr<Token> Clone() const override;
};

