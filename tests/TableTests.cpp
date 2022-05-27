/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "TableTests.h"
#include "../src/Table.h"
#include <iostream>
#include "Assertion.h"
#include "../src/NumberCell.h"
#include "../src/StringCell.h"

using namespace std;

void TableTests::testTable() {
    cout << "*************************************" << endl;
    cout << "Running: " << __FUNCTION__ << endl;

    Table table;
    table.AddCell(NumberCell("A1", "2", 2)).AddCell(NumberCell("B2", "A1 * 2", 4));

    Assertion::Test(table.ContainsCell({"A1"}), true);
    Assertion::Test(table.ContainsCell({"B2"}), true);
    Assertion::Test(table.ContainsCell({"C1"}), false);
    Assertion::Test(table.ContainsCell({"A2"}), false);

    table.DelCell({"A1"});

    Assertion::Test(table.ContainsCell({"A1"}), false);

    table.AddCell(NumberCell("A1", "2", 2)).AddCell(NumberCell("C3", "0", 0));

    table.SetCellColor({"A1"}, 100);
    table.SetCellColor({"B2"}, 50);
    table.SetCellColor({"C1"}, 10);

    Assertion::Test(table.GetCellColor({"A1"}), 100);
    Assertion::Test(table.GetCellColor({"B2"}), 50);
    Assertion::Test(table.GetCellColor({"C1"}), Cell::DEFAULT_COLOR);
    Assertion::Test(table.GetCellColor({"C3"}), Cell::DEFAULT_COLOR);

    table.AddCell(StringCell("A2", "ahoj")).AddCell(StringCell("B1", "test"));

    Assertion::Test(table.GetCellNumericValue({"A1"}), 2.0);
    Assertion::Test(table.GetCellNumericValue({"A2"}), 0.0);
    Assertion::Test(table.GetCellNumericValue({"B1"}), 0.0);
    Assertion::Test(table.GetCellNumericValue({"B2"}), 4.0);
    Assertion::Test(table.GetCellNumericValue({"C3"}), 0.0);
    Assertion::Test(table.GetCellNumericValue({"C1"}), 0.0);

    Assertion::Test(table.GetCellOrigValue({"A1"}), "2"s);
    Assertion::Test(table.GetCellOrigValue({"A2"}), "ahoj"s);
    Assertion::Test(table.GetCellOrigValue({"B1"}), "test"s);
    Assertion::Test(table.GetCellOrigValue({"B2"}), "A1 * 2"s);
    Assertion::Test(table.GetCellOrigValue({"C3"}), "0"s);
    Assertion::Test(table.GetCellOrigValue({"C1"}), ""s);

    cout << "Finished: " << __FUNCTION__ << endl;
    cout << "*************************************" << endl;
}

void TableTests::runAll() {
    testTable();
}