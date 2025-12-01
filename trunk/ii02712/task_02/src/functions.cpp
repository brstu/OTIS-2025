#include "functions.h"
#include <cmath>

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double u, double y_pred, double u_pred) {
    return a * y - b * y * y + c * u + d * std::sin(u);
}
