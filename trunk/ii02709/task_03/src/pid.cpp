#include "pid.h"
#include <cmath>

PID::PID(double K, double T, double TD, double T0) {
    if (T <= 0.0) {
        q0 = K * (1.0 + TD / T0);
        q1 = -K * (1.0 + 2.0 * TD / T0);
        q2 = K * (TD / T0);
    } else {
        q0 = K * (1.0 + T0/(2.0*T) + TD/T0);
        q1 = -K * (1.0 - T0/(2.0*T) + 2.0*TD/T0);
        q2 = K * (TD/T0);
    }
    reset(0.0);
}

PID::PID(DiscreteTag, double q0_, double q1_, double q2_, double u0)
: q0(q0_), q1(q1_), q2(q2_) {
    reset(u0);
}

void PID::reset(double u0) {
    u_prev = u0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}

double PID::update(double e) {
    double delta = q0*e + q1*e_prev1 + q2*e_prev2;
    double u = u_prev + delta;
    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;
    return u;
}
