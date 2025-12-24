/**
 * @file pid_controller.cpp
 * @brief Реализация методов класса цифрового ПИД-регулятора
 */

#include "pid_controller.h"
#include <stdexcept>
#include <vector>

PIDRegulator::PIDRegulator(double gain_factor, double integration_const, 
                         double differentiation_const, double discretization_step) {
    if (discretization_step <= 0) {
        throw std::invalid_argument("Шаг дискретизации должен иметь положительное значение");
    }
    
    this->gain_factor = gain_factor;
    this->integration_const = integration_const;
    this->differentiation_const = differentiation_const;
    this->discretization_step = discretization_step;
    
    double Td_over_T0 = differentiation_const / discretization_step;
    double T0_over_T = discretization_step / integration_const;
    
    this->coeff_alpha = gain_factor * (1.0 + Td_over_T0);
    this->coeff_beta = -gain_factor * (1.0 + 2.0 * Td_over_T0 - T0_over_T);
    this->coeff_gamma = gain_factor * Td_over_T0;
    
    
    history_errors = std::vector<double>(2, 0.0);
    previous_control = 0.0;
}

double PIDRegulator::computeControl(double target_value, double measured_value) {
    double current_error = target_value - measured_value;
    
    
    double control_increment = coeff_alpha * current_error 
                             + coeff_beta * history_errors[0] 
                             + coeff_gamma * history_errors[1];
    
    double current_control = previous_control + control_increment;
    
    history_errors[1] = history_errors[0];
    history_errors[0] = current_error;
    previous_control = current_control;
    
    return current_control;
}

void PIDRegulator::clearState() {
    history_errors[0] = 0.0;
    history_errors[1] = 0.0;
    previous_control = 0.0;
}

std::vector<double> PIDRegulator::obtainCoefficients() const {
    return {coeff_alpha, coeff_beta, coeff_gamma};
}