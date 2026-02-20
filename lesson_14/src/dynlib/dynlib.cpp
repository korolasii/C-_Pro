#include "dynlib.h"

extern "C" int multiply(int a, int b) {
    return a * b;
}

extern "C" double divide(double a, double b) {
    if (b == 0) return 0;
    return a / b;
}
