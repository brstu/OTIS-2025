#include "modelsAndPID.hpp"
#include "pid.hpp"
#include <iostream>

int main() {
    // Конфигурация симуляции
    const int simulation_time = 100;          // время симуляции (количество шагов)
    const double setpoint = 25.0;             // заданная температура (уставка)
    const double initial_temperature = 20.0;  // начальная температура
    const double initial_control = 0.0;       // начальное управляющее воздействие
    
    // Параметры линейной модели
    const double linear_a = 0.9;              // коэффициент тепловых потерь
    const double linear_b = 0.2;              // коэффициент нагрева
    
    // Параметры нелинейной модели
    NonlinearModelParams nonlinear_params;
    nonlinear_params.a = 0.85;
    nonlinear_params.b = 0.01;          // слабая квадратичная нелинейность
    nonlinear_params.c = 0.25;
    nonlinear_params.d = 0.05;          // слабая синусоидальная нелинейность
    
    std::cout << "=== Temperature Control Systems Simulation ===" << std::endl;
    std::cout << "Target temperature: " << setpoint << " °C" << std::endl;
    std::cout << "Initial temperature: " << initial_temperature << " °C" << std::endl;
    std::cout << "Simulation time: " << simulation_time << " steps" << std::endl;
    
    // Параметры ПИД-регуляторов
    PIDParameters linear_pid_params;
    linear_pid_params.Kp = 0.8;
    linear_pid_params.Ki = 0.05;
    linear_pid_params.Kd = 0.1;
    linear_pid_params.min_output = -10.0;
    linear_pid_params.max_output = 10.0;
    linear_pid_params.min_integral = -20.0;
    linear_pid_params.max_integral = 20.0;
    linear_pid_params.dt = 1.0;
    
    PIDParameters nonlinear_pid_params;
    nonlinear_pid_params.Kp = 1.0;
    nonlinear_pid_params.Ki = 0.03;
    nonlinear_pid_params.Kd = 0.15;
    nonlinear_pid_params.min_output = -10.0;
    nonlinear_pid_params.max_output = 10.0;
    nonlinear_pid_params.min_integral = -20.0;
    nonlinear_pid_params.max_integral = 20.0;
    nonlinear_pid_params.dt = 1.0;
    
    PIDController linear_pid(linear_pid_params);
    PIDController nonlinear_pid(nonlinear_pid_params);
    
    // 1. Линейная система без регулятора
    std::cout << "\n1. Linear system without PID controller..." << std::endl;
    simulateLinearSystemWithoutPID("temperature_linear_without_pid.csv",
                                   initial_temperature,
                                   5.0,
                                   simulation_time,
                                   linear_a, linear_b);
    
    // 2. Линейная система с ПИД-регулятором
    std::cout << "\n2. Linear system with PID controller..." << std::endl;
    simulateLinearSystemWithPID("temperature_linear_with_pid.csv",
                               setpoint,
                               initial_temperature,
                               simulation_time,
                               linear_a, linear_b,
                               linear_pid);
    
    // 3. Нелинейная система без регулятора
    std::cout << "\n3. Nonlinear system without PID controller..." << std::endl;
    SimulationConfig nonlinear_without_config;
    nonlinear_without_config.filename = "temperature_nonlinear_without_pid.csv";
    nonlinear_without_config.initial_y = initial_temperature;
    nonlinear_without_config.initial_u = 5.0;
    nonlinear_without_config.simulation_time = simulation_time;
    nonlinear_without_config.setpoint = 0.0;
    
    simulateNonLinearSystemWithoutPID(nonlinear_without_config, nonlinear_params);
    
    // 4. Нелинейная система с ПИД-регулятором
    std::cout << "\n4. Nonlinear system with PID controller..." << std::endl;
    SimulationConfig nonlinear_with_config;
    nonlinear_with_config.filename = "temperature_nonlinear_with_pid.csv";
    nonlinear_with_config.initial_y = initial_temperature;
    nonlinear_with_config.initial_u = initial_control;
    nonlinear_with_config.simulation_time = simulation_time;
    nonlinear_with_config.setpoint = setpoint;
    
    simulateNonLinearSystemWithPID(nonlinear_with_config, nonlinear_params, nonlinear_pid);
    
    std::cout << "\n=== Simulation completed ===" << std::endl;
    std::cout << "CSV files created for visualization:" << std::endl;
    std::cout << "  - temperature_linear_without_pid.csv" << std::endl;
    std::cout << "  - temperature_linear_with_pid.csv" << std::endl;
    std::cout << "  - temperature_nonlinear_without_pid.csv" << std::endl;
    std::cout << "  - temperature_nonlinear_with_pid.csv" << std::endl;
    
    return 0;
}