#include "function.h"

PID::PID(double K, double T, double TD, double T0) {
    q0 = K * (1 + T0 / T + TD / T0);
    q1 = -K * (1 + 2 * TD / T0 - T0 / T);
    q2 = K * TD / T0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
    u_prev = 0.0;
}

double PID::compute(double e) {
    double u = u_prev + q0 * e + q1 * e_prev1 + q2 * e_prev2;
    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;
    return u;
}

Object::Object(double tau, double K_obj, double T0) {
    a = exp(-T0 / tau);
    b = K_obj * (1 - a);
    y_prev = 0.0;
}

double Object::update(double u) {
    double y = a * y_prev + b * u;
    y_prev = y;
    return y;
}