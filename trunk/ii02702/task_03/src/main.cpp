#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "models.hpp"
#include "pid.hpp"

/**
 * @brief Сохранение данных в CSV файл
 * @param filename Имя файла для сохранения
 * @param time Вектор временных меток
 * @param values Вектор значений
 * @param controls Вектор управляющих воздействий (опционально)
 * @param setpoint Заданное значение (уставка) (опционально)
 */
void saveToCSV(const std::string& filename, 
               const std::vector<int>& time,
               const std::vector<double>& values,
               const std::vector<double>& controls = {},
               double setpoint = 0.0) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error " << filename << std::endl;
        return;
    }
    
    // Заголовок CSV файла
    file << "Time,Value,Setpoint";
    if (!controls.empty()) {
        file << ",Control";
    }
    file << "\n";
    
    // Запись данных
    for (size_t i = 0; i < time.size(); ++i) {
        file << time[i] << "," 
             << std::fixed << std::setprecision(6) << values[i] << ","
             << setpoint;
        
        if (!controls.empty() && i < controls.size()) {
            file << "," << std::fixed << std::setprecision(6) << controls[i];
        }
        
        file << "\n";
    }
    
    file.close();
    std::cout << "Data is written " << filename << std::endl;
}

/**
 * @brief Моделирование линейной системы без ПИД-регулятора
 * @param filename Имя файла для сохранения результатов
 * @param initial_y Начальное состояние системы
 * @param constant_u Постоянное входное воздействие
 * @param simulation_time Время симуляции
 * @param a Коэффициент при предыдущем значении y
 * @param b Коэффициент при входном воздействии u
 */
void simulateLinearSystemWithoutPID(const std::string& filename,
                                    double initial_y,
                                    double constant_u,
                                    int simulation_time,
                                    double a, double b) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    
    double y = initial_y;
    
    for (int t = 0; t <= simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);
        
        // Обновление состояния системы
        y = a * y + b * constant_u;
    }
    
    // Сохранение данных
    saveToCSV(filename, time_points, temperature_values, {}, 0.0);
}

/**
 * @brief Моделирование линейной системы с ПИД-регулятором
 * @param filename Имя файла для сохранения результатов
 * @param setpoint Заданное значение температуры
 * @param initial_y Начальное состояние системы
 * @param simulation_time Время симуляции
 * @param a Коэффициент при предыдущем значении y
 * @param b Коэффициент при входном воздействии u
 * @param pid ПИД-регулятор
 */
void simulateLinearSystemWithPID(const std::string& filename,
                                 double setpoint,
                                 double initial_y,
                                 int simulation_time,
                                 double a, double b,
                                 PIDController& pid) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    std::vector<double> control_signals;
    
    double y = initial_y;
    
    for (int t = 0; t <= simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);

        double u = pid.calculate(setpoint, y);
        control_signals.push_back(u);
        y = a * y + b * u;
    }
    
    saveToCSV(filename, time_points, temperature_values, control_signals, setpoint);
}

/**
 * @brief Моделирование нелинейной системы без ПИД-регулятора
 * @param filename Имя файла для сохранения результатов
 * @param initial_y Начальное состояние системы
 * @param initial_u Начальное входное воздействие
 * @param simulation_time Время симуляции
 * @param a Линейный коэффициент при y
 * @param b Коэффициент при квадрате предыдущего значения y
 * @param c Коэффициент при входном воздействии u
 * @param d Коэффициент при синусоидальном члене
 */
void simulateNonLinearSystemWithoutPID(const std::string& filename,
                                       double initial_y,
                                       double initial_u,
                                       int simulation_time,
                                       double a, double b,
                                       double c, double d) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    
    const double y_offset = 0.1;
    const double u_offset = 0.1;
    const double u_step = 0.5;
    
    double y = initial_y;
    double prevY = initial_y - y_offset;
    double prevU = initial_u - u_offset;
    
    for (int t = 0; t <= simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);
        
        // Сохранение текущих значений
        double currentY = y;
        
        // Обновление состояния нелинейной системы
        y = a * y - b * prevY * prevY + c * initial_u + d * sin(prevU);
        
        // Обновление предыдущих значений
        prevU += u_step;
        prevY = currentY;
    }
    
    // Сохранение данных
    saveToCSV(filename, time_points, temperature_values, {}, 0.0);
}

/**
 * @brief Моделирование нелинейной системы с ПИД-регулятором
 * @param filename Имя файла для сохранения результатов
 * @param setpoint Заданное значение температуры
 * @param initial_y Начальное состояние системы
 * @param initial_u Начальное входное воздействие
 * @param simulation_time Время симуляции
 * @param a Линейный коэффициент при y
 * @param b Коэффициент при квадрате предыдущего значения y
 * @param c Коэффициент при входном воздействии u
 * @param d Коэффициент при синусоидальном члене
 * @param pid ПИД-регулятор
 */
void simulateNonLinearSystemWithPID(const std::string& filename,
                                    double setpoint,
                                    double initial_y,
                                    double initial_u,
                                    int simulation_time,
                                    double a, double b,
                                    double c, double d,
                                    PIDController& pid) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    std::vector<double> control_signals;
    
    const double y_offset = 0.1;
    const double u_offset = 0.1;
    
    double y = initial_y;
    double prevY = initial_y - y_offset;
    double prevU = initial_u - u_offset;
    
    for (int t = 0; t <= simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);
        
        // Вычисление управляющего воздействия
        double u = pid.calculate(setpoint, y);
        control_signals.push_back(u);
        
        // Сохранение текущих значений
        double currentY = y;
        double currentU = u;
        
        // Обновление состояния нелинейной системы
        y = a * y - b * prevY * prevY + c * u + d * sin(prevU);
        
        // Обновление предыдущих значений
        prevU = currentU;
        prevY = currentY;
    }
    
    // Сохранение данных
    saveToCSV(filename, time_points, temperature_values, control_signals, setpoint);
}

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
 
    PIDController linear_pid(0.8, 0.05, 0.1,    // Kp, Ki, Kd
                            -10.0, 10.0,        // ограничения выхода
                            -20.0, 20.0,        // ограничения интеграла
                            1.0);               // шаг времени
    
    PIDController nonlinear_pid(1.0, 0.03, 0.15,
                               -10.0, 10.0,
                               -20.0, 20.0,
                               1.0);
    
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