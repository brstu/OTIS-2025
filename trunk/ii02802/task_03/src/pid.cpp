#include "pid.h"

/** @file pid.cpp
 * @brief Реализация класса ПИД-регулятора.
 */

PID::PID(double K, double Ti, double Td, double Ts) {
    q0 = K * (1.0 + Ts / Ti + Td / Ts);
    q1 = -K * (1.0 + 2.0 * Td / Ts);
    q2 = K * Td / Ts;
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