/**
 * @file process_model.cpp
 * @brief Реализация методов класса динамической системы
 */

#include "process_model.h"
#include <stdexcept>

DynamicSystem::DynamicSystem(const std::vector<double>& system_coefficients, double initial_state) {
    if (system_coefficients.size() < 4) {
        throw std::invalid_argument("Недостаточное количество параметров модели");
    }
    this->system_coefficients = system_coefficients;
    this->internal_state = initial_state;
}

double DynamicSystem::evaluateLinear(double control_input) {
    
    double system_output = system_coefficients[0] * internal_state 
                         + system_coefficients[1] * control_input;
    
    internal_state = system_output;
    return system_output;
}

double DynamicSystem::evaluateNonlinear(double control_input) {
   
    double nonlinear_component = system_coefficients[0] * internal_state 
                               - system_coefficients[1] * internal_state * internal_state 
                               + system_coefficients[2] * control_input 
                               + system_coefficients[3] * std::cos(control_input);
    
    internal_state = nonlinear_component;
    return nonlinear_component;
}

void DynamicSystem::initializeState(double initial_value) {
    internal_state = initial_value;
}