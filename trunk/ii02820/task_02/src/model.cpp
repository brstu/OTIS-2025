#include "model.h"
#include <cmath>

LinearModel::LinearModel(double a, double b, double initial_y) 
    : a(a), b(b), y_prev(initial_y) {}

double LinearModel::calculate(double u) {
    double y = a * y_prev + b * u;
    y_prev = y;
    return y;
}

NonlinearModel::NonlinearModel(double a, double b, double c, double d, double initial_y)
    : a(a), b(b), c(c), d(d), y_prev(initial_y), y_prev_prev(initial_y) {}

double NonlinearModel::calculate(double u) {
    double y = a * y_prev - b * y_prev_prev * y_prev_prev + c * u + d * sin(u);
    y_prev_prev = y_prev;
    y_prev = y;
    return y;
}
