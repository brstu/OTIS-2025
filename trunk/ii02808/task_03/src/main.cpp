/**
 * @file main.cpp
 * @brief Основная программа для тестирования ПИД-регулятора
 * 
 * Программа демонстрирует работу ПИД-регулятора на различных 
 * моделях объекта управления.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "pid_controller.h"
#include "process_model.h"

/**
 * @brief Проводит simulation системы с ПИД-регулятором
 * @param pid ПИД-регулятор
 * @param process Модель процесса
 * @param setpoints Вектор заданий
 * @param use_nonlinear Флаг использования нелинейной модели
 * @return Вектор результатов simulation
 */
std::vector<double> simulateSystem(PIDController& pid, ProcessModel& process, 
                                  const std::vector<double>& setpoints, bool use_nonlinear = false) {
    std::vector<double> results;
    
    for (size_t i = 0; i < setpoints.size(); ++i) {
        double current_value = (results.empty()) ? 0.0 : results.back();
        
        // Вычисляем управляющее воздействие
        double control_signal = pid.calculate(setpoints[i], current_value);
        
        // Применяем управление к модели процесса
        double new_value;
        if (use_nonlinear) {
            new_value = process.nonlinearModel(control_signal);
        } else {
            new_value = process.linearModel(control_signal);
        }
        
        results.push_back(new_value);
    }
    
    return results;
}

/**
 * @brief Основная функция программы
 */
int main() {
    // Параметры модели (из предыдущей работы)
    setlocale(LC_ALL, "");
    std::vector<double> model_params = {0.8, 0.6, 0.4, 2.2};
    
    // Создаем модель процесса
    ProcessModel process(model_params, 0.0);
    
    // Параметры ПИД-регулятора
    double K = 1.0;   // Коэффициент передачи
    double T = 1.0;   // Постоянная интегрирования  
    double Td = 0.1;  // Постоянная дифференцирования
    double T0 = 0.1;  // Время квантования
    
    // Создаем ПИД-регулятор
    PIDController pid(K, T, Td, T0);
    
    // Тестовые задания (setpoints)
    std::vector<double> setpoints(100, 1.0);  // Ступенчатое изменение
    
    // Проводим simulation для линейной модели
    auto linear_results = simulateSystem(pid, process, setpoints, false);
    
    // Сбрасываем регулятор и модель для следующего теста
    pid.reset();
    process.setInitialValue(0.0);
    
    // Проводим simulation для нелинейной модели
    auto nonlinear_results = simulateSystem(pid, process, setpoints, true);
    
    // Сохраняем результаты в файл для построения графиков
    std::ofstream outfile("simulation_results.csv");
    outfile << "Step,Setpoint,Linear,Nonlinear\n";
    for (size_t i = 0; i < setpoints.size(); ++i) {
        outfile << i << "," << setpoints[i] << "," 
                << linear_results[i] << "," << nonlinear_results[i] << "\n";
    }
    outfile.close();
    
    std::cout << "Simulation completed. Results saved to simulation_results.csv" << std::endl;
    
    return 0;
}