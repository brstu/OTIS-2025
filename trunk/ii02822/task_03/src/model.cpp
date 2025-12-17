#include <cmath>

// Глобальные переменные делаем const и разделяем объявления
static const double K_obj_default = 1.0;
static const double T_obj_default = 0.5;

static double K_obj = K_obj_default;
static double T_obj = T_obj_default;
static double y_prev = 0.0;

void modelInit(double K, double T) {
    K_obj = K;
    T_obj = T;
    y_prev = 0.0;
}

double modelUpdate(double u, double dt) {
    double a;
    double b;

    if (T_obj > 0) {
        a = 1.0 - dt / T_obj;
        b = K_obj * dt / T_obj;
    }
    else {
        a = 0.0;
        b = K_obj;
    }

    const double y = a * y_prev + b * u;
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