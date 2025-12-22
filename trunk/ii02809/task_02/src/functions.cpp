#include "functions.h"
#include <cmath>

double linearModel(double y_tau, double u_tau, const ModelParams& params) {
    return params.a * y_tau + params.b * u_tau;
}

double nonlinearModel(double y_tau, double y_tau_minus_1, double u_tau, double u_tau_minus_1, const ModelParams& params) {
    return params.a * y_tau
        - params.b * y_tau_minus_1 * y_tau_minus_1
        + params.c * u_tau
        + params.d * sin(u_tau_minus_1);
}
