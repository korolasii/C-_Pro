#include "mathlib.h"
#include <stdexcept>
#include <cmath>

namespace mathlib {

    long long factorial(int n) {
        if (n < 0) throw std::invalid_argument("Negative factorial not defined");
        long long result = 1;
        for (int i = 1; i <= n; ++i) result *= i;
        return result;
    }

    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        return a / b;
    }

    double logarithm(double x, double base) {
        if (x <= 0 || base <= 0 || base == 1)
            throw std::invalid_argument("Invalid arguments for logarithm");
        return std::log(x) / std::log(base);
    }
}
