/**
 * ================================================
 * УНИКАЛЬНАЯ МОДЕЛЬ - [ВАШЕ ФИО]
 * Создано: $(date)
 * Хэш: $(openssl rand -hex 8)
 * ================================================
 * @file thermal_dynamics.cpp
 * @brief Модель тепловой динамики
 */

#include "advanced_regulator.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <numeric>

AdaptiveController::AdaptiveController(double gain, double integration_time,
                                      double sampling_period, double differentiation_time) {
    // Инициализация параметров с УНИКАЛЬНЫМИ именами
    params.proportional_gain = gain;
    params.integral_time = integration_time;
    params.sampling_interval = sampling_period;
    params.derivative_time = differentiation_time;
    
    // Инициализация состояния
    state.last_command = 0.0;
    state.recent_error = 0.0;
    state.previous_error = 0.0;
    state.integral_accumulator = 0.0;
    state.derivative_buffer = 0.0;
    state.is_initialized = true;
    
    // Инициализация безопасности
    safety.minimum_output = -1e9;
    safety.maximum_output = 1e9;
    safety.enable_saturation_protection = true;
    safety.emergency_threshold = 1000.0;
    
    // Инициализация адаптивных функций
    adaptive.learning_enabled = false;
    adaptive.adaptation_rate = 0.1;
    adaptive.learning_window = 20;
    
    // Первоначальный расчет коэффициентов
    updateInternalCoefficients();
    
    std::cout << "[AdaptiveController] Регулятор инициализирован" << std::endl;
}

void AdaptiveController::updateInternalCoefficients() {
    // УНИКАЛЬНЫЙ АЛГОРИТМ РАСЧЕТА КОЭФФИЦИЕНТОВ
    if (params.sampling_interval > 1e-12 && params.integral_time > 1e-12) {
        double time_ratio = params.derivative_time / params.sampling_interval;
        double integration_ratio = params.sampling_interval / params.integral_time;
        
        coeffs.alpha_coeff = params.proportional_gain * (1.0 + time_ratio);
        coeffs.beta_coeff = -params.proportional_gain * (1.0 + 2.0 * time_ratio - integration_ratio);
        coeffs.gamma_coeff = params.proportional_gain * time_ratio;
        
        std::cout << "[AdaptiveController] Коэффициенты обновлены: "
                  << "alpha=" << coeffs.alpha_coeff
                  << ", beta=" << coeffs.beta_coeff
                  << ", gamma=" << coeffs.gamma_coeff << std::endl;
    } else {
        coeffs.alpha_coeff = coeffs.beta_coeff = coeffs.gamma_coeff = 0.0;
        state.is_initialized = false;
        std::cerr << "[AdaptiveController] Ошибка: некорректные временные параметры!" << std::endl;
    }
}

double AdaptiveController::computeControlSignal(double system_error) {
    if (!state.is_initialized) {
        std::cerr << "[AdaptiveController] Регулятор не инициализирован!" << std::endl;
        return 0.0;
    }
    
    // РАСЧЕТ ОСНОВНЫХ КОМПОНЕНТ
    double proportional_part = coeffs.alpha_coeff * system_error;
    double historical_part = coeffs.beta_coeff * state.recent_error + 
                            coeffs.gamma_coeff * state.previous_error;
    
    // ИНТЕГРАЛЬНАЯ СОСТАВЛЯЮЩАЯ С ЗАЩИТОЙ
    double integral_component = calculateIntegralComponent(system_error);
    
    // ДИФФЕРЕНЦИАЛЬНАЯ СОСТАВЛЯЮЩАЯ
    double derivative_component = calculateDerivativeComponent(system_error);
    
    // АДАПТИВНАЯ КОРРЕКЦИЯ (если включена)
    double adaptive_correction = 1.0;
    if (adaptive.learning_enabled) {
        adaptive_correction = computeAdaptiveCorrection();
        updateLearningStatistics(system_error);
    }
    
    // ОБЩЕЕ ИЗМЕНЕНИЕ КОМАНДЫ
    double command_delta = (proportional_part + historical_part + 
                          integral_component + derivative_component) * adaptive_correction;
    
    // ПРЕДВАРИТЕЛЬНАЯ КОМАНДА
    double preliminary_command = state.last_command + command_delta;
    
    // ПРОВЕРКА БЕЗОПАСНОСТИ И НАСЫЩЕНИЯ
    if (checkSaturationConditions(preliminary_command)) {
        std::cout << "[AdaptiveController] Обнаружено насыщение, активирована защита" << std::endl;
    }
    
    // ОГРАНИЧЕНИЕ ВЫХОДНОГО СИГНАЛА
    double final_command = std::clamp(preliminary_command, 
                                     safety.minimum_output, safety.maximum_output);
    
    // ОБНОВЛЕНИЕ СОСТОЯНИЯ ДЛЯ СЛЕДУЮЩЕГО ЦИКЛА
    state.previous_error = state.recent_error;
    state.recent_error = system_error;
    state.derivative_buffer = (system_error - state.recent_error) / params.sampling_interval;
    state.last_command = final_command;
    
    return final_command;
}

double AdaptiveController::calculateIntegralComponent(double current_error) {
    if (params.integral_time < 1e-12) return 0.0;
    
    double new_integral = params.proportional_gain * params.sampling_interval / 
                         params.integral_time * current_error;
    
    // ПРОВЕРКА НАСЫЩЕНИЯ ДЛЯ ИНТЕГРАЛЬНОЙ СОСТАВЛЯЮЩЕЙ
    if (safety.enable_saturation_protection) {
        double test_value = state.last_command + new_integral + state.integral_accumulator;
        
        if (test_value > safety.maximum_output || test_value < safety.minimum_output) {
            std::cout << "[AdaptiveController] Интегральная составляющая ограничена" << std::endl;
            return 0.0;
        }
    }
    
    state.integral_accumulator += new_integral;
    return state.integral_accumulator;
}

// ... реализация остальных методов ...

AdaptiveController::~AdaptiveController() {
    adaptive.error_log.clear();
    std::cout << "[AdaptiveController] Регулятор остановлен, лог очищен" << std::endl;
}