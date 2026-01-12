// Добавьте в main_lab3.cpp после вывода в консоль:

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "pid.h"
#include "mdl.h"
#include "plot_utils.h"

std::vector<double> simulateSystem(PIDController& pid, ProcessModel& process, 
                                  const std::vector<double>& setpoints, bool use_nonlinear = false) {
    std::vector<double> results;
    std::vector<double> control_signals; // Сохраняем управляющие воздействия
    
    for (double setpoint : setpoints) {
        double current_value = (results.empty()) ? 0.0 : results.back();
        double control_signal = pid.calculate(setpoint, current_value);
        control_signals.push_back(control_signal);
        
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

int main() {
    setlocale(LC_ALL, "");
    std::vector<double> model_params = {0.85, 0.01, 0.15, 0.01};
    ProcessModel process(model_params, 10.0);
    
    double K = 0.8;   
    double T = 4.0;   
    double Td = 0.05;  
    double T0 = 1.0;  
    
    PIDController pid(K, T, Td, T0);
    std::vector<double> setpoints(100, 20.0);  // Увеличим количество шагов
    
    // Симуляция линейной модели
    auto linear_results = simulateSystem(pid, process, setpoints, false);
    
    pid.reset();
    process.setInitialValue(0.0);
    
    // Симуляция нелинейной модели
    auto nonlinear_results = simulateSystem(pid, process, setpoints, true);
    
    // Сохранение в CSV файл
    std::ofstream csv_file("simulation_results.csv");
    csv_file << "Step,Setpoint,Linear_Output,Nonlinear_Output\n";
    
    for (size_t i = 0; i < setpoints.size(); ++i) {
        csv_file << i << "," 
                 << setpoints[i] << "," 
                 << linear_results[i] << "," 
                 << nonlinear_results[i] << "\n";
    }
    csv_file.close();
    
    std::cout << "Simulation completed. Results saved to simulation_results.csv" << std::endl;
    
    // Генерация Python скрипта для визуализации
    generatePythonPlotScript();
    system("python3 plot_pid_results.py");
    return 0;
}

