/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "DivideOperator.h"

double DivideOperator::Evaluate() const {
    return leftOperand->Evaluate() / rightOperand->Evaluate();
}

std::unique_ptr<Token> DivideOperator::Clone() const {
    return std::unique_ptr<Token>(new DivideOperator(*this));
}