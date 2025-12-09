#include "pid.h"
#include <iostream>
#include <vector>
#include <cmath>

PID::PID(double K_val, double Ti_val, double Td_val, double T0_val)
    : K(K_val), Ti(Ti_val), Td(Td_val), T0(T0_val) {
    
    if (T0 <= 0) T0 = 1.0;
    if (Ti <= 0) Ti = 1.0;
    
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / Ti);
    q2 = K * Td / T0;
    
    std::cout << "PID created: K=" << K << ", Ti=" << Ti 
              << ", Td=" << Td << ", T0=" << T0 << std::endl;
    std::cout << "Coefficients: q0=" << q0 << ", q1=" << q1 << ", q2=" << q2 << std::endl;
}

double PID::calculate(double setpoint, double current_value) {
    double error = setpoint - current_value;
    
    double delta_u = q0 * error + q1 * e_prev1 + q2 * e_prev2;
    double u = u_prev + delta_u;
    
    if (u > 100.0) u = 100.0;
    if (u < 0.0) u = 0.0;
    
    e_prev2 = e_prev1;
    e_prev1 = error;
    u_prev = u;
    
    return u;
}

void PID::reset() {
    e_prev1 = 0.0;
    e_prev2 = 0.0;
    u_prev = 0.0;
    integral = 0.0;
    d_prev = 0.0;
}

std::vector<double> PID::getCoefficients() const {
    return std::vector<double>{q0, q1, q2};
}

void PID::getParameters(double& K_param, double& Ti_param, double& Td_param) const {
    K_param = K;
    Ti_param = Ti;
    Td_param = Td;
}