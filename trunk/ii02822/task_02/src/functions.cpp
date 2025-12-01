#include <cmath>
#include "functions.h"

double linear(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear(double y_current, double y_prev, double u_current, double a, double b, double c, double d) {
    return a * y_current - b * y_prev * y_prev + c * u_current + d * std::sin(u_current);
}