/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 02.05.2021
 */

#include "SheetTests.h"
#include "../src/Sheet.h"
#include <iostream>
#include "Assertion.h"

using namespace std;

void SheetTests::runAll() {
    testIsCyclePresent();
    testSheet();
}

void SheetTests::testIsCyclePresent() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;

    Sheet sheet;
    sheet.cellDependencies[Coords("D5")] = set<Coords>{Coords("A1"), Coords("C10")};
    sheet.cellDependencies[Coords("A2")] = set<Coords>{Coords("D5"), Coords("C10")};
    sheet.cellDependencies[Coords("A1")] = set<Coords>{Coords("A2")};

    Assertion::Test(sheet.IsCyclePresent(), true);

    sheet.Clear();

    sheet.cellDependencies[Coords("A1")] = set<Coords>{Coords("B1")};
    sheet.cellDependencies[Coords("B1")] = set<Coords>{Coords("A1")};

    Assertion::Test(sheet.IsCyclePresent(), true);

    sheet.Clear();

    sheet.cellDependencies[Coords("A1")] = set<Coords>{Coords("B1")};
    sheet.cellDependencies[Coords("B1")] = set<Coords>{Coords("D1"), Coords("C1")};
    sheet.cellDependencies[Coords("C1")] = set<Coords>{Coords("E10")};
    sheet.cellDependencies[Coords("D1")] = set<Coords>{Coords("B2")};

    Assertion::Test(sheet.IsCyclePresent(), false);

    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void SheetTests::testSheet() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;
    Sheet sheet;

    sheet.AddCell(Coords("A1"), "100");
    sheet.AddCell(Coords("C10"), "200");
    sheet.AddCell(Coords("D5"), "A1 + C10");
    sheet.AddCell(Coords("A2"), "D5 - 10");
    sheet.AddCell(Coords("E8"), "20 - 100");
    
    try {
        sheet.AddCell(Coords("A1"), "A2");
        throw logic_error("Cycle should have been detected!");
    } catch (const logic_error & e) {}

    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;

}