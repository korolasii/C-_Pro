#include "mathlib.h"
#include <cmath>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

double tlog(double x) {
    return std::log(x);
}
