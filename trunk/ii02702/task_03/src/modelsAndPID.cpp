#include "modelsAndPID.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

std::vector<double> simulateLinearModel(double y, double u, int t, double a, double b) {
    std::vector<double> results;
    for (int i = 0; i <= t; i++) {
        results.push_back(y);
        y = a * y + b * u;
    }
    return results;
}

std::vector<double> simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d) {
    std::vector<double> results;

    // Инициализируем предыдущие выходные и входные значения с помощью смещений.
    // Смещения (yOffset и uOffset) представляют собой разницу между начальным и предыдущим состояниями,
    // позволяя нелинейной модели начать с заданной истории для y и u.
    const double y_offset = 0.1;
    const double u_offset = 0.1;

    const double u_step = 0.5;       // шаг изменения для переменной u в нелинейной модели

    double prevY = y - y_offset;
    double prevU = u - u_offset;

    for (int i = 0; i <= t; i++) {
        results.push_back(y);
        double nextY = a * y - b * prevY * prevY + c * u + d * sin(prevU);
        prevU += u_step;
        prevY = y;
        y = nextY;
    }
    return results;
}

void saveToCSV(const std::string& filename, 
               const std::vector<int>& time,
               const std::vector<double>& values,
               const std::vector<double>& controls,
               double setpoint) {
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

void simulateNonLinearSystemWithoutPID(const SimulationConfig& config,
                                       const NonlinearModelParams& params) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    
    const double y_offset = 0.1;
    const double u_offset = 0.1;
    const double u_step = 0.5;
    
    double y = config.initial_y;
    double prevY = config.initial_y - y_offset;
    double prevU = config.initial_u - u_offset;
    
    for (int t = 0; t <= config.simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);
        
        // Сохранение текущих значений
        double currentY = y;
        
        // Обновление состояния нелинейной системы
        y = params.a * y - params.b * prevY * prevY + 
            params.c * config.initial_u + params.d * sin(prevU);
        
        // Обновление предыдущих значений
        prevU += u_step;
        prevY = currentY;
    }
    
    // Сохранение данных
    saveToCSV(config.filename, time_points, temperature_values, {}, 0.0);
}

void simulateNonLinearSystemWithPID(const SimulationConfig& config,
                                    const NonlinearModelParams& params,
                                    PIDController& pid) {
    std::vector<int> time_points;
    std::vector<double> temperature_values;
    std::vector<double> control_signals;
    
    const double y_offset = 0.1;
    const double u_offset = 0.1;
    
    double y = config.initial_y;
    double prevY = config.initial_y - y_offset;
    double prevU = config.initial_u - u_offset;
    
    for (int t = 0; t <= config.simulation_time; t++) {
        time_points.push_back(t);
        temperature_values.push_back(y);
        
        // Вычисление управляющего воздействия
        double u = pid.calculate(config.setpoint, y);
        control_signals.push_back(u);
        
        // Сохранение текущих значений
        double currentY = y;
        double currentU = u;
        
        // Обновление состояния нелинейной системы
        y = params.a * y - params.b * prevY * prevY + 
            params.c * u + params.d * sin(prevU);
        
        // Обновление предыдущих значений
        prevU = currentU;
        prevY = currentY;
    }
    
    // Сохранение данных
    saveToCSV(config.filename, time_points, temperature_values, 
              control_signals, config.setpoint);
}