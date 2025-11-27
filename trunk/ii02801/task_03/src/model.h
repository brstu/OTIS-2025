#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <cmath>

/**
 * Линейная модель:
 * y(t) = a*y(t-1) + b*u(t-1)
 */
std::vector<double> simulateLinear(
    int steps,
    double y_init,
    double a,
    double b,
    const std::vector<double>& u
);

/**
 * Нелинейная модель:
 * y[t] = a*y[t-1] − b*y[t-2]^2 + c*u[t-1] + d*sin(u[t-2])
 */
std::vector<double> simulateNonlinear(
    int steps,
    double y_init,
    double a,
    double b,
    double c,
    double d,
    const std::vector<double>& u
);

#endif
