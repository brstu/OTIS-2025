#include "pid.h"
#include <iostream>
#include <vector>
#include <cmath>

PID::PID(double K_val, double Ti_val, double Td_val, double T0_val)
    : K(K_val), Ti(Ti_val), Td(Td_val), T0(T0_val) {}

double PID::calculate(double setpoint, double current_value)
{
    const double U_MIN = 0.0;
    const double U_MAX = 100.0;

    double error = setpoint - current_value;

    double deriv = (error - e_prev1) / T0;
    double d_filtered = d_filter_alpha * d_prev + (1.0 - d_filter_alpha) * deriv;

    double integral_candidate = integral + (T0 / Ti) * error;

    double u_unsat = K * (error + integral_candidate + Td * d_filtered);

    double u_sat = u_unsat;
    if (u_sat > U_MAX) u_sat = U_MAX;
    if (u_sat < U_MIN) u_sat = U_MIN;

    bool allow_integral_update = true;
    if (u_unsat > U_MAX && error > 0.0) {
        allow_integral_update = false;
    }
    if (u_unsat < U_MIN && error < 0.0) {
        allow_integral_update = false;
    }

    if (allow_integral_update) {
        integral = integral_candidate;
    }

    d_prev = d_filtered;
    e_prev2 = e_prev1;
    e_prev1 = error;
    u_prev = u_sat;

    return u_sat;
}

void PID::reset()
{
    e_prev1 = 0.0;
    e_prev2 = 0.0;
    u_prev = 0.0;
    integral = 0.0;
    d_prev = 0.0;
}

std::vector<double> PID::getCoefficients() const
{
    return std::vector<double>{q0, q1, q2};
}

void PID::getParameters(double& K_param, double& Ti_param, double& Td_param) const
{
    K_param = K;
    Ti_param = Ti;
    Td_param = Td;
}