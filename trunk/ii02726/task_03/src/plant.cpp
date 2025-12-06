#include "plant.h"

std::vector<double> linear_func(int steps, double a, double b,
                                const std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps, 0.0);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; ++i) {
        y[i] = a * y[i - 1] + b * u[i - 1];
    }
    return y;
}

std::vector<double> nonlinear_func(int steps, const abcd& str_fun,
                                   const std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps, 0.0);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; ++i) {
        y[i] = str_fun.a * y[i - 1]
             - str_fun.b * y[i - 2] * y[i - 2]
             + str_fun.c * u[i - 1]
             + str_fun.d * std::sin(u[i - 2]);
    }
    return y;
}
