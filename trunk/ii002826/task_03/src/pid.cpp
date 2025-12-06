#include "pid.h"
#include <cmath>

PID::PID(const PIDParams& p) : p_(p) {
    // Защита от деления на ноль для T и T0
    double T = (p_.T == 0.0) ? 1e-12 : p_.T;
    double T0 = (p_.T0 == 0.0) ? 1e-12 : p_.T0;

    q0_ = p_.K * (1.0 + T0 / T + p_.Td / T0);
    q1_ = -p_.K * (1.0 + 2.0 * p_.Td / T0);
    q2_ = p_.K * (p_.Td / T0);
}

double PID::update(double e) {
    double du = q0_ * e + q1_ * e_prev_ + q2_ * e_prev2_;
    double u = u_prev_ + du;

    // shift memory
    e_prev2_ = e_prev_;
    e_prev_  = e;
    u_prev_  = u;

    return u;
}

void PID::reset() {
    u_prev_ = e_prev_ = e_prev2_ = 0.0;
}
