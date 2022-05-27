/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Operator.h"

/**
 * @brief Class representing a plus operator.
 */
class PlusOperator : public Operator{
public:
    PlusOperator() : Operator(OperatorPriority::LOW) {};

    /**
     * Sums the two operands.
     * @return sum of the operands
     */
    double Evaluate() const override;

    std::unique_ptr<Token> Clone() const override;
};

