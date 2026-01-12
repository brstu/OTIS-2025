#include "pid.h"
#include <stdexcept>

PIDRegulator::PIDRegulator(double P, double I, double D, double Ts) {
    if (Ts <= 0) throw std::invalid_argument("Invalid sampling time");
    
    gains = {P, I, D, Ts};
    memory = {0.0, 0.0, 0.0};
    computeCoeffs();
}

void PIDRegulator::computeCoeffs() {
    double& K = gains.P;
    double& Ti = gains.I;
    double& Td = gains.D;
    double& T0 = gains.Ts;
    
    coeffs.a0 = K * (1.0 + Td / T0);
    coeffs.a1 = -K * (1.0 + 2.0 * Td / T0 - T0 / Ti);
    coeffs.a2 = K * Td / T0;
}

double PIDRegulator::update(double target, double measurement) {
    double error = target - measurement;
    
    double delta = coeffs.a0 * error 
                 + coeffs.a1 * memory.ek1 
                 + coeffs.a2 * memory.ek2;
    
    double output = memory.uk1 + delta;
    
    memory.ek2 = memory.ek1;
    memory.ek1 = error;
    memory.uk1 = output;
    
    return output;
}

void PIDRegulator::clear() {
    memory = {0.0, 0.0, 0.0};
}

std::array<double, 3> PIDRegulator::getCoeffs() const {
    return {coeffs.a0, coeffs.a1, coeffs.a2};
}