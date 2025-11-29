#include "model.h"
#include <cmath>

double plant_linear(double y_prev, double u, const ModelParams& p) {
    return p.a * y_prev + p.b * u;
}

double plant_nonlinear(double y_prev, double y_prev2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * (y_prev2 * y_prev2) + p.c * u + p.d * std::sin(u);
}
