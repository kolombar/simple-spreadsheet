/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "Operator.h"

Operator::Operator(const OperatorPriority & prior) : priority(prior) {}

Operator::Operator(const Operator &other) : priority(other.priority), leftOperand(other.leftOperand->Clone()), rightOperand(other.rightOperand->Clone()){}

Operator::OperatorPriority Operator::GetPriority() const {
    return priority;
}

void Operator::SetLeft(const std::unique_ptr<Token> & lhs) {
    leftOperand = lhs->Clone();
}

void Operator::SetRight(const std::unique_ptr<Token> & rhs) {
    rightOperand = rhs->Clone();
}