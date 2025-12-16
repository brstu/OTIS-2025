#include <cmath>

static double K_obj = 1.0;
static double T_obj = 0.5;
static double y_prev = 0.0;

void modelInit(double K, double T) {
    K_obj = K;
    T_obj = T;
    y_prev = 0.0;
}

double modelUpdate(double u, double dt) {
    double a, b;

    if (T_obj > 0) {
        a = 1 - dt / T_obj;
        b = K_obj * dt / T_obj;
    }
    else {
        a = 0;
        b = K_obj;
    }

    double y = a * y_prev + b * u;
    y_prev = y;

    return y;
}

void modelReset() {
    y_prev = 0.0;
}

void modelSetParameters(double K, double T) {
    K_obj = K;
    T_obj = T;
    modelReset();
}