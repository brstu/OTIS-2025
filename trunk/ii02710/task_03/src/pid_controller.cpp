/**
 * @file pid_controller.cpp
 * @brief Реализация методов класса PID-регулятора
 */

#include "pid_controller.h"
#include <algorithm>

 /**
  * @brief Конструктор PID-регулятора
  * @param p Пропорциональный коэффициент
  * @param i Интегральный коэффициент
  * @param d Дифференциальный коэффициент
  * @param min Минимальное значение выходного сигнала
  * @param max Максимальное значение выходного сигнала
  */
PIDController::PIDController(double p, double i, double d, double min, double max)
    : Kp(p), Ki(i), Kd(d), output_min(min), output_max(max) {
    setpoint = 0;
    integral = 0;
    prev_error = 0;
}

/**
 * @brief Вычисляет выходной сигнал ПИД-регулятора
 * @param measured_value Измеренное значение температуры
 * @param dt Временной интервал (шаг) в секундах
 * @return Управляющее воздействие
 */
double PIDController::calculate(double measured_value, double dt) {
    // Вычисление ошибки
    double error = setpoint - measured_value;

    // Пропорциональная составляющая
    double proportional = Kp * error;

    // Интегральная составляющая
    integral += error * dt;
    double integral_term = Ki * integral;

    // Дифференциальная составляющая
    double derivative = 0;
    if (dt > 0) {
        derivative = (error - prev_error) / dt;
    }
    double derivative_term = Kd * derivative;

    // Вычисление выходного сигнала
    double output = proportional + integral_term + derivative_term;

    // Ограничение выходного сигнала
    output = std::clamp(output, output_min, output_max);

    // Обновление предыдущей ошибки
    prev_error = error;

    return output;
}

/**
 * @brief Устанавливает заданное значение температуры
 * @param value Новое заданное значение
 */
void PIDController::setSetpoint(double value) {
    setpoint = value;
}

/**
 * @brief Получает текущее заданное значение
 * @return Заданное значение температуры
 */
double PIDController::getSetpoint() const {
    return setpoint;
}

/**
 * @brief Сбрасывает интегральную составляющую и предыдущую ошибку
 */
void PIDController::reset() {
    integral = 0;
    prev_error = 0;
}

/**
 * @brief Устанавливает новые коэффициенты ПИД-регулятора
 * @param p Новый пропорциональный коэффициент
 * @param i Новый интегральный коэффициент
 * @param d Новый дифференциальный коэффициент
 */
void PIDController::setParameters(double p, double i, double d) {
    Kp = p;
    Ki = i;
    Kd = d;
}