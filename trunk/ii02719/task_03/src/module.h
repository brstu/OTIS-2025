/**
 * @file module.h
 * @brief Заголовочный файл модуля управления ПИД-регулятором
 * @author Соловчук И.Г.
 * @version 1.0
 * @date 2025
 * 
 * @copyright Copyright (c) 2025
 * 
 * @defgroup PID_Module Модуль ПИД-регулятора
 * @brief Функции для реализации дискретного ПИД-регулятора
 * 
 * @defgroup Model_Module Модуль модели объекта
 * @brief Функции для моделирования нелинейного объекта
 * 
 * @defgroup Utility_Module Вспомогательные функции
 * @brief Вспомогательные функции для работы системы
 */

#ifndef PID_MODULE_H
#define PID_MODULE_H

#include <array>

/**
 * @brief Пространство имен для систем управления
 */
namespace ControlSystem {

/**
 * @struct ControlParams
 * @brief Структура параметров для расчета управления ПИД-регулятором
 * @ingroup PID_Module
 */
struct ControlParams {
    double q0;      ///< Пропорциональный коэффициент дискретного регулятора
    double q1;      ///< Интегральный коэффициент дискретного регулятора
    double q2;      ///< Дифференциальный коэффициент дискретного регулятора
    double e_k;     ///< Ошибка регулирования на текущем шаге
    double e_prev;  ///< Ошибка регулирования на предыдущем шаге
    double e_prev2; ///< Ошибка регулирования на предпредыдущем шаге
    double u_prev;  ///< Управляющее воздействие на предыдущем шаге
};

/**
 * @struct ModelParams
 * @brief Структура параметров нелинейной модели объекта
 * @ingroup Model_Module
 */
struct ModelParams {
    double a;       ///< Коэффициент линейной части модели
    double b;       ///< Коэффициент нелинейной квадратичной части
    double c;       ///< Коэффициент управления
    double d;       ///< Коэффициент нелинейной синусоидальной части
    double y1;      ///< Выход объекта на шаге k-1
    double y0;      ///< Выход объекта на шаге k-2
    double u1;      ///< Управление на шаге k-1
    double u0;      ///< Управление на шаге k-2
};

/**
 * @struct StateVariables
 * @brief Структура переменных состояния системы
 * @ingroup Utility_Module
 */
struct StateVariables {
    std::array<double, 3> y;    ///< История температур: [y(k), y(k-1), y(k-2)]
    std::array<double, 2> u;    ///< История управлений: [u(k), u(k-1)]
    double e_prev;              ///< Предыдущая ошибка e(k-1)
    double e_prev2;             ///< Пред-предыдущая ошибка e(k-2)
    double u_prev;              ///< Предыдущее управление u(k-1)
    double e_k;                 ///< Текущая ошибка e(k)
};

/**
 * @brief Вычисляет коэффициенты дискретного ПИД-регулятора
 * @param K Коэффициент усиления регулятора
 * @param T Постоянная времени интегрирования
 * @param Td Постоянная времени дифференцирования
 * @param T0 Время дискретизации системы
 * @param[out] q0 Рассчитанный коэффициент q0
 * @param[out] q1 Рассчитанный коэффициент q1
 * @param[out] q2 Рассчитанный коэффициент q2
 * @ingroup PID_Module
 * 
 * @details Формулы расчета:
 * q0 = K * (1 + Td/T0)
 * q1 = -K * (1 + 2*Td/T0 - T0/T)
 * q2 = K * Td/T0
 */
void calculatePidCoefficients(double K, double T, double Td, double T0,
                             double& q0, double& q1, double& q2);

/**
 * @brief Вычисляет управляющее воздействие ПИД-регулятора
 * @param params Параметры для расчета управления
 * @return Управляющее воздействие на текущем шаге
 * @ingroup PID_Module
 * 
 * @note Формула расчета: u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 * @warning Результат ограничивается функцией applyControlLimits
 */
double calculateControl(const ControlParams& params);

/**
 * @brief Применяет ограничения к управляющему воздействию
 * @param control Сигнал управления
 * @return Ограниченный сигнал управления
 * @ingroup PID_Module
 * 
 * @details Ограничения: 0% ≤ control ≤ 100%
 */
double applyControlLimits(double control);

/**
 * @brief Моделирует нелинейный объект управления
 * @param params Параметры модели объекта
 * @return Новое значение температуры объекта
 * @ingroup Model_Module
 * 
 * @details Модель: y(k) = a*y(k-1) - b*y(k-2)² + c*u(k-1) + d*sin(u(k-2))
 */
double calculateNonlinearModel(const ModelParams& params);

/**
 * @brief Защита от отрицательных значений температуры
 * @param temperature Рассчитанное значение температуры
 * @return Скорректированная температура
 * @ingroup Utility_Module
 * 
 * @details Обеспечивает физическую корректность модели
 */
double applyTemperatureProtection(double temperature);

/**
 * @brief Вычисляет ошибку регулирования
 * @param setpoint Заданное значение
 * @param current_value Текущее значение
 * @return Ошибка регулирования
 * @ingroup Utility_Module
 */
double calculateError(double setpoint, double current_value);

/**
 * @brief Обновляет переменные состояния системы
 * @param[in,out] state Переменные состояния для обновления
 * @ingroup Utility_Module
 * 
 * @details Сдвигает массивы истории для подготовки к следующему шагу
 */
void updateStateVariables(StateVariables& state);

} // namespace ControlSystem

// Псевдонимы для удобства использования
using ControlParams = ControlSystem::ControlParams;
using ModelParams = ControlSystem::ModelParams;
using StateVariables = ControlSystem::StateVariables;
using ControlSystem::calculatePidCoefficients;
using ControlSystem::calculateControl;
using ControlSystem::applyControlLimits;
using ControlSystem::calculateNonlinearModel;
using ControlSystem::applyTemperatureProtection;
using ControlSystem::calculateError;
using ControlSystem::updateStateVariables;

#endif // PID_MODULE_H