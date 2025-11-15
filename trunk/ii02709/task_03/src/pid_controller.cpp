/**
 * @file pid_controller.cpp
 * @brief Реализация ПИД-регулятора
 */

#include "pid_controller.h"

PIDController::PIDController(double K, double T, double TD, double T0)
    : q0(0.0), q1(0.0), q2(0.0), u_prev(0.0), e_prev1(0.0), e_prev2(0.0)  // ИНИЦИАЛИЗАЦИЯ!
{
    q0 = K * (1.0 + T0 / (2.0 * T) + TD / T0);
    q1 = K * (T0 / T - 2.0 * TD / T0 - 1.0);
    q2 = K * (TD / T0);
}

double PIDController::compute(double error) {
    double u = q0 * error + q1 * e_prev1 + q2 * e_prev2 + u_prev;
    e_prev2 = e_prev1;
    e_prev1 = error;
    u_prev = u;
    return u;
}

void PIDController::reset() {
    u_prev = e_prev1 = e_prev2 = 0.0;
}