#include "lab2.h"
#include <cmath>

namespace lab2 {

long double next_linear(long double y_current, long double u) {
    return a * y_current + b * u;
}

long double next_nonlinear(long double y_current, long double u) {
    return a * y_current - b * y_current * y_current + c1 * u + c2 * std::sinh(u);
}

std::vector<long double> simulate_linear(int steps, long double y0, long double u) {
    if (steps < 0) return {};
    std::vector<long double> values;
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        y = next_linear(y, u);
        values.push_back(y);
    }
    return values;
}

std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u) {
    if (steps < 0) return {};
    std::vector<long double> values;
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        y = next_nonlinear(y, u);
        values.push_back(y);
    }
    return values;
}

}