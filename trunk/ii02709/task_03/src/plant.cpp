/**
 * @file plant.cpp
 * @brief Реализация моделей объекта управления.
 */

#include "plant.h"
#include <cmath>

LinearPlant::LinearPlant(double a_, double b_, double c_, double y0)
    : a(a_), b(b_), c(c_), yk(y0)
{
}

double LinearPlant::step(double u) {
    yk = a * yk + b * u + c;
    return yk;
}

void LinearPlant::reset() {
    yk = 0.0;
}

NonlinearPlant::NonlinearPlant(double a_, double b_, double c_, double alpha_, double y0)
    : a(a_), b(b_), c(c_), alpha(alpha_), yk(y0)
{
}

double NonlinearPlant::step(double u) {
    double u_eff = u / (1.0 + alpha * std::fabs(u));
    yk = a * yk + b * u_eff + c;
    return yk;
}

void NonlinearPlant::reset() {
    yk = 0.0;
}
