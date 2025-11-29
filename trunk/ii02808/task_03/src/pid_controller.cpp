/**
 * @file pid_controller.cpp
 * @brief Реализация методов класса ПИД-регулятора
 */

#include "pid_controller.h"
#include <stdexcept>

PIDController::PIDController(double K, double T, double Td, double T0) {
    if (T0 <= 0) {
        throw std::invalid_argument("Время квантования должно быть положительным");
    }
    
    this->K = K;
    this->T = T;
    this->Td = Td;
    this->T0 = T0;
    
    // Вычисляем коэффициенты по формулам из задания
    this->q0 = K * (1 + Td / T0);
    this->q1 = -K * (1 + 2 * Td / T0 - T0 / T);
    this->q2 = K * Td / T0;
    
    // Инициализируем предыдущие значения
    reset();
}

double PIDController::calculate(double setpoint, double current_value) {
    double error = setpoint - current_value;
    
    // Вычисляем приращение управления по рекуррентной формуле
    double delta_u = q0 * error + q1 * prev_error[0] + q2 * prev_error[1];
    
    // Вычисляем текущее управляющее воздействие
    double output = prev_output + delta_u;
    
    // Обновляем предыдущие значения
    prev_error[1] = prev_error[0];
    prev_error[0] = error;
    prev_output = output;
    
    return output;
}

void PIDController::reset() {
    prev_error[0] = 0.0;
    prev_error[1] = 0.0;
    prev_output = 0.0;
}

std::vector<double> PIDController::getCoefficients() const {
    return {q0, q1, q2};
}