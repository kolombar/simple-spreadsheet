/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include <iostream>
#include "ParserTests.h"
#include "../src/Parser/CosFunction.h"
#include "../src/Parser/DivideOperator.h"
#include "../src/Table.h"
#include "../src/Command.h"
#include "Assertion.h"
#include <math.h>
#include "../src/NumberCell.h"

using namespace std;

void ParserTests::testParseNumber() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    queue<unique_ptr<Token>> tokens;
    vector<string> testValues = {"10", "150", "-1", "abc", "", "\t", "01111", "10..5", "10.", "01", "10.55", "-10.55", "0.05", "-0.05"};
    vector<bool> parseResults = {true, true, true, false, false, false, false, false, false, false, true, true, true, true};
    auto parseResultsIt = parseResults.begin();
    shared_ptr<Table> table;
    table = make_shared<Table>();
    MathParser parser(table);

    for (auto &val : testValues) {
        string number(val);
        auto it = number.begin();
        cout << "test number: " << number << endl;
        Assertion::Test(parser.ParseNumber(it, number, tokens), static_cast<bool>(*parseResultsIt));
        parseResultsIt++;
    }

    Assertion::Test(tokens.front().get()->Evaluate(), 10.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 150.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -1.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 10.55);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -10.55);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 0.05);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -0.05);
    tokens.pop();
    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void ParserTests::testParseFunction() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    queue<unique_ptr<Token>> tokens;
    vector<string> testValues = {"cos(3)", "sin(10.5)", "log(0.8)", "10", "", "\t", "log(3"};
    vector<bool> parseResults = {true, true, true, false, false, false, false};
    unique_ptr<ParsedResult> result = make_unique<ParsedResult>();
    shared_ptr<Table> table;
    table = make_shared<Table>();
    MathParser parser(table);
    auto parseResultsIt = parseResults.begin();
    for (auto &val : testValues) {
        auto it = val.begin();
        cout << "test function: " << val << endl;
        Assertion::Test(parser.ParseFunction(it, val, tokens, result), static_cast<bool>(*parseResultsIt));
        parseResultsIt++;
    }

    // test functions with cell references
    vector<string> testValuesWithRefs = {"cos(A1)", "sin(A1 + B2)", "log(A)", "b", "bac", "a1", "log(a"};
    vector<bool> parseResultsWithRefs = {true, true, false, false, false, false, false};
    table->AddCell(NumberCell("A1", "2", 2.0));
    table->AddCell(NumberCell("B2", "3", 3.0));
    View::ROWS = 2;
    View::COLUMNS = 2;
    MathParser parserWithRefs(table);

    auto parseResultsWithRefsIt = parseResultsWithRefs.begin();
    for (auto &val : testValuesWithRefs) {
        auto it = val.begin();
        cout << "test function: " << val << endl;
        try {
            Assertion::Test(parserWithRefs.ParseFunction(it, val, tokens, result),
                            static_cast<bool>(*parseResultsWithRefsIt));
        } catch (const invalid_argument &e) {
            cout << "error occured: " << e.what() << endl;
        }
        parseResultsWithRefsIt++;
    }

    Assertion::Test(tokens.front().get()->Evaluate(), cos(3.0));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), sin(10.5));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), log(0.8));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), cos(2.0));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), sin(5.0));
    tokens.pop();
    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void ParserTests::testParseParentheses() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    queue<unique_ptr<Token>> tokens;
    vector<string> testValues = {"(1 + log(1))", "(2", "(-2)", "abc", "", "\t", "((10 - 2)*2)"};
    vector<bool> parseResults = {true, false, true, false, false, false, true};
    unique_ptr<ParsedResult> result = make_unique<ParsedResult>();
    shared_ptr<Table> table;
    table = make_shared<Table>();
    MathParser parser(table);
    auto parseResultsIt = parseResults.begin();
    for (auto &val : testValues) {
        string number(val);
        auto it = number.begin();
        cout << "test expr: " << number << endl;
        Assertion::Test(parser.ParseParentheses(it, number, tokens), static_cast<bool>(*parseResultsIt));
        parseResultsIt++;
    }

    // test exprs with cell references
    vector<string> testValuesWithRefs = {"(A1 + log(1))", "(B2", "(-A1)", "(A1 / B2)", "(a1()", "a1", "((a1 - b2) * b2)"};
    vector<bool> parseResultsWithRefs = {true, false, true, true, false, false, true};
    table->AddCell(NumberCell("A1", "2", 2.0));
    table->AddCell(NumberCell("B2", "3", 3.0));
    View::ROWS = 2;
    View::COLUMNS = 2;
    MathParser parserWithRefs(table);

    auto parseResultsWithRefsIt = parseResultsWithRefs.begin();
    for (auto &val : testValuesWithRefs) {
        auto it = val.begin();
        cout << "test expr: " << val << endl;
        try {
            Assertion::Test(parserWithRefs.ParseParentheses(it, val, tokens),
                            static_cast<bool>(*parseResultsWithRefsIt));
        } catch (const invalid_argument &e) {
            cout << "error occured: " << e.what() << endl;
        }
        parseResultsWithRefsIt++;
    }

    Assertion::Test(tokens.front().get()->Evaluate(), 1.0 + log(1.0));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -2.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), (10.0 - 2.0) * 2.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 2.0 + log(1.0));
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -2.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 2.0 / 3.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), (2.0 - 3.0) * 3.0);
    tokens.pop();
    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void ParserTests::testParseCellReference() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    queue<unique_ptr<Token>> tokens;
    vector<string> testValues = {"A1", "AA1", "b2", "b22", "", "\t", "-a1"};
    vector<bool> parseResults = {true, false, true, false, false, false, true};
    unique_ptr<ParsedResult> result = make_unique<ParsedResult>();
    shared_ptr<Table> table;
    table = make_shared<Table>();
    table->AddCell(NumberCell("A1", "2", 2.0));
    table->AddCell(NumberCell("B2", "3", 3.0));
    View::ROWS = 2;
    View::COLUMNS = 2;
    MathParser parser(table);
    auto parseResultsIt = parseResults.begin();
    for (auto &val : testValues) {
        string number(val);
        auto it = number.begin();
        cout << "test ref: " << number << endl;
        Assertion::Test(parser.ParseCellReference(it, number, tokens, result), static_cast<bool>(*parseResultsIt));
        parseResultsIt++;
    }

    Assertion::Test(tokens.front().get()->Evaluate(), 2.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), 3.0);
    tokens.pop();
    Assertion::Test(tokens.front().get()->Evaluate(), -2.0);
    tokens.pop();
    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void ParserTests::testParser() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    MathParser parser((shared_ptr<Table>()));

    cout << "test expr: " << "cos(10)" << endl;
    Assertion::Test(parser.Parse("cos(10)")->GetResult(), cos(10));

    cout << "test expr: " << "1 / 5" << endl;
    Assertion::Test(parser.Parse("1 / 5")->GetResult(), 1.0 / 5);

    cout << "test expr: " << "5 + 2 * 10 - 50 / 5 + 2 - 1 + abs(2 - 10)" << endl;
    Assertion::Test(parser.Parse("5 + 2 * 10 - 50 / 5 + 2 - 1 + abs(2 - 10)")->GetResult(), (5 + 2 * 10 - 50 / 5 + 2 - 1 + fabs(2 - 10)));

    cout << "test expr: " << "5 + abs((3 + 2) * 2)" << endl;
    Assertion::Test(parser.Parse("5 + abs((3 + 2) * 2)")->GetResult(), (5 + fabs((3 + 2) * 2)));

    cout << "test expr: " << "(10 - 2)*5" << endl;
    Assertion::Test(parser.Parse("(10 - 2)*5")->GetResult(), (10.0 - 2.0) * 5.0);

    cout << "test expr: " << "-3 * log(2) + 0.5" << endl;
    Assertion::Test(parser.Parse("-3 * log(2) + 0.5")->GetResult(), -3.0 * log(2.0) + 0.5);

    cout << "test expr: " << "ABS(-10) * ( 2 - cos(3))" << endl;
    Assertion::Test(parser.Parse("ABS(-10) * ( 2 - cos(3))")->GetResult(), fabs(-10.0) * (2.0 - cos(3.0)));

    cout << "test expr: " << "1/ 0" << endl;
    Assertion::Test(parser.Parse("1/ 0")->GetResult(), 1.0 / 0.0);

    cout << "test expr: " << "5 / 3" << endl;
    Assertion::Test(parser.Parse("5 / 3")->GetResult(), 5.0 / 3.0);

    cout << "test expr: " << "((2 - 1)*2) - 10" << endl;
    Assertion::Test(parser.Parse("((2 - 1)*2) - 10")->GetResult(), ((2.0 - 1.0)*2.0) - 10.0);

    cout << "test expr: " << "-29 / -40" << endl;
    Assertion::Test(parser.Parse("-29 / -40")->GetResult(), -29.0 / -40.0);

    cout << "test expr: " << "-29 / + 40" << endl;
    try {
        parser.Parse("-29 / + 40");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }


    cout << "test expr: " << "+29" << endl;
    try {
        parser.Parse("+29");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "test expr: " << "29-" << endl;
    try {
        parser.Parse("29-");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "test expr: " << "29 - / 2" << endl;
    try {
        parser.Parse("29 - / 2");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "test expr: " << "( / 2)" << endl;
    try {
        parser.Parse("( / 2)");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "test expr: " << "10 - (*2)" << endl;
    try {
        parser.Parse("10 - (*2)");
        throw logic_error("Exception should have been thrown!");
    } catch (const logic_error &e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void ParserTests::runAll() {
    testParseNumber();
    testParseFunction();
    testParseParentheses();
    testParseCellReference();
    testParser();
}