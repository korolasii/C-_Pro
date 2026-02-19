#include <iostream>
#include "mathlib.h"

int main() {
    std::cout << "5! = " << mathlib::factorial(5) << "\n";
    std::cout << "2 + 3 = " << mathlib::add(2, 3) << "\n";
    std::cout << "log2(8) = " << mathlib::logarithm(8, 2) << "\n";
    return 0;
}
