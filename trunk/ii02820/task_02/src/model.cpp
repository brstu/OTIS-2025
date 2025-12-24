#include <cmath>
#include "model.h"

double linear(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

double non_linear(double y_current, double y_prev, double u, 
                  double a, double b, double c, double d) {
    return a * y_current - b * std::pow(y_prev, 2) + c * u + d * std::sin(u);
}