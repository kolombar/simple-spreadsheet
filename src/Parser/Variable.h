/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Token.h"

/**
 * @brief A base class representing variables (i.e. elements with numeric value).
 */
class Variable : public Token {
public:
    explicit Variable(std::string expr) : expression(move(expr)) {};

    Variable() = default;

    virtual ~Variable() = default;

protected:
    std::string expression;
};

