/**
 * @file model.cpp
 * @brief Реализация нелинейной модели
 */

#include "model.h"
#include <cmath>

NonlinearModel::NonlinearModel(double a, double b, double c1, double c2)
    : a_(a), b_(b), c1_(c1), c2_(c2) {}

double NonlinearModel::next(double y_curr, double u) const {
    return a_ * y_curr
         - b_ * y_curr * y_curr
         + c1_ * u
         + c2_ * std::sinh(u);
}

std::vector<double> NonlinearModel::simulate(int steps, double y0, double u) const {
    if (steps <= 0) return {};
    std::vector<double> result;
    result.reserve(steps);
    double y = y0;
    for (int i = 0; i < steps; ++i) {
        y = next(y, u);
        result.push_back(y);
    }
    return result;
}