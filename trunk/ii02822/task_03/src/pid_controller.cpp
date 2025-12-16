#include "pid_controller.h"
#include <cmath>
#include <limits>

PIDController::PIDController(double K, double Ti, double Td, double T)
    : K(K), Ti(Ti), Td(Td), T(T), u_prev(0.0), e_prev1(0.0), e_prev2(0.0) {
    calculateCoefficients();
}

void PIDController::calculateCoefficients() {
    double safe_T = (T == 0.0) ? 0.01 : T;
    double safe_Ti = Ti;

    if (Ti == 0.0) {
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
    double e = setpoint - current_value;
    double u = u_prev + q0 * e + q1 * e_prev1 + q2 * e_prev2;

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

void PIDController::setParameters(double K, double Ti, double Td, double T) {
    this->K = K;
    this->Ti = Ti;
    this->Td = Td;
    this->T = T;
    calculateCoefficients();
    reset();
}

void PIDController::getParameters(double& K, double& Ti, double& Td, double& T) const {
    K = this->K;
    Ti = this->Ti;
    Td = this->Td;
    T = this->T;
}