#pragma once
#include "nonlinear.h"

/**
 * @brief Моделирование ПИД-регулятора для нелинейной системы
 * 
 * Функция реализует дискретный ПИД-регулятор, управляющий нелинейной системой:
 * - Пропорциональная составляющая (P): Kp * error
 * - Интегральная составляющая (I): Ki * Σ(error * dt)
 * - Дифференциальная составляющая (D): Kd * Δerror / dt
 * 
 * Управляемая система описывается уравнением:
 * y(t) = a*y(t-1) - b*y(t-2)^2 + c*u_pid + d*sin(u_pid)
 * где u_pid - выходное воздействие ПИД-регулятора
 * 
 * @param coeff Коэффициенты нелинейной модели
 * @param y0 Начальное значение выходной переменной y(0)
 * @param n Количество шагов моделирования
 * @param setpoint Заданное значение (желаемое значение выходной переменной)
 * @param Kp Коэффициент пропорциональной составляющей (по умолчанию 1.0)
 * @param Ki Коэффициент интегральной составляющей (по умолчанию 0.1)
 * @param Kd Коэффициент дифференциальной составляющей (по умолчанию 0.01)
 * @param dt Временной шаг дискретизации (по умолчанию 1.0)
 * @return std::vector<double> Вектор значений выходной переменной y на каждом шаге
 * 
 * @note Используется дискретная форма ПИД-регулятора с прямой формулой:
 * u(t) = Kp*e(t) + Ki*Σe(t)*dt + Kd*(e(t)-e(t-1))/dt
 * 
 * @warning Для устойчивой работы системы коэффициенты Kp, Ki, Kd должны быть
 * тщательно подобраны. Неправильные коэффициенты могут привести к расходимости
 * 
 * @see Для настройки коэффициентов рекомендуется использовать методы:
 * - Метод Циглера-Николса
 * - Метод проб и ошибок
 * - Автоматическая настройка
 * 
 * @example
 * NonLinearCoeff coeff = {0.5, 0.2, 0.15, 0.3, 1.2};
 * // Базовый ПИД с коэффициентами по умолчанию
 * auto results1 = simulatePidRegulatorForNonlinear(coeff, 1.0, 10, 2.0);
 * 
 * // ПИД с пользовательскими коэффициентами
 * auto results2 = simulatePidRegulatorForNonlinear(coeff, 1.0, 10, 2.0, 1.5, 0.2, 0.05);
 */
std::vector<double> simulatePidRegulatorForNonlinear(
    const NonLinearCoeff &coeff, 
    double y0, 
    int n, 
    double setpoint,
    double Kp = 1.0,
    double Ki = 0.1,
    double Kd = 0.01,
    double dt = 1.0)
{
    std::vector<double> results;
    std::vector<double> controlSignals;
    
    double y_prev_prev = y0;
    double y_prev = y0;
    double y_current = y0;
    
    double integral = 0.0;
    double prev_error = 0.0;
    double u_pid = coeff.u;
    
    for (int i = 0; i < n; i++)
    {
        double error = setpoint - y_current;
        double P = Kp * error;
        integral += error * dt;
        double I = Ki * integral;
        double derivative = (error - prev_error) / dt;
        double D = Kd * derivative;
        u_pid = P + I + D;
        prev_error = error;
        double y_next = coeff.a * y_current - coeff.b * y_prev * y_prev 
                      + coeff.c * u_pid + coeff.d * sin(u_pid);
        
        results.push_back(y_current);
        controlSignals.push_back(u_pid);

        y_prev_prev = y_prev;
        y_prev = y_current;
        y_current = y_next;
    }
    return results;
}