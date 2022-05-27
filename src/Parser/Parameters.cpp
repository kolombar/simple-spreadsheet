/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 28.04.2021
 */

#include <iostream>
#include "Parameters.h"
#include "MathParser.h"

using namespace std;

Parameters::Parameters(string parameters, const shared_ptr<Table>& table) {
    size_t pos, oldPos = 0;
    string param;
    MathParser parser(table);

    if (parameters.find(',') == string::npos) {
        unique_ptr<ParsedResult> result = parser.Parse(parameters);
        for (auto &dep : result->GetCellReferences()) {
            cellReferences.insert(dep);
        }
        params.push_back(result->GetResult());
    } else {
        int cnt = 0;
        while ((pos = parameters.find(',')) != string::npos) {
            param = parameters.substr(0, pos);
            unique_ptr<ParsedResult> result = parser.Parse(param);
            for (auto &dep : result->GetCellReferences()) {
                cellReferences.insert(dep);
            }
            params.push_back(result->GetResult());
            parameters = parameters.substr(oldPos, parameters.size());
            oldPos = pos + 1;
            cnt++;
            if (cnt == 4) {
                break;
            }
        }
    }
}

double Parameters::GetParam(const int pos) const {
    if (pos < (int) params.size()) {
        return params[pos];
    } else {
        throw out_of_range("Index out of range");
    }
}

std::set<Coords> Parameters::GetCellReferences() const {
    return cellReferences;
}