#include "pid_controller.h"
#include <algorithm>
#include <limits>

static double clamp(double v, double lo, double hi) {
    return (v < lo) ? lo : (v > hi) ? hi : v;
}

PIDController::PIDController(double k, double ti, double td, double dtt)
    : K(k), Ti(ti), Td(td), dt(dtt)
{
    double Ti_safe = (Ti > 0.0) ? Ti : std::numeric_limits<double>::max();
    double Td_safe = td;  // НЕ ограничиваем Td — иначе ломается при Td=0.8

    q0 = K * (1.0 + dt / Ti_safe + Td_safe / dt);
    q1 = -K * (1.0 + 2.0 * Td_safe / dt - dt / Ti_safe);
    q2 = K * (Td_safe / dt);
}

double PIDController::compute(double e)
{
    double du = q0 * e + q1 * e_prev1 + q2 * e_prev2;

    // Мягкий анти-windup
    du = clamp(du, -30.0, 30.0);
    u_prev += du;

    e_prev2 = e_prev1;
    e_prev1 = e;

    return u_prev;
}

void PIDController::reset()
{
    u_prev = e_prev1 = e_prev2 = 0.0;
}