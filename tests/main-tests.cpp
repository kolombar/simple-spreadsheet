/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "ParserTests.h"
#include "SheetTests.h"
#include "TableTests.h"

int main() {
    ParserTests::runAll();

    SheetTests::runAll();

    TableTests::runAll();

    return 0;
}