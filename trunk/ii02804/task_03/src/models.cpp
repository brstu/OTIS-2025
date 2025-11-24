#include "models.h"
#include <cmath>
#include <algorithm> // для clamp

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear_model(double y, double& y_prev, double u, double& u_prev,
                        double a, double b, double c, double d) {
    // чтобы не было NaN/бесконечности
    y_prev = y;
    u_prev = u;

    double linear_part = a * y + c * u;
    double nonlinear_part = -b * y * y + d * std::sin(u_prev);

    double y_next = linear_part + nonlinear_part;

    // чтобы не было nan
    if (!std::isfinite(y_next)) y_next = 0.0;

    return y_next;
}
