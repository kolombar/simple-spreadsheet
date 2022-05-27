/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "MinusOperator.h"

double MinusOperator::Evaluate() const {
    return leftOperand->Evaluate() - rightOperand->Evaluate();
}

std::unique_ptr<Token> MinusOperator::Clone() const {
    return std::unique_ptr<Token>(new MinusOperator(*this));
}