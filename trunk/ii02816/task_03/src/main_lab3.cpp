/**
 * @file lab3main.cpp
 * @brief Основная программа для тестирования ПИД-регулятора
 * 
 * Программа демонстрирует работу ПИД-регулятора на различных 
 * моделях объекта управления.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "pid.h"
#include "mdl.h"

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
    
    for (double setpoint : setpoints) {

        double current_value = (results.empty()) ? 0.0 : results.back();
        
        // Вычисляем управляющее воздействие
        double control_signal = pid.calculate(setpoint, current_value);
        
        
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
    
    setlocale(LC_ALL, "");
    std::vector<double> model_params = {0.85, 0.01, 0.15, 0.01};
    
    
    ProcessModel process(model_params, 10.0);
    
    
    double K = 0.8;   
    double T = 4.0;   
    double Td = 0.05;  
    double T0 = 1.0;  
    
    
    PIDController pid(K, T, Td, T0);
    
    
    std::vector<double> setpoints(20, 20.0);  
    
    
    auto linear_results = simulateSystem(pid, process, setpoints, false);
    
    
    pid.reset();
    process.setInitialValue(0.0);
    
    
    auto nonlinear_results = simulateSystem(pid, process, setpoints, true);
    
    
    std::cout << "Step\t\tSetpoint\t\tLinear\t\tNonlinear\n";
    for (size_t i = 0; i < setpoints.size(); ++i) {
        std::cout << i << "\t\t" << setpoints[i] << "\t\t" 
                << linear_results[i] << "\t\t" << nonlinear_results[i] << "\n";
    }
    
    std::cout << "Simulation completed. Results saved to simulation_results.csv" << std::endl;
    
    return 0;
}