/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "MultiplyOperator.h"

double MultiplyOperator::Evaluate() const {
    return leftOperand->Evaluate() * rightOperand->Evaluate();
}

std::unique_ptr<Token> MultiplyOperator::Clone() const {
    return std::unique_ptr<Token>(new MultiplyOperator(*this));
}