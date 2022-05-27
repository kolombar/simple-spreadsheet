/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.04.2021
 */

// Inspired by https://www.geeksforgeeks.org/expression-evaluation/

#include <stack>
#include <algorithm>
#include <queue>
#include <iostream>
#include <utility>
#include "MathParser.h"
#include "NumberToken.h"
#include "LogFunction.h"
#include "AbsFunction.h"
#include "SinFunction.h"
#include "PlusOperator.h"
#include "MinusOperator.h"
#include "MultiplyOperator.h"
#include "ParsedResult.h"
#include "DivideOperator.h"
#include "CosFunction.h"
#include "../Command.h"

using namespace std;

MathParser::MathParser(std::shared_ptr<Table> table) : table(std::move(table)) {
    CreateFunctionRegister();
    CreateOperatorRegister();
}

void MathParser::CreateFunctionRegister() {
    registeredFunctions["log"] = [](const Parameters &params) {
        return unique_ptr<Variable>(new LogFunction(params.GetParam(0)));
    };

    registeredFunctions["abs"] = [](const Parameters &params) {
        return unique_ptr<Variable>(new AbsFunction(params.GetParam(0)));
    };

    registeredFunctions["sin"] = [](const Parameters &params) {
        return unique_ptr<Variable>(new SinFunction(params.GetParam(0)));
    };

    registeredFunctions["cos"] = [](const Parameters &params) {
        return unique_ptr<Variable>(new CosFunction(params.GetParam(0)));
    };
}

void MathParser::CreateOperatorRegister() {
    registeredOperators["+"] = []() {
        return unique_ptr<Operator>(new PlusOperator());
    };

    registeredOperators["-"] = []() {
        return unique_ptr<Operator>(new MinusOperator());
    };

    registeredOperators["*"] = []() {
        return unique_ptr<Operator>(new MultiplyOperator());
    };

    registeredOperators["/"] = []() {
        return unique_ptr<Operator>(new DivideOperator());
    };
}

void MathParser::Tokenize(const string &expression,
                          queue<unique_ptr<Token>> &variables,
                          queue<unique_ptr<Operator>> &operators,
                          unique_ptr<ParsedResult> &result) const {
    string str = expression;
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    auto it = str.begin();

    while (it != str.end()) {

        if (ParseParentheses(it, str, variables)) {
            continue;
        }

        if (ParseNumber(it, str, variables)) {
            continue;
        }

        if (ParseFunction(it, str, variables, result)) {
            continue;
        }

        if (ParseCellReference(it, str, variables, result)) {
            continue;
        }

        if (ParseOperator(it, str, operators)) {
            continue;
        }

        throw invalid_argument("Unknown expression.");
    }
}

unique_ptr<ParsedResult> MathParser::Parse(const string &expr) const {
    if (expr.empty()) {
        throw invalid_argument("Empty expression.");
    }
    // Tokenize (parse) expression
    unique_ptr<ParsedResult> result(new ParsedResult());
    queue<unique_ptr<Token>> variables;
    queue<unique_ptr<Operator>> operators;
    Tokenize(expr, variables, operators, result);

    // evaluate expression
    stack<unique_ptr<Token>> variablesStack;
    stack<unique_ptr<Operator>> operatorsStack;
    unique_ptr<Token> elem;
    unique_ptr<Operator> oper;

    bool takeVariable = true;
    while (!variables.empty()) {
        if (takeVariable) {
            elem = move(variables.front());
            variables.pop();
            variablesStack.push(move(elem));
        } else {
            oper = move(operators.front());
            operators.pop();
            while (!operatorsStack.empty() && operatorsStack.top()->GetPriority() >= oper->GetPriority()) {
                EvalOperator(variablesStack, operatorsStack);
            }
            operatorsStack.push(move(oper));
        }
        takeVariable = !takeVariable;
    }

    while (!operatorsStack.empty()) {
        EvalOperator(variablesStack, operatorsStack);
    }

    result->SetResult(variablesStack.top()->Evaluate());
    return result;
}

bool MathParser::ParseNumber(string::iterator &it, const string &expr, queue<unique_ptr<Token>> &tokens) const {
    if (isdigit((*it)) ||
        (IsNegativeExpression(it, expr) && (it + 1) != expr.end() && isdigit(*(it + 1)))) { // we found a number
        auto start = it;
        it++;
        while (it != expr.end() && (isdigit((*it)) || *it == '.')) {
            it++;
        }

        auto end = it;
        string strNum(start, end);

        if (!IsNumberValid(strNum)) { // the number is not valid
            it = start;
            return false;
        }

        tokens.push(unique_ptr<Variable>(new NumberToken(strNum)));
        return true;
    }

    return false;
}

bool MathParser::ParseOperator(string::iterator &it, const string &expr, queue<unique_ptr<Operator>> &opersQueue) const {
    string charToEval = string(1, *it);

    if (registeredOperators.count(charToEval) != 0 && !IsNegativeExpression(it, expr)) { // we found a possible operator
        if ((*it != '-' && it == expr.begin()) || it == (expr.end() - 1)) {
            return false;
        }

        if (it !=  expr.begin()) {
            string prevChar = string(1, *(it - 1));

            if (prevChar == "(" && *it != '-') {
                return false;
            }

            if (registeredOperators.count(prevChar) != 0 && *it != '-') {
                return false;
            }
        }

        opersQueue.push(registeredOperators.at(charToEval)());
        it++;
        return true;
    }

    return false;
}

bool MathParser::ParseFunction(string::iterator &it,
                               const string &expr,
                               queue<unique_ptr<Token>> &tokens, unique_ptr<ParsedResult> &result) const {
    if (IsFunctionString(it, expr)) { // we found a function
        auto start = it;
        it++;

        while (it != expr.end() && *it != '(') {
            it++;
        }

        if (it == expr.end()) {
            it = start;
            return false;
        }

        string func(start, it);
        auto parenStart = ++it;

        // there might be other parentheses inside the current ones
        int parenCnt = 0;
        while (it != expr.end()) {
            // increment parentheses count if we encounter any left parenthesis
            if (*it == '(') {
                parenCnt++;
            }

            if (*it == ')') {
                // decrement the parentheses count if we encounter any right parenthesis (and if we have encountered any left parenthesis before)
                if (parenCnt > 0) {
                    parenCnt--;
                } else {
                    break;
                }
            }
            it++;
        }

        if (it != expr.end()) {
            it++; // this is to include the closing parenthesis
        } else { // we haven't found the closing parenthesis - set the iterator to its original value and report failure
            it = start;
            return false;
        }

        auto end = it;
        string arg(parenStart, end - 1);

        if (registeredFunctions.count(func) == 0) { // the function is unknown
            it = start;
            return false;
        }

        Parameters params(arg, table);

        // store cell dependencies found in function arguments
        for (auto &dep : params.GetCellReferences()) {
            result->AddDependency(dep);
        }

        tokens.push(registeredFunctions.at(func)(params));
        return true;
    }

    return false;
}

bool MathParser::ParseParentheses(string::iterator &it, const string &expr, queue<unique_ptr<Token>> &tokens) const {
    if (*it == '(') {
        auto start = ++it;

        // there might be other parentheses inside the current ones
        int parenCnt = 0;
        while (it != expr.end()) {
            // increment parentheses count if we encounter any left parenthesis
            if (*it == '(') {
                parenCnt++;
            }

            if (*it == ')') {
                // decrement the parentheses count if we encounter any right parenthesis (and if we have encountered any left parenthesis before)
                if (parenCnt > 0) {
                    parenCnt--;
                } else {
                    break;
                }
            }
            it++;
        }

        // we haven't found the closing parenthesis - set the iterator to its original value and report failure
        if (it == expr.end()) {
            it = --start;
            return false;
        }

        auto end = it++;

        unique_ptr<ParsedResult> result = Parse(string(start, end));
        tokens.push(std::unique_ptr<Variable>(new NumberToken(result->GetResult())));
        return true;
    }

    return false;
}

bool MathParser::ParseCellReference(string::iterator &it, const string &expr, queue<unique_ptr<Token>> &tokens,
                                    unique_ptr<ParsedResult> &result) const {
    if (IsCellReference(it, expr) || IsNegativeCellReference(it, expr)) {
        auto itCopy = it;
        bool isNegative = false;
        if (*it == '-') {
            isNegative = true;
            it++;
        }

        auto start = it++;

        while (it != expr.end() && isdigit(*it)) {
            it++;
        }

        auto end = it;

        string ref(start, end);
        Coords coords(ref);

        // if the found coordinates are not valid, we set the iterator back to its original value and report failure
        if (!coords.IsValid()) {
            it = itCopy;
            return false;
        }

        // add the found coordinates to the list of cell dependencies
        result->AddDependency(coords);

        // get the numerical value of the given cell
        double numericResult = table->GetCellNumericValue(ref);

        if (isNegative) {
            tokens.push(unique_ptr<Variable>(new NumberToken(-numericResult)));
        } else {
            tokens.push(unique_ptr<Variable>(new NumberToken(numericResult)));
        }

        return true;
    }

    return false;
}

bool MathParser::IsNegativeCellReference(const std::string::iterator &it, const std::string &expr) const {
    return IsNegativeExpression(it, expr) && IsCellReference(it + 1, expr);
}

bool MathParser::IsCellReference(const std::string::iterator &it, const std::string &expr) const {
    return ((*it >= 'A' && *it <= 'Z') || (*it >= 'a' && *it <= 'z')) && ((it + 1) != expr.end() && isdigit(*(it + 1)));
}

bool MathParser::IsNegativeExpression(const std::string::iterator &it, const std::string &expr) const {
    return *it == '-' && (it == expr.begin() || *(it - 1) == '(' || *(it - 1) == '+' || *(it - 1) == '*' || *(it - 1) == '/');
}

void MathParser::EvalOperator(stack<unique_ptr<Token>> &variablesStack, stack<unique_ptr<Operator>> &operatorsStack) const {
    std::unique_ptr<Token> secondVal(std::move(variablesStack.top()));
    variablesStack.pop();

    std::unique_ptr<Token> firstVal(std::move(variablesStack.top()));
    variablesStack.pop();

    std::unique_ptr<Operator> op(std::move(operatorsStack.top()));
    operatorsStack.pop();

    op->SetLeft(firstVal);
    op->SetRight(secondVal);

    variablesStack.push(std::move(op));
}

bool MathParser::IsFunctionString(string::iterator it, const std::string &expr) const {
    while (it != expr.end() && ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z'))) {
        it++;
    }

    if (it != expr.end() && *it == '(') {
        return true;
    }

    return false;
}

bool MathParser::IsNumberValid(const std::string &number) const {
    auto it = number.begin();

    if (*it == '0' && ((it + 1) != number.end() && isdigit(*(it + 1)))) {
        return false;
    }

    if (*it == '-') {
        it++;
    }

    int cntDots = 0;

    while (it != number.end()) {
        if (*it == '.') {
            cntDots++;
        }

        if (!(isdigit(*it) || *it == '.')) {
            return false;
        }

        it++;
    }

    if (*(--it) == '.') {
        return false;
    }

    if (cntDots > 1) {
        return false;
    }

    return true;
}