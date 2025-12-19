#include "modelsAndPID.hpp"
#include "pid.hpp"
#include <iostream>

int main() {
    const int simulation_time = 100;          // время симуляции (количество шагов)
    const double setpoint = 25.0;             // заданная температура (уставка)
    
    const double linear_a = 0.9;              // коэффициент тепловых потерь
    const double linear_b = 0.2;              // коэффициент нагрева
    
    const double nonlinear_a = 0.85;
    const double nonlinear_b = 0.01;          // слабая квадратичная нелинейность
    const double nonlinear_c = 0.25;
    const double nonlinear_d = 0.05;          // слабая синусоидальная нелинейность

    const double initial_temperature = 20.0;  // начальная температура
    const double initial_control = 0.0;       // начальное управляющее воздействие
    
    std::cout << "=== Temperature Control Systems Simulation ===" << std::endl;
    std::cout << "Target temperature: " << setpoint << " °C" << std::endl;
    std::cout << "Initial temperature: " << initial_temperature << " °C" << std::endl;
    std::cout << "Simulation time: " << simulation_time << " steps" << std::endl;
 
    PIDController linear_pid({0.8, 0.05, 0.1,    // Kp, Ki, Kd
                            -10.0, 10.0,        // ограничения выхода
                            -20.0, 20.0,        // ограничения интеграла
                            1.0});               // шаг времени
    
    PIDController nonlinear_pid({1.0, 0.03, 0.15,
                               -10.0, 10.0,
                               -20.0, 20.0,
                               1.0});
    
    std::cout << "\n1. Linear system without PID controller..." << std::endl;
    simulateLinearSystemWithoutPID("temperature_linear_without_pid.csv",
                                   initial_temperature,
                                   5.0,
                                   simulation_time,
                                   linear_a, linear_b);
    
    std::cout << "\n2. Linear system with PID controller..." << std::endl;
    simulateLinearSystemWithPID("temperature_linear_with_pid.csv",
                               setpoint,
                               initial_temperature,
                               simulation_time,
                               linear_a, linear_b,
                               linear_pid);
    
    std::cout << "\n3. Nonlinear system without PID controller..." << std::endl;
    simulateNonLinearSystemWithoutPID("temperature_nonlinear_without_pid.csv",
                                     initial_temperature,
                                     5.0,
                                     simulation_time,
                                     nonlinear_a, nonlinear_b,
                                     nonlinear_c, nonlinear_d);
    
    std::cout << "\n4. Nonlinear system with PID controller..." << std::endl;
    simulateNonLinearSystemWithPID("temperature_nonlinear_with_pid.csv",
                                  setpoint,
                                  initial_temperature,
                                  initial_control,
                                  simulation_time,
                                  nonlinear_a, nonlinear_b,
                                  nonlinear_c, nonlinear_d,
                                  nonlinear_pid);
    
    std::cout << "\n=== Simulation completed ===" << std::endl;
    std::cout << "CSV files created for visualization:" << std::endl;
    std::cout << "  - temperature_linear_without_pid.csv" << std::endl;
    std::cout << "  - temperature_linear_with_pid.csv" << std::endl;
    std::cout << "  - temperature_nonlinear_without_pid.csv" << std::endl;
    std::cout << "  - temperature_nonlinear_with_pid.csv" << std::endl;
    
    return 0;
}