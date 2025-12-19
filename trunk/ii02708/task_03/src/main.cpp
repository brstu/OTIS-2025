#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "nonlinear.h"
#include "pid.h"

/**
 * @brief Сохраняет данные в CSV файл
 * 
 * @param filename Имя файла для сохранения
 * @param time Вектор временных меток
 * @param values Вектор значений
 * @param setpoint Заданное значение (опционально)
 * @return true Файл успешно сохранен
 * @return false Ошибка при сохранении
 */
bool saveToCSV(const std::string& filename, 
               const std::vector<int>& time, 
               const std::vector<double>& values,
               double setpoint = 0.0);

int main()
{
    NonLinearCoeff nonlinearCoeff;
    nonlinearCoeff.a = 0.5;
    nonlinearCoeff.b = 0.2;
    nonlinearCoeff.c = 0.15;
    nonlinearCoeff.d = 0.3;
    nonlinearCoeff.u = 1.2;
    
    double y0;
    std::cout << "Enter initial temperature y1: ";
    std::cin >> y0;
    
    int n = 20;
    double setpoint = 2.0;
    
    double Kp = 1.5;
    double Ki = 0.2;
    double Kd = 0.05;
    
    std::cout << "\n=== Temperature Regulation System Simulation ===\n";
    std::cout << "Initial temperature: " << y0 << "\n";
    std::cout << "Desired temperature: " << setpoint << "\n";
    std::cout << "Number of steps: " << n << "\n";
    std::cout << "PID parameters: Kp=" << Kp << ", Ki=" << Ki << ", Kd=" << Kd << "\n\n";
    
    std::cout << "1. System without regulator:" << std::endl;
    std::vector<double> nonlinearResults = calculateNonlinear(nonlinearCoeff, y0, n);
    
    std::vector<int> timeSteps(n);
    for (int i = 0; i < n; i++) {
        timeSteps[i] = i + 1;
    }
    
    if (saveToCSV("temperature_without_pid.csv", timeSteps, nonlinearResults, setpoint)) {
        std::cout << "   Results saved to temperature_without_pid.csv\n";
    }
    
    for (int i = 0; i < std::min(5, n); i++) {
        std::cout << "   t" << i + 1 << " = " << nonlinearResults[i];
        std::cout << " (deviation: " << std::abs(setpoint - nonlinearResults[i]) << " )" << std::endl;
    }
    if (n > 5) {
        std::cout << "   ...\n";
        std::cout << "   t" << n << " = " << nonlinearResults[n-1];
        std::cout << " (deviation: " << std::abs(setpoint - nonlinearResults[n-1]) << " )" << std::endl;
    }
    
    std::cout << "\n2. System with PID regulator:" << std::endl;
    std::vector<double> pidResults = simulatePidRegulatorForNonlinear(
        nonlinearCoeff, y0, n, setpoint, PidParams{ Kp, Ki, Kd });
    
    if (saveToCSV("temperature_with_pid.csv", timeSteps, pidResults, setpoint)) {
        std::cout << "   Results saved to temperature_with_pid.csv\n";
    }
    
    for (int i = 0; i < std::min(5, n); i++) {
        std::cout << "   t" << i + 1 << " = " << pidResults[i];
        std::cout << " (deviation: " << std::abs(setpoint - pidResults[i]) << " )" << std::endl;
    }
    if (n > 5) {
        std::cout << "   ...\n";
        std::cout << "   t" << n << " = " << pidResults[n-1];
        std::cout << " (deviation: " << std::abs(setpoint - pidResults[n-1]) << " )" << std::endl;
    }

    std::cout << "\n3. Efficiency comparison:" << std::endl;
    
    double sumErrorWithoutPID = 0.0;
    double sumErrorWithPID = 0.0;
    
    for (int i = 0; i < n; i++) {
        sumErrorWithoutPID += std::abs(setpoint - nonlinearResults[i]);
        sumErrorWithPID += std::abs(setpoint - pidResults[i]);
    }
    
    double avgErrorWithoutPID = sumErrorWithoutPID / n;
    double avgErrorWithPID = sumErrorWithPID / n;
    
    std::cout << "   Average deviation without regulator: " << avgErrorWithoutPID << "\n";
    std::cout << "   Average deviation with PID regulator: " << avgErrorWithPID << "\n";
    
    double improvement = ((avgErrorWithoutPID - avgErrorWithPID) / avgErrorWithoutPID) * 100;
    std::cout << "   Improvement: " << std::fixed << std::setprecision(1) << improvement << "%\n";
    
    if (std::ofstream summary("simulation_summary.txt"); summary.is_open()) {
        summary << "=== Simulation Summary ===\n";
        summary << "Initial temperature: " << y0 << "\n";
        summary << "Desired temperature: " << setpoint << "\n";
        summary << "Number of steps: " << n << "\n";
        summary << "PID parameters: Kp=" << Kp << ", Ki=" << Ki << ", Kd=" << Kd << "\n";
        summary << "Average error without PID: " << avgErrorWithoutPID << "\n";
        summary << "Average error with PID: " << avgErrorWithPID << "\n";
        summary << "Improvement: " << improvement << "%\n";
        summary << "\nTo plot graphs run: python plot_temperature.py\n";
        summary.close();
        std::cout << "\nSummary saved to simulation_summary.txt\n";
    }
    
    std::cout << "\nTo plot graphs run the command: python plot_temperature.py\n";
    
    return 0;
}

bool saveToCSV(const std::string& filename, 
               const std::vector<int>& time, 
               const std::vector<double>& values,
               double setpoint)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    
    file << "Time,Value";
    if (setpoint != 0.0) {
        file << ",Setpoint";
    }
    file << std::endl;
    
    for (size_t i = 0; i < values.size(); ++i) {
        file << time[i] << "," << std::fixed << std::setprecision(6) << values[i];
        if (setpoint != 0.0) {
            file << "," << setpoint;
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Data saved to file: " << filename << std::endl;
    return true;
}