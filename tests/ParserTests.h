/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

class ParserTests {
public:
    static void runAll() ;
private:

    static void testParser() ;

    void testTokenize() const;

    static void testParseNumber() ;

    static void testParseParentheses() ;

    static void testParseFunction() ;

    static void testParseCellReference() ;
};
