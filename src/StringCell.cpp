/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 01.05.2021
 */

#include "StringCell.h"

using namespace std;

unique_ptr<Cell> StringCell::Clone() const {
    return unique_ptr<Cell>(new StringCell(*this));
}

std::string StringCell::GetDisplayValue() const {
    return origValue;
}