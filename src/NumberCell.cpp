/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include <sstream>
#include <iostream>
#include "NumberCell.h"

using namespace std;

unique_ptr<Cell> NumberCell::Clone() const {
    return unique_ptr<Cell>(new NumberCell(*this));
}

std::string NumberCell::GetDisplayValue() const {
    stringstream ss;
    ss << numericValue;
    string displayValue;
    ss >> displayValue;
    return displayValue;
}