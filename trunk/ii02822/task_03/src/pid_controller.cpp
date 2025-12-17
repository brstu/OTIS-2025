#include "pid_controller.h"
#include <cmath>
#include <algorithm>

PIDController::PIDController(double K_val, double Ti_val, double Td_val, double T_val)
    : K(K_val), Ti(Ti_val), Td(Td_val), T(T_val) {
    calculateCoefficients();
}

void PIDController::calculateCoefficients() {
    const double safe_T = (std::fabs(T) < 1e-10) ? 0.01 : T;

    if (std::fabs(Ti) < 1e-10) {
        q0 = K * (1.0 + Td / safe_T);
        q1 = -K * (1.0 + 2.0 * Td / safe_T);
        q2 = K * Td / safe_T;
    }
    else {
        q0 = K * (1.0 + safe_T / Ti + Td / safe_T);
        q1 = -K * (1.0 + 2.0 * Td / safe_T);
        q2 = K * Td / safe_T;
    }
}

double PIDController::calculate(double setpoint, double current_value) {
    const double e = setpoint - current_value;
    const double u = u_prev + q0 * e + q1 * e_prev1 + q2 * e_prev2;

    e_prev2 = e_prev1;
    e_prev1 = e;
    u_prev = u;

    return u;
}

void PIDController::reset() {
    u_prev = 0.0;
    e_prev1 = 0.0;
    e_prev2 = 0.0;
}

void PIDController::setParameters(double new_K, double new_Ti, double new_Td, double new_T) {

    K = new_K;
    Ti = new_Ti;
    Td = new_Td;
    T = new_T;
    calculateCoefficients();
    reset();
}

void PIDController::getParameters(double& out_K, double& out_Ti, double& out_Td, double& out_T) const {
    out_K = K;
    out_Ti = Ti;
    out_Td = Td;
    out_T = T;
}