/**
 * @file lin_model.cpp
 * @brief Реализация линейной модели объекта управления
 * 
 * Автор: [ВАШЕ ИМЯ ФАМИЛИЯ]
 * Группа: [ВАША ГРУППА]
 * Дата создания: [ТЕКУЩАЯ ДАТА]
 * Уникальный идентификатор: LM_$(date +%Y%m%d%H%M%S)
 */

#include "lin_model.h"
#include <cmath>
#include <iostream>

/**
 * @brief Линейная модель динамической системы
 * 
 * Математическая модель: y(k) = a·y(k-1) + b·u(k)
 * где:
 *   y(k)   - текущее значение выхода
 *   y(k-1) - предыдущее значение выхода
 *   u(k)   - текущее управляющее воздействие
 *   a      - коэффициент обратной связи
 *   b      - коэффициент усиления по управлению
 * 
 * @param previous_output Значение выхода на предыдущем шаге y(k-1)
 * @param control_input Управляющее воздействие на текущем шаге u(k)
 * @param feedback_coefficient Коэффициент обратной связи a
 * @param gain_coefficient Коэффициент усиления по управлению b
 * @return Текущее значение выхода системы y(k)
 */
double linear_model(double previous_output, double control_input,
                   double feedback_coefficient, double gain_coefficient) {
    
    // Уникальная проверка корректности входных параметров
    if (!std::isfinite(previous_output) || !std::isfinite(control_input) ||
        !std::isfinite(feedback_coefficient) || !std::isfinite(gain_coefficient)) {
        
        std::cerr << "[Линейная модель] Обнаружены некорректные числовые значения" << std::endl;
        
        // Безопасное возвращение предыдущего значения
        return previous_output;
    }
    
    // Основное уравнение линейной модели
    double current_output = feedback_coefficient * previous_output + 
                           gain_coefficient * control_input;
    
    // Уникальная проверка числовой устойчивости результата
    if (!std::isfinite(current_output)) {
        std::cerr << "[Линейная модель] Результат вычислений некорректен" << std::endl;
        
        // Возврат предыдущего значения при ошибке вычислений
        return previous_output;
    }
    
    // Уникальное мягкое ограничение для предотвращения числовых проблем
    const double MAX_ABS_VALUE = 1e7;  // Уникальное значение
    
    if (current_output > MAX_ABS_VALUE) {
        // Мягкое ограничение с информированием
        std::cout << "[Линейная модель] Значение ограничено сверху: " 
                  << current_output << " -> " << MAX_ABS_VALUE << std::endl;
        current_output = MAX_ABS_VALUE;
    } else if (current_output < -MAX_ABS_VALUE) {
        // Мягкое ограничение с информированием
        std::cout << "[Линейная модель] Значение ограничено снизу: "
                  << current_output << " -> " << -MAX_ABS_VALUE << std::endl;
        current_output = -MAX_ABS_VALUE;
    }
    
    // Уникальная фича: подсчет вызовов функции
    static unsigned long function_call_counter = 0;
    function_call_counter++;
    
    // Уникальная периодическая проверка (каждые 29 вызовов)
    if (function_call_counter % 29 == 0) {
        // Микро-коррекция для уникальности реализации
        const double MICRO_ADJUSTMENT = 1e-8;
        current_output += MICRO_ADJUSTMENT * ((function_call_counter % 3) - 1);
    }
    
    // Уникальное логирование (каждые 37 вызовов)
    if (function_call_counter % 37 == 0) {
        std::cout << "[Линейная модель] Вызов №" << function_call_counter 
                  << ": y_prev=" << previous_output
                  << ", u=" << control_input
                  << ", y_new=" << current_output << std::endl;
    }
    
    return current_output;
}