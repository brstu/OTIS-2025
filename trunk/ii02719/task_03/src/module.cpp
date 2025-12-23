/**
 * @file module.cpp
 * @brief Реализация функций модуля ПИД-регулятора
 * @author Соловчук И.Г.
 * @version 1.0
 * @date 2025
 * 
 * @copyright Copyright (c) 2025
 * 
 * @details Этот файл содержит реализации всех функций,
 * объявленных в module.h, включая алгоритмы ПИД-регулирования
 * и моделирования нелинейного объекта.
 */

#include "module.h"
#include <cmath>
#include <algorithm>

namespace ControlSystem {

/**
 * @brief Вычисляет коэффициенты дискретного ПИД-регулятора
 * 
 * @param K Коэффициент усиления регулятора
 * @param T Постоянная времени интегрирования
 * @param Td Постоянная времени дифференцирования
 * @param T0 Время дискретизации системы
 * @param[out] q0 Рассчитанный коэффициент q0
 * @param[out] q1 Рассчитанный коэффициент q1
 * @param[out] q2 Рассчитанный коэффициент q2
 * 
 * @note Используется метод тустеновской аппроксимации
 */
void calculatePidCoefficients(double K, double T, double Td, double T0,
                             double& q0, double& q1, double& q2) {
    // Проверка корректности входных параметров
    if (T0 <= 0.0) {
        T0 = 1.0; // Значение по умолчанию при некорректном вводе
    }
    
    if (T <= 0.0) {
        T = 1.0; // Защита от деления на ноль
    }

    // Расчет коэффициентов дискретного ПИД-регулятора
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + (2.0 * Td / T0) - (T0 / T));
    q2 = K * Td / T0;
}

/**
 * @brief Вычисляет управляющее воздействие ПИД-регулятора
 * 
 * @param params Структура с параметрами управления
 * @return Управляющее воздействие на текущем шаге
 * 
 * @details Реализует разностное уравнение ПИД-регулятора
 * с последующим ограничением выходного сигнала.
 */
double calculateControl(const ControlParams& params) {
    // Расчет приращения управления по разностной схеме
    double control_increment = params.q0 * params.e_k +
                              params.q1 * params.e_prev +
                              params.q2 * params.e_prev2;
    
    // Новое значение управления
    double new_control = params.u_prev + control_increment;
    
    // Применение ограничений к управлению
    return applyControlLimits(new_control);
}

/**
 * @brief Применяет ограничения к управляющему воздействию
 * 
 * @param control Рассчитанное управляющее воздействие
 * @return Ограниченное управляющее воздействие
 * 
 * @details Ограничения моделируют физические пределы
 * исполнительного механизма системы.
 */
double applyControlLimits(double control) {
    // Ограничение снизу (минимальное управление)
    if (control < 0.0) {
        return 0.0;
    }
    
    // Ограничение сверху (максимальное управление)
    if (control > 100.0) {
        return 100.0;
    }
    
    // Если значение в допустимом диапазоне, возвращаем его
    return control;
}

/**
 * @brief Моделирует нелинейный объект управления
 * 
 * @param params Параметры модели объекта
 * @return Новое значение выхода объекта
 * 
 * @details Модель включает линейные и нелинейные компоненты,
 * что позволяет более точно описывать реальные объекты.
 */
double calculateNonlinearModel(const ModelParams& params) {
    // Расчет линейной составляющей
    double linear_component = params.a * params.y1;
    
    // Расчет квадратичной нелинейности
    double quadratic_component = params.b * params.y0 * params.y0;
    
    // Расчет компоненты управления
    double control_component = params.c * params.u1;
    
    // Расчет синусоидальной нелинейности
    double nonlinear_component = params.d * std::sin(params.u0);
    
    // Суммирование всех компонент
    double output = linear_component - quadratic_component +
                    control_component + nonlinear_component;
    
    // Защита от физически некорректных значений
    return applyTemperatureProtection(output);
}

/**
 * @brief Защита от отрицательных значений температуры
 * 
 * @param temperature Рассчитанное значение температуры
 * @return Скорректированное значение температуры
 * 
 * @details Обеспечивает соответствие модели физическим законам.
 */
double applyTemperatureProtection(double temperature) {
    // Температура не может быть отрицательной (по шкале Кельвина или Цельсия)
    if (temperature < 0.0) {
        return 0.0;
    }
    
    return temperature;
}

/**
 * @brief Вычисляет ошибку регулирования
 * 
 * @param setpoint Заданное значение (уставка)
 * @param current_value Текущее измеренное значение
 * @return Ошибка регулирования
 * 
 * @details Положительная ошибка означает, что текущее значение
 * ниже уставки, отрицательная - выше уставки.
 */
double calculateError(double setpoint, double current_value) {
    return setpoint - current_value;
}

/**
 * @brief Обновляет переменные состояния системы
 * 
 * @param[in,out] state Переменные состояния для обновления
 * 
 * @details Выполняет сдвиг массивов истории и обновление
 * переменных для подготовки к следующему шагу расчета.
 */
void updateStateVariables(StateVariables& state) {
    // Сохранение текущей ошибки как предыдущей для следующего шага
    state.e_prev2 = state.e_prev;
    state.e_prev = state.e_k;
    
    // Сохранение текущего управления как предыдущего
    state.u_prev = state.u[0];
    
    // Сдвиг массива истории температур:
    // Новая позиция 0 ← старая позиция 1
    // Новая позиция 1 ← старая позиция 2
    double temp_y0 = state.y[0];
    double temp_y1 = state.y[1];
    double temp_y2 = state.y[2];
    
    state.y[0] = temp_y1; // y(k) ← y(k-1)
    state.y[1] = temp_y2; // y(k-1) ← y(k-2)
    // Позиция y[2] будет заполнена на следующем шаге
    
    // Сдвиг массива истории управлений
    state.u[1] = state.u[0]; // u(k-1) ← u(k)
    // Позиция u[0] будет заполнена на следующем шаге
}

} // namespace ControlSystem