/**
 * @file    pid.cpp
 * @brief   Реализация класса PID
 * @details Содержит реализацию цифрового ПИД-регулятора
 * @author  Vladimir
 * @date    2025-12-09
 * @version 1.0
 */

#include "pid.h"
#include <iostream>
#include <vector>
#include <cmath>

/**
 * @brief Конструктор класса PID
 * @param K_val Коэффициент усиления
 * @param Ti_val Постоянная времени интегрирования
 * @param Td_val Постоянная времени дифференцирования
 * @param T0_val Период дискретизации
 * 
 * Рассчитывает коэффициенты дискретного регулятора по формулам:
 * q0 = K*(1 + Td/T0)
 * q1 = -K*(1 + 2*Td/T0 - T0/Ti)
 * q2 = K*Td/T0
 */
PID::PID(double K_val, double Ti_val, double Td_val, double T0_val)
    : K(K_val), Ti(Ti_val), Td(Td_val), T0(T0_val) {
    
    // Проверка корректности параметров
    if (T0 <= 0) T0 = 1.0;
    if (Ti <= 0) Ti = 1.0;
    
    // Расчет коэффициентов дискретного регулятора
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / Ti);
    q2 = K * Td / T0;
    
    // Вывод информации для отладки
    std::cout << "PID created: K=" << K << ", Ti=" << Ti 
              << ", Td=" << Td << ", T0=" << T0 << std::endl;
    std::cout << "Coefficients: q0=" << q0 << ", q1=" << q1 << ", q2=" << q2 << std::endl;
}

/**
 * @brief Расчет управляющего воздействия
 * @param setpoint Задающее воздействие
 * @param current_value Текущее значение процесса
 * @return Управляющее воздействие (ограниченное 0-100%)
 * 
 * Алгоритм расчета:
 * 1. Вычисление ошибки: e[k] = setpoint - current_value
 * 2. Расчет приращения: Δu = q0*e[k] + q1*e[k-1] + q2*e[k-2]
 * 3. Новое значение: u[k] = u[k-1] + Δu
 * 4. Ограничение значения
 */
double PID::calculate(double setpoint, double current_value) {
    // Вычисление ошибки регулирования
    double error = setpoint - current_value;
    
    // Расчет приращения управляющего воздействия
    double delta_u = q0 * error + q1 * e_prev1 + q2 * e_prev2;
    double u = u_prev + delta_u;
    
    // Ограничение управляющего воздействия (0-100%)
    if (u > 100.0) u = 100.0;
    if (u < 0.0) u = 0.0;
    
    // Обновление истории
    e_prev2 = e_prev1;
    e_prev1 = error;
    u_prev = u;
    
    return u;
}

/**
 * @brief Сброс состояния регулятора
 * 
 * Обнуляет все внутренние переменные регулятора.
 * Используется при перезапуске системы или изменении режима работы.
 */
void PID::reset() {
    e_prev1 = 0.0;
    e_prev2 = 0.0;
    u_prev = 0.0;
    integral = 0.0;
    d_prev = 0.0;
}

/**
 * @brief Получение коэффициентов дискретного регулятора
 * @return Вектор коэффициентов [q0, q1, q2]
 */
std::vector<double> PID::getCoefficients() const {
    return std::vector<double>{q0, q1, q2};
}

/**
 * @brief Получение параметров ПИД-регулятора
 * @param[out] K_param Коэффициент усиления
 * @param[out] Ti_param Постоянная времени интегрирования
 * @param[out] Td_param Постоянная времени дифференцирования
 */
void PID::getParameters(double& K_param, double& Ti_param, double& Td_param) const {
    K_param = K;
    Ti_param = Ti;
    Td_param = Td;
}