#include "pid.h"
#include <iostream>
#include <vector>
#include <cmath>

/**
 * @brief Конструктор ПИД-регулятора
 */
PID::PID(double K_val, double Ti_val, double Td_val, double T0_val)
    : K(K_val), Ti(Ti_val), Td(Td_val), T0(T0_val),
      e_prev1(0.0), e_prev2(0.0), u_prev(0.0),
      integral(0.0), d_prev(0.0) {
    
    if (T0 <= 0) T0 = 1.0;
    if (Ti <= 0) Ti = 1.0;
    
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / Ti);
    q2 = K * Td / T0;
}

/**
 * @brief Вычисление управляющего воздействия
 */
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

/**
 * @brief Сброс состояния регулятора
 */
void PID::reset() {
    e_prev1 = 0.0;
    e_prev2 = 0.0;
    u_prev = 0.0;
    integral = 0.0;
    d_prev = 0.0;
}

/**
 * @brief Получение коэффициентов рекуррентного алгоритма
 */
std::vector<double> PID::getCoefficients() const {
    return std::vector<double>{q0, q1, q2};
}

/**
 * @brief Получение параметров ПИД-регулятора
 */
void PID::getParameters(double& K_param, double& Ti_param, double& Td_param) const {
    K_param = K;
    Ti_param = Ti;
    Td_param = Td;
}