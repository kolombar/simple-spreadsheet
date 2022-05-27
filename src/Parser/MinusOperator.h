/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Operator.h"

/**
 * @brief Class representing a minus operator.
 */
class MinusOperator : public Operator{
public:

    MinusOperator() : Operator(OperatorPriority::LOW) {};

    /**
     * Subtracts the right operand from the left operand.
     * @return result of the subtraction
     */
    double Evaluate() const override;

    std::unique_ptr<Token> Clone() const override;

};

