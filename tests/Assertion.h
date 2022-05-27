/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <iostream>


struct Assertion {
    template<typename T_, typename Cmp_ = std::equal_to<T_>>
    static void Test(const T_ &lhs, const T_ &rhs, Cmp_ func = std::equal_to<T_>()) {
        if (!func(lhs, rhs)) {
            std::cout << "*************** ASSERTION INFO ***************" << std::endl;
            std::cout << "left-hand side: " << lhs << std::endl;
            std::cout << "right-hand side: " << rhs << std::endl;
            throw std::logic_error("Assertion failed!");
        }
    }
};
