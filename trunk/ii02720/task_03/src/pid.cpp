/**
 * @file pid.cpp
 * @brief Реализация методов класса дискретного ПИД-регулятора
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Модуль содержит реализацию рекуррентного алгоритма ПИД-регулятора
 * для системы автоматического управления тепловым объектом.
 */

#include "pid.h"
#include <stdexcept>
#include <vector>

PIDController::PIDController(double gainK, double integralT, double derivativeTd, double samplingT0) {

    if (samplingT0 <= 0) {
        throw std::invalid_argument("Шаг квантования T0 должен быть положительным числом");
    }
    

    this->K = gainK;
    this->T = integralT;
    this->Td = derivativeTd;
    this->T0 = samplingT0;
    

    this->q0 = gainK * (1.0 + derivativeTd / samplingT0);
    this->q1 = -gainK * (1.0 + 2.0 * derivativeTd / samplingT0 - samplingT0 / integralT);
    this->q2 = gainK * derivativeTd / samplingT0;
    

    prev_error = std::vector<double>(2, 0.0);
    prev_output = 0.0;
}

double PIDController::calculate(double targetSetpoint, double measuredValue) {

    double currentError = targetSetpoint - measuredValue;
    


    double deltaControl = q0 * currentError + q1 * prev_error[0] + q2 * prev_error[1];
    double controlOutput = prev_output + deltaControl;
    

    prev_error[1] = prev_error[0];
    prev_error[0] = currentError;
    prev_output = controlOutput;
    
    return controlOutput;
}

void PIDController::reset() {

    prev_error[0] = 0.0;
    prev_error[1] = 0.0;
    prev_output = 0.0;
}

std::vector<double> PIDController::getCoefficients() const {

    return {q0, q1, q2};
}


std::vector<double> PIDController::getParameters() const {
    return {K, T, Td, T0};
}
