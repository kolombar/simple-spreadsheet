/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include "Operator.h"
#include <memory>

/**
 * @brief Class representing division operator.
 */
class DivideOperator : public Operator {
public:
    DivideOperator() : Operator(OperatorPriority::HIGH) {};

    std::unique_ptr<Token> Clone() const override;

    /**
     * Divides left operand by the right operand.
     * @return result of the division
     */
    double Evaluate () const override;
};

