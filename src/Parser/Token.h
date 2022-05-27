/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 28.04.2021
 */

#pragma once

#include <memory>

/**
 * @brief A base class representing tokens (i.e. individual elements) of mathematical expression.
 */
class Token {
public:
    Token() = default;
    virtual ~Token() = default;

    virtual double Evaluate() const = 0;

    virtual std::unique_ptr<Token> Clone() const = 0;

};

