/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#include "NumberToken.h"

std::unique_ptr<Token> NumberToken::Clone() const {
    return std::unique_ptr<Token>(new NumberToken(*this));
}

double NumberToken::Evaluate() const {
    if (!expression.empty()) {
        return atof(expression.c_str());
    }

    return value;
}