/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "PlusOperator.h"

double PlusOperator::Evaluate() const {
    return leftOperand->Evaluate() + rightOperand->Evaluate();
}

std::unique_ptr<Token> PlusOperator::Clone() const {
    return std::unique_ptr<Token>(new PlusOperator(*this));
}