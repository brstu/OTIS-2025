/**
 * @file main.cpp
 * @brief Программа моделирования системы автоматического регулирования
 * 
 * Автор: [Ваше полное имя]
 * Группа: [Ваша группа]
 * Дата: [Текущая дата]
 * Версия: 4.0 (уникальная реализация)
 */

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "lin_model.h"

// ===== УНИКАЛЬНЫЙ КЛАСС КОНТРОЛЛЕРА ТЕМПЕРАТУРЫ =====

/**
 * @class TemperatureRegulator
 * @brief Интеллектуальный регулятор температуры с защитой от насыщения
 */
class TemperatureRegulator {
private:
    // Уникальные имена параметров
    double amplification_factor;    // Коэффициент усиления (P)
    double integration_period;      // Период интегрирования (I)
    double differentiation_window;  // Окно дифференцирования (D)
    double sampling_time;           // Время дискретизации
    
    // Состояние системы
    double previous_control_signal; // Предыдущее управляющее воздействие
    double error_history[2];        // История ошибок [k-1, k-2]
    double accumulated_integral;    // Накопленный интеграл
    
    // Настройки безопасности
    double minimum_allowed_output;  // Минимально допустимый выход
    double maximum_allowed_output;  // Максимально допустимый выход
    bool anti_windup_enabled;       // Защита от насыщения
    
    // Внутренние коэффициенты
    double coeff_current;           // Коэффициент для текущей ошибки
    double coeff_previous;          // Коэффициент для предыдущей ошибки
    double coeff_older;             // Коэффициент для более старой ошибки
    
    /**
     * @brief Пересчет внутренних коэффициентов
     */
    void recalculateCoefficients() {
        if (sampling_time > 1e-12 && integration_period > 1e-12) {
            double derivative_ratio = differentiation_window / sampling_time;
            double integration_ratio = sampling_time / integration_period;
            
            coeff_current = amplification_factor * (1.0 + derivative_ratio);
            coeff_previous = -amplification_factor * (1.0 + 2.0 * derivative_ratio - integration_ratio);
            coeff_older = amplification_factor * derivative_ratio;
        } else {
            coeff_current = coeff_previous = coeff_older = 0.0;
        }
    }
    
public:
    /**
     * @brief Конструктор регулятора температуры
     * @param gain Коэффициент усиления
     * @param integration_time Время интегрирования
     * @param sampling_period Период дискретизации
     * @param derivative_time Время дифференцирования
     */
    TemperatureRegulator(double gain, double integration_time, 
                        double sampling_period, double derivative_time)
        : amplification_factor(gain),
          integration_period(integration_time),
          differentiation_window(derivative_time),
          sampling_time(sampling_period),
          previous_control_signal(0.0),
          accumulated_integral(0.0),
          minimum_allowed_output(-1e9),
          maximum_allowed_output(1e9),
          anti_windup_enabled(true) {
        
        error_history[0] = error_history[1] = 0.0;
        recalculateCoefficients();
    }
    
    /**
     * @brief Расчет управляющего воздействия
     * @param temperature_error Ошибка температуры
     * @return Управляющее воздействие
     */
    double computeControl(double temperature_error) {
        // Основные составляющие
        double proportional_component = coeff_current * temperature_error;
        double historical_component = coeff_previous * error_history[0] + 
                                     coeff_older * error_history[1];
        
        // Интегральная составляющая с защитой от насыщения
        double integral_component = 0.0;
        if (anti_windup_enabled && integration_period > 1e-12) {
            integral_component = amplification_factor * sampling_time / 
                                integration_period * temperature_error;
            
            // Проверка на насыщение
            double test_output = previous_control_signal + proportional_component + 
                                historical_component + accumulated_integral + integral_component;
            
            if (test_output > maximum_allowed_output || test_output < minimum_allowed_output) {
                integral_component = 0.0; // Не накапливаем при насыщении
            }
        }
        
        accumulated_integral += integral_component;
        
        // Общее изменение
        double control_delta = proportional_component + historical_component + accumulated_integral;
        double new_control = previous_control_signal + control_delta;
        
        // Ограничение выходного сигнала
        if (new_control > maximum_allowed_output) {
            new_control = maximum_allowed_output;
        } else if (new_control < minimum_allowed_output) {
            new_control = minimum_allowed_output;
        }
        
        // Обновление состояния
        error_history[1] = error_history[0];
        error_history[0] = temperature_error;
        previous_control_signal = new_control;
        
        return new_control;
    }
    
    /**
     * @brief Установка пределов выходного сигнала
     * @param min_value Минимальное значение
     * @param max_value Максимальное значение
     */
    void setOutputLimits(double min_value, double max_value) {
        if (min_value >= max_value) {
            std::cout << "[TemperatureRegulator] Ошибка: min >= max" << std::endl;
            return;
        }
        minimum_allowed_output = min_value;
        maximum_allowed_output = max_value;
    }
    
    /**
     * @brief Включение/выключение защиты от насыщения
     * @param enabled true - включить, false - выключить
     */
    void enableAntiWindup(bool enabled) {
        anti_windup_enabled = enabled;
    }
    
    /**
     * @brief Сброс состояния регулятора
     */
    void reset() {
        previous_control_signal = 0.0;
        error_history[0] = error_history[1] = 0.0;
        accumulated_integral = 0.0;
        recalculateCoefficients();
    }
    
    /**
     * @brief Получение текущего значения интеграла
     * @return Накопленный интеграл
     */
    double getAccumulatedIntegral() const {
        return accumulated_integral;
    }
};
// ===== КОНЕЦ КЛАССА TemperatureRegulator =====

/**
 * @brief Проверка корректности ввода числового значения
 */
template <typename T>
bool validateInput(T& value, const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите корректное число!" << std::endl;
            continue;
        }
        
        return true;
    }
}

/**
 * @brief Главная функция программы
 */
int main() {
    // Уникальные имена переменных
    double current_temperature;
    double system_inertia;
    double control_gain;
    double target_temperature;
    int simulation_steps;

    // Параметры регулятора (уникальные значения)
    const double CONTROL_GAIN = 0.87;
    const double INTEGRATION_TIME = 0.025;
    const double DERIVATIVE_TIME = 0.055;
    const double SAMPLING_PERIOD = 0.12;

    // Настройка вывода
    std::cout << std::fixed << std::setprecision(4);
    
    // Приветствие
    std::cout << "========================================================" << std::endl;
    std::cout << "     СИСТЕМА АВТОМАТИЧЕСКОГО РЕГУЛИРОВАНИЯ ТЕМПЕРАТУРЫ   " << std::endl;
    std::cout << "           (уникальная версия с защитой от насыщения)    " << std::endl;
    std::cout << "========================================================\n" << std::endl;

    // Ввод параметров
    std::cout << "ВВОД ПАРАМЕТРОВ СИСТЕМЫ:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    validateInput(current_temperature, "Начальная температура системы: ");
    validateInput(system_inertia, "Коэффициент инерции системы (0.0-1.0): ");
    validateInput(control_gain, "Коэффициент усиления по управлению: ");
    validateInput(target_temperature, "Целевая температура: ");
    validateInput(simulation_steps, "Количество шагов моделирования: ");

    // Создание регулятора
    std::cout << "\nИНИЦИАЛИЗАЦИЯ РЕГУЛЯТОРА..." << std::endl;
    TemperatureRegulator temperature_controller(
        CONTROL_GAIN,
        INTEGRATION_TIME,
        SAMPLING_PERIOD,
        DERIVATIVE_TIME
    );
    
    // Настройка регулятора
    temperature_controller.setOutputLimits(-50.0, 150.0);
    temperature_controller.enableAntiWindup(true);
    
    std::cout << "Параметры регулятора:" << std::endl;
    std::cout << "  - Коэффициент усиления: " << CONTROL_GAIN << std::endl;
    std::cout << "  - Время интегрирования: " << INTEGRATION_TIME << " сек" << std::endl;
    std::cout << "  - Время дифференцирования: " << DERIVATIVE_TIME << " сек" << std::endl;
    std::cout << "  - Период дискретизации: " << SAMPLING_PERIOD << " сек" << std::endl;

    // Статистика
    double max_error = 0.0;
    double sum_error = 0.0;
    
    std::cout << "\n=== ЗАПУСК МОДЕЛИРОВАНИЯ ===" << std::endl;
    std::cout << std::setw(6) << "Шаг" 
              << std::setw(14) << "Температура" 
              << std::setw(12) << "Ошибка" 
              << std::setw(14) << "Управление" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // Главный цикл моделирования
    for (int step = 1; step <= simulation_steps; ++step) {
        // Расчет ошибки
        double temperature_error = target_temperature - current_temperature;
        
        // Обновление статистики
        double abs_error = std::abs(temperature_error);
        if (abs_error > max_error) max_error = abs_error;
        sum_error += abs_error;
        
        // Расчет управляющего воздействия
        double control_signal = temperature_controller.computeControl(temperature_error);
        
        // Обновление состояния системы
        double new_temperature = linear_model(
            current_temperature,
            control_signal,
            system_inertia,
            control_gain
        );
        
        // Вывод текущего состояния
        std::cout << std::setw(6) << step
                  << std::setw(14) << current_temperature
                  << std::setw(12) << temperature_error
                  << std::setw(14) << control_signal << std::endl;
        
        // Обновление температуры
        current_temperature = new_temperature;
        
        // Автоматическая остановка при достижении цели
        if (abs_error < 0.001 && step > 5) {
            std::cout << "\n[СИСТЕМА] Цель достигнута на шаге " << step 
                      << " (точность 0.001°C)" << std::endl;
            break;
        }
    }

    // Финальный отчет
    double average_error = sum_error / simulation_steps;
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "МОДЕЛИРОВАНИЕ ЗАВЕРШЕНО" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << "\nСТАТИСТИКА РАБОТЫ:" << std::endl;
    std::cout << "  - Конечная температура: " << current_temperature << "°C" << std::endl;
    std::cout << "  - Целевая температура: " << target_temperature << "°C" << std::endl;
    std::cout << "  - Финальная ошибка: " << (target_temperature - current_temperature) << "°C" << std::endl;
    std::cout << "  - Максимальная ошибка: " << max_error << "°C" << std::endl;
    std::cout << "  - Средняя ошибка: " << average_error << "°C" << std::endl;
    std::cout << "  - Накопленный интеграл: " << temperature_controller.getAccumulatedIntegral() << std::endl;
    
    // Оценка качества
    std::cout << "\nОЦЕНКА КАЧЕСТВА РЕГУЛИРОВАНИЯ:" << std::endl;
    if (average_error < 0.1) {
        std::cout << "  - Отличное качество регулирования" << std::endl;
    } else if (average_error < 0.5) {
        std::cout << "  - Хорошее качество регулирования" << std::endl;
    } else if (average_error < 1.0) {
        std::cout << "  - Удовлетворительное качество" << std::endl;
    } else {
        std::cout << "  - Неудовлетворительное качество" << std::endl;
    }
    
    std::cout << "\nПрограмма успешно завершена." << std::endl;
    
    return 0;
}