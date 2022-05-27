/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include <string>
#include <set>
#include "Variable.h"

/**
 * @brief A base class for math operators.
 */
class Operator : public Token {
public:
    enum class OperatorPriority {
        LOW = 0,
        HIGH = 1
    };

    explicit Operator(const OperatorPriority & priority);

    Operator(const Operator & other);

    virtual ~Operator() = default;

    OperatorPriority GetPriority() const;

    /**
     * Sets the left operand.
     * @param lhs left operand
     */
    void SetLeft(const std::unique_ptr<Token> & lhs);

    /**
     * Sets the right operand.
     * @param rhs right operand
     */
    void SetRight(const std::unique_ptr<Token> & rhs);

protected:
    OperatorPriority priority;

    std::unique_ptr<Token> leftOperand;

    std::unique_ptr<Token> rightOperand;
};

