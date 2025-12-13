#include <cmath>
#include "model.hpp"

double computeLinear(double y, double u, double a, double b) {
    return a * y + b * u;
}

double computeNonlinear(double y, double y_prev, double u, double a, double b, double c, double d) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u);
}
