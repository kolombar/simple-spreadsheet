/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

// Inspired by https://www.geeksforgeeks.org/expression-evaluation/

#pragma once

#include <string>
#include <queue>
#include <stack>
#include <map>
#include "Operator.h"
#include "Parameters.h"
#include "../Table.h"
#include "ParsedResult.h"
#include "../../tests/ParserTests.h"

/**
 * @brief A parser that enables parsing and evaluating mathematical expressions represented as strings.
 * @details The class has to be initialized with an instance of Table because of possible cell references in the expressions. It holds two registers - one for available operators and one for available functions. All expressions have to be passed as strings. Firstly, every expression is tokenized (i.e. parsed to tokens reprezenting either operators or variables). Secondly, tokenized expression is evaluated. Priority of expression evaluation can be determined by using parentheses.
 */
class MathParser {
public:
    explicit MathParser(std::shared_ptr<Table> table);

    /**
     * Parses and evaluates the given expression.
     * @param expr expression to be parsed
     * @return parsed result
     */
    std::unique_ptr<ParsedResult> Parse(const std::string &expr) const;

    friend class ParserTests;

private:
    std::shared_ptr<Table> table;

    typedef std::unique_ptr<Variable> (*customFunc)(const Parameters & params);
    std::map<std::string, customFunc> registeredFunctions;

    typedef std::unique_ptr<Operator> (*customOper)();
    std::map<std::string, customOper> registeredOperators;

    void CreateFunctionRegister();

    void CreateOperatorRegister();

    /**
     * Tokenizes the given expressions, i.e. it parses the expression into operators and variables.
     * @param expression expression to be parsed
     * @param variables parsed variables
     * @param operators parsed operators
     * @param result parsed result (particularly for storing cell dependencies)
     */
    void Tokenize(const std::string &expression,
                  std::queue<std::unique_ptr<Token>> & variables,
                  std::queue<std::unique_ptr<Operator>> & operators,
                  std::unique_ptr<ParsedResult> &result) const;

    /**
     * Checks whether current expression is a number and if so, it creates the corresponding token and adds it to the queue of already found tokends.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @param tokens queue with already parsed tokens
     * @return true if expression is a number and it was successfully tokenized
     */
    bool ParseNumber(std::string::iterator & it,
                            const std::string &expr,
                            std::queue<std::unique_ptr<Token>> & tokens) const;

    /**
     * Check whether current expression is an operator and if so, it creates the corresponding token and adds it to the queue of already found operators.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @param opersQueue queue with already parsed operators
     * @return true if expression is an operator and it was successfully tokenized
     */
    bool ParseOperator(std::string::iterator & it,
                       const std::string &expr,
                       std::queue<std::unique_ptr<Operator>> & opersQueue) const;

    /**
     * Check whether current expression is a function and if so, it creates the corresponding token and adds it to the queue of already found tokens.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @param tokens queue with already found tokens
     * @param result parsed result (particularly for storing cell dependencies)
     * @return true if expression is a function and it was successfully tokenized
     */
    bool ParseFunction(std::string::iterator & it,
                       const std::string &expr,
                       std::queue<std::unique_ptr<Token>> & tokens,
                       std::unique_ptr<ParsedResult> & result) const;

    /**
     * Check whether current expression is a parenthesis (with another expression inside) and if so, it parses and evaluates the expression in between two parentheses.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @param tokens queue with already found tokens
     * @return true if expression is a parenthesis (with another expression inside) and it was successfully tokenized
     */
    bool ParseParentheses(std::string::iterator & it,
                          const std::string & expr,
                          std::queue<std::unique_ptr<Token>> & tokens) const;

    /**
     * Check whether current expression is a cell reference and if so, it creates the corresponding token and adds it to the queue of already found tokens.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @param tokens queue with already found tokens
     * @param result parsed result (particularly for storing cell dependencies)
     * @return true if expression is a cell reference and it was successfully tokenized
     */
    bool ParseCellReference(std::string::iterator & it,
                            const std::string & expr,
                            std::queue<std::unique_ptr<Token>> & tokens,
                            std::unique_ptr<ParsedResult> &result) const;

    /**
     * Checks whether current expression is a negative cell reference (i.e. a cell reference with a minus in front of it).
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @return true if expression is a negative cell reference
     */
    bool IsNegativeCellReference(const std::string::iterator &it, const std::string &expr) const;

    /**
     * Checks whether current expression is a cell reference.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @return true if expression is a cell reference
     */
    bool IsCellReference(const std::string::iterator &it, const std::string &expr) const;

    /**
     * This method helps to differentiate between a minus operator and negative expression.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @return true if the minus sign represents a negative expression
     */
    bool IsNegativeExpression(const std::string::iterator &it, const std::string &expr) const;

    /**
     * Evaluates current operator.
     * @param variablesStack stack with tokenized variables
     * @param operatorsStack stack with tokenized operators
     */
    void EvalOperator(std::stack<std::unique_ptr<Token>> & variablesStack,
                             std::stack<std::unique_ptr<Operator>> & operatorsStack) const;

    /**
     * Checks whether set of letters represents any known function.
     * @param it iterator of the math expression
     * @param expr expression to be parsed
     * @return true if the set of letters represents any known function
     */
     bool IsFunctionString(std::string::iterator it, const std::string &expr) const;

     /**
      * Checks whether the given number-string is a valid number
      * @param number number-string to be checked
      * @return true if the string is a valid number
      */
     bool IsNumberValid(const std::string &number) const;
};

