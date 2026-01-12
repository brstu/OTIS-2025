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

void generatePythonPlotScript() {
    std::ofstream py_script("plot_results.py");
    py_script << R"(
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Чтение данных
data = pd.read_csv('simulation_results.csv')

# Создание графика
plt.figure(figsize=(12, 8))

# График 1: Сравнение линейной и нелинейной моделей
plt.subplot(2, 2, 1)
plt.plot(data['Step'], data['Setpoint'], 'k--', label='Setpoint', linewidth=2)
plt.plot(data['Step'], data['Linear_Output'], 'b-', label='Linear Model', linewidth=2)
plt.plot(data['Step'], data['Nonlinear_Output'], 'r-', label='Nonlinear Model', linewidth=2)
plt.xlabel('Time Step')
plt.ylabel('Output Value')
plt.title('PID Controller Performance')
plt.legend()
plt.grid(True, alpha=0.3)

# График 2: Ошибка регулирования
plt.subplot(2, 2, 2)
error_linear = data['Setpoint'] - data['Linear_Output']
error_nonlinear = data['Setpoint'] - data['Nonlinear_Output']
plt.plot(data['Step'], error_linear, 'b-', label='Linear Error', alpha=0.7)
plt.plot(data['Step'], error_nonlinear, 'r-', label='Nonlinear Error', alpha=0.7)
plt.axhline(y=0, color='k', linestyle='--', alpha=0.3)
plt.xlabel('Time Step')
plt.ylabel('Error')
plt.title('Control Error')
plt.legend()
plt.grid(True, alpha=0.3)

# График 3: Разница между моделями
plt.subplot(2, 2, 3)
difference = data['Nonlinear_Output'] - data['Linear_Output']
plt.plot(data['Step'], difference, 'g-', linewidth=2)
plt.fill_between(data['Step'], 0, difference, alpha=0.3, color='green')
plt.xlabel('Time Step')
plt.ylabel('Difference')
plt.title('Difference: Nonlinear - Linear')
plt.grid(True, alpha=0.3)

# График 4: Гистограмма распределения ошибок
plt.subplot(2, 2, 4)
plt.hist(error_linear, bins=20, alpha=0.5, label='Linear', color='blue')
plt.hist(error_nonlinear, bins=20, alpha=0.5, label='Nonlinear', color='red')
plt.xlabel('Error Value')
plt.ylabel('Frequency')
plt.title('Error Distribution')
plt.legend()

plt.tight_layout()
plt.savefig('pid_controller_results.png', dpi=300, bbox_inches='tight')
plt.show()

print("Plots saved as 'pid_controller_results.png'")
)";
    py_script.close();
    
    std::cout << "Python script generated: plot_results.py" << std::endl;
    std::cout << "Run: python plot_results.py" << std::endl;
}