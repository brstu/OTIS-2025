/**
 * @file module.cpp
 * @brief Реализация функций ПИД-регулятора и модели объекта
 * @author Соловчук И.Г. ИИ-27
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
выфвыф
/**
 * @brief Расчет управляющего воздействия ПИД-регулятором
 */
double calculateControl(double q0, double q1, double q2,
                       double e_k, double e_prev, double e_prev2, 
                       double u_prev) {
    double delta_u = q0 * e_k + q1 * e_prev + q2 * e_prev2;
    double u_k = u_prev + delta_u;
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
double calculateNonlinearModel(double a, double b, double c, double d,
                             double y1, double y0, double u1, double u0) {
    double y2 = a * y1 - b * y0 * y0 + c * u1 + d * sin(u0);
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
void updateStateVariables(double y[], double u[], 
                         double& e_prev, double& e_prev2, double& u_prev,
                         double e_k) {
    // Обновление истории температур (y[2] - старейшее, y[0] - новейшее)
    y[2] = y[1];  // y(k-2) ← y(k-1)
    y[1] = y[0];  // y(k-1) ← y(k)
    
    // Обновление истории управлений
    u[2] = u[1];  // u(k-2) ← u(k-1)
    u[1] = u[0];  // u(k-1) ← u(k)
    
    // Обновление переменных ПИД-регулятора
    e_prev2 = e_prev;  // e(k-2) ← e(k-1)
    e_prev = e_k;      // e(k-1) ← e(k)
    u_prev = u[0];     // u(k-1) ← u(k)
}