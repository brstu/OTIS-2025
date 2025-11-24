/**
 * @file pid.cpp
 * @brief Реализация методов PID-регулятора
 */

#include "pid_contr.h"

PID::PID(double q0, double q1, double q2) 
    : q0(q0),
      q1(q1),
      q2(q2) {
}

PID::PID(double K, double Ti, double Td, double T0) 
    : q0(K * (1.0 + T0/Ti + Td/T0)),
      q1(-K * (1.0 + 2.0*Td/T0 - T0/Ti)),
      q2(K * Td/T0) {
}

double PID::compute(double e) {
    double delta_u = q0 * e + q1 * e_prev1 + q2 * e_prev2;
    
    double u = u_prev + delta_u;
    
    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;
    
    return u;
}

void PID::reset() {
    u_prev = 0.0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}