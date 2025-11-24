#include "pid.h"

PID::PID(double K, double T, double TD, double dt)
    : K(K), T(T), TD(TD), dt(dt)
{
    // Коэффициенты для дискретного ПИД
    q0 = K * (1.0 + dt / T + TD / dt);
    q1 = -K * (1.0 + 2.0 * TD / dt);
    q2 = K * TD / dt;
}

double PID::update(double e)
{
    double u = u_prev + q0 * e + q1 * e_prev1 + q2 * e_prev2;

    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;

    return u;
}
