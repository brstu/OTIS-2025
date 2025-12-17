#include "functions.h"
#include <cmath>

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double u, double y_pred, double u_pred) {
    return a * y - b * pow(y_pred, 2) + c * u + d * sin(u_pred);
}

std::vector<double> simulatePIDRegulatorUsingNonLinearModel(double w, int steps) {
    double y = 1.1; // Initial y
    double u = 0.0; // Initial u
    double y_prev = y - 0.1; // Init previous y (0.1 for difference)
    double u_prev = u - 0.1; // Init previous u (0.1 for difference)

    double e = w - y;
    double e_prev1 = e;
    double e_prev2 = e;
    std::vector<double> results;

    for (int k = 0; k < steps; k++) {
        double u_new = u + q0 * e + q1 * e_prev1 + q2 * e_prev2;
        double y_new = nonlinearModel(y, u_new, y_prev, u_prev);
        double e_new = w - y_new;

        results.push_back(y_new);

        y_prev = y;
        u_prev = u;
        y = y_new;
        u = u_new;
        e_prev2 = e_prev1;
        e_prev1 = e;
        e = e_new;
    }

    return results;
}