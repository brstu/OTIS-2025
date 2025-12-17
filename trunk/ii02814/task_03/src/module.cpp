/**
 * @file module.cpp
 * @brief Реализация функций ПИД-регулятора и модели объекта
 * @author Козловский Е.Ю. ИИ-28
 * @date 2025
 */

#include "module.h"
#include <cmath>

/**
 * @brief Расчет коэффициентов ПИД-регулятора для дискретной формы
 */
void calculatePidCoefficients(double K, double T, double Td, double T0, 
                             double& q0, double& q1, double& q2) {
    q0 = K * (1 + Td / T0);
    q1 = -K * (1 + 2 * Td / T0 - T0 / T);
    q2 = K * Td / T0;
}

/**
 * @brief Расчет управляющего воздействия ПИД-регулятором
 */
double calculateControl(const ControlParams& params) {
    double delta_u = params.q0 * params.e_k + params.q1 * params.e_prev + params.q2 * params.e_prev2;
    double u_k = params.u_prev + delta_u;
    return applyControlLimits(u_k);
}

/**
 * @brief Применение ограничений к управляющему воздействию
 */
double applyControlLimits(double u) {
    if (u > 100) u = 100;
    if (u < 0) u = 0;
    return u;
}

/**
 * @brief Расчет нелинейной модели объекта управления
 */
double calculateNonlinearModel(const ModelParams& params) {
    double y2 = params.a * params.y1 - params.b * params.y0 * params.y0 + params.c * params.u1 + params.d * sin(params.u0);
    return applyTemperatureProtection(y2);
}

/**
 * @brief Защита от отрицательной температуры
 */
double applyTemperatureProtection(double temperature) {
    if (temperature < 0) temperature = 0;
    return temperature;
}

/**
 * @brief Расчет ошибки регулирования
 */
double calculateError(double setpoint, double current_value) {
    return setpoint - current_value;
}

/**
 * @brief Обновление переменных состояния для следующей итерации
 */
void updateStateVariables(StateVariables& state) {
    // Обновление истории температур (y[2] - старейшее, y[0] - новейшее)
    state.y[0] = state.y[1];  // y(k) ← y(k-1)
    state.y[1] = state.y[2];  // y(k-1) ← y(k)
    
    // Обновление истории управлений
    state.u[0] = state.u[1];  // u(k) ← u(k-1)
    
    // Обновление переменных ПИД-регулятора
    state.e_prev2 = state.e_prev;  // e(k-2) ← e(k-1)
    state.e_prev = state.e_k;      // e(k-1) ← e(k)
    state.u_prev = state.u[1];     // u(k-1) ← u(k)
}