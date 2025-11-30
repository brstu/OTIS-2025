/**
 * @file pid.cpp
 * @brief Реализация дискретного ПИД-регулятора.
 */

#include "pid.h"
#include <array>
#include <cmath>

namespace {

inline std::array<double,3> compute_q_values(double K, double T, double TD, double T0) {
    std::array<double,3> q = {0.0, 0.0, 0.0};
    if (T <= 0.0) {
        q[0] = K * (1.0 + TD / T0);
        q[1] = -K * (1.0 + 2.0 * TD / T0);
        q[2] = K * (TD / T0);
    } else {
        q[0] = K * (1.0 + T0 / (2.0 * T) + TD / T0);
        q[1] = -K * (1.0 - T0 / (2.0 * T) + 2.0 * TD / T0);
        q[2] = K * (TD / T0);
    }
    return q;
}

} 


PID::PID(double K, double T, double TD, double T0)
    : q0(compute_q_values(K, T, TD, T0)[0]),
      q1(compute_q_values(K, T, TD, T0)[1]),
      q2(compute_q_values(K, T, TD, T0)[2])
{
   
}


PID::PID(DiscreteTag, double q0_, double q1_, double q2_, double u0)
    : q0(q0_), q1(q1_), q2(q2_), u_prev(u0)
{
    
}

void PID::reset(double u0) {
    u_prev = u0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}

double PID::update(double e) {
    double delta = q0 * e + q1 * e_prev1 + q2 * e_prev2;
    double u = u_prev + delta;

    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev  = u;

    return u;
}
