#include "functions.h"
#include <cmath>

// Линейная модель
double linearModel(double y, double u, const LinearParams& p) {
    return p.a * y + p.b * u;
}

// Нелинейная модель
double nonlinearModel(double y, double y_prev, double u, double u_prev, const NonlinearParams& p) {
    return p.a * y - p.b * std::pow(y_prev, 2.0) + p.c * u + p.d * std::sin(u_prev);
}
