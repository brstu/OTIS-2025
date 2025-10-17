#include "lab2.h"
#include <cmath>    // для std::sinh
#include <stdexcept>

namespace lab2 {

long double next_linear(long double y_current, long double u) {
    // прямое применение формулы
    return a * y_current + b * u;
}

long double next_nonlinear(long double y_current, long double u) {
    // проверка на разумные входные данные (опционально)
    // здесь простая реализация — непосредственно по формуле
    return a * y_current - b * y_current * y_current + c1 * u + c2 * std::sinh(u);
}

std::vector<long double> simulate_linear(int steps, long double y0, long double u) {
    if (steps < 0) throw std::invalid_argument("steps must be non-negative");
    std::vector<long double> values;
    values.reserve(steps);
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        long double next = next_linear(y, u);
        values.push_back(next);
        y = next;
    }
    return values;
}

std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u) {
    if (steps < 0) throw std::invalid_argument("steps must be non-negative");
    std::vector<long double> values;
    values.reserve(steps);
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        long double next = next_nonlinear(y, u);
        values.push_back(next);
        y = next;
    }
    return values;
}

} // namespace lab2