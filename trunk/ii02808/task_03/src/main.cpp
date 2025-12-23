/**
 * @file main.cpp
 * @brief Основная программа исследования работы ПИД-регулятора
 * 
 * Программа выполняет сравнительный анализ поведения ПИД-регулятора
 * при управлении линейными и нелинейными динамическими системами.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "pid_controller.h"
#include "process_model.h"

/**
 * @brief Осуществляет моделирование замкнутой системы управления
 * @param controller ПИД-регулятор
 * @param dynamic_system Модель динамической системы
 * @param reference_signals Последовательность задающих воздействий
 * @param use_nonlinear_model Флаг выбора нелинейной модели системы
 * @return Массив значений выхода системы на каждом шаге моделирования
 */
std::vector<double> executeSimulation(PIDRegulator& controller, 
                                     DynamicSystem& dynamic_system,
                                     const std::vector<double>& reference_signals,
                                     bool use_nonlinear_model = false) {
    std::vector<double> simulation_output;
    
    for (double reference_value : reference_signals) {

        double current_state = simulation_output.empty() ? 0.0 : simulation_output.back();
        
    
        double control_signal = controller.computeControl(reference_value, current_state);
        

        double next_state;
        if (use_nonlinear_model) {
            next_state = dynamic_system.evaluateNonlinear(control_signal);
        } else {
            next_state = dynamic_system.evaluateLinear(control_signal);
        }
        
        simulation_output.push_back(next_state);
    }
    
    return simulation_output;
}

/**
 * @brief Главная функция исследовательской программы
 */
int main() {

    std::setlocale(LC_ALL, "Russian");
    

    std::vector<double> system_parameters = {0.85, 0.01, 0.15, 0.01};
    
    DynamicSystem system_model(system_parameters, 10.0);
    
    double controller_gain = 0.8;          // Коэффициент усиления
    double integral_time = 4.0;            // Время интегрирования
    double derivative_time = 0.05;         // Время дифференцирования
    double sampling_period = 1.0;          // Период дискретизации
    
    PIDRegulator controller(controller_gain, integral_time, derivative_time, sampling_period);
    
    const int simulation_steps = 1000;
    std::vector<double> test_reference(simulation_steps, 10.0);
    
    auto linear_response = executeSimulation(controller, system_model, 
                                           test_reference, false);
    
    controller.clearState();
    system_model.initializeState(0.0);
    
    auto nonlinear_response = executeSimulation(controller, system_model,
                                              test_reference, true);
    
    
    std::cout << std::setw(8) << "Шаг" 
              << std::setw(15) << "Задание" 
              << std::setw(18) << "Линейная модель" 
              << std::setw(18) << "Нелинейная модель" << "\n";
    
    for (size_t iteration = 0; iteration < test_reference.size(); ++iteration) {
        std::cout << std::setw(8) << iteration 
                  << std::setw(15) << std::fixed << std::setprecision(3) << test_reference[iteration]
                  << std::setw(18) << linear_response[iteration] 
                  << std::setw(18) << nonlinear_response[iteration] << "\n";
    }
    
    std::cout << "\nМоделирование завершено. Результаты сохранены в файл simulation_data.csv" << std::endl;
    
    return 0;
}