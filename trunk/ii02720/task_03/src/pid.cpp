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
    // Проверка корректности времени квантования
    if (samplingT0 <= 0) {
        throw std::invalid_argument("Шаг квантования T0 должен быть положительным числом");
    }
    
    // Сохраняем параметры регулятора
    this->K = gainK;
    this->T = integralT;
    this->Td = derivativeTd;
    this->T0 = samplingT0;
    
    // Вычисление коэффициентов рекуррентного алгоритма ПИД
    // q0 = K * (1 + Td/T0)
    // q1 = -K * (1 + 2*Td/T0 - T0/T)
    // q2 = K * Td/T0
    this->q0 = gainK * (1.0 + derivativeTd / samplingT0);
    this->q1 = -gainK * (1.0 + 2.0 * derivativeTd / samplingT0 - samplingT0 / integralT);
    this->q2 = gainK * derivativeTd / samplingT0;
    
    // Инициализация буфера ошибок e(k-1) и e(k-2)
    prev_error = std::vector<double>(2, 0.0);
    prev_output = 0.0;
}

double PIDController::calculate(double targetSetpoint, double measuredValue) {
    // Вычисление текущей ошибки регулирования
    double currentError = targetSetpoint - measuredValue;
    
    // Рекуррентный алгоритм: u(k) = u(k-1) + delta_u
    // delta_u = q0*e(k) + q1*e(k-1) + q2*e(k-2)
    double deltaControl = q0 * currentError + q1 * prev_error[0] + q2 * prev_error[1];
    double controlOutput = prev_output + deltaControl;
    
    // Обновление буфера ошибок (сдвиг)
    prev_error[1] = prev_error[0];  // e(k-2) = e(k-1)
    prev_error[0] = currentError;    // e(k-1) = e(k)
    prev_output = controlOutput;
    
    return controlOutput;
}

void PIDController::reset() {
    // Сброс состояния регулятора в начальное
    prev_error[0] = 0.0;
    prev_error[1] = 0.0;
    prev_output = 0.0;
}

std::vector<double> PIDController::getCoefficients() const {
    // Возврат вектора коэффициентов [q0, q1, q2]
    return {q0, q1, q2};
}

// Дополнительный метод для получения параметров регулятора (Степанюк И.С.)
std::vector<double> PIDController::getParameters() const {
    return {K, T, Td, T0};
}
