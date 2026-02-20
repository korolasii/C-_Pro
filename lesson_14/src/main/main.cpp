#include <iostream>
#include "../mathlib/mathlib.h" 
#include "../dynlib/dynlib.h"

int main() {
    std::cout << "Factorial(5): " << factorial(5) << std::endl;
    std::cout << "Add(3,4): " << add(3,4) << std::endl;
    std::cout << "Subtract(10,7): " << subtract(10,7) << std::endl;
    std::cout << "Log(10): " << tlog(10) << std::endl;

    std::cout << "Multiply(6,7): " << multiply(6,7) << std::endl;
    std::cout << "Divide(22,7): " << divide(22,7) << std::endl;

    return 0;
}
