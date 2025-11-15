/**
 * @file main.cpp
 * @brief Симуляция ПИД-регулятора с нелинейным объектом
 * @author ii02709
 * @date 14.11.2025
 */

#include "pid_controller.h"
#include "model.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

/**
 * @brief Главная функция моделирования
 * @return 0 при успехе
 */
int main() {
    constexpr double K  = 10.0; 
    constexpr double T  = 0.1;  
    constexpr double TD = 0.05; 
    constexpr double T0 = 0.1;  
    constexpr int steps = 200;  

    PIDController pid(K, T, TD, T0);
    NonlinearModel model;
    double y = 0.0;

    std::ofstream out("../doc/data_pid_step.csv");
    if (!out.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи!\n";
        return 1;
    }

    out << "t,w,y,u\n";

    for (int k = 0; k < steps; ++k) {
        double t = k * T0;
        double w = (k < 100) ? 1.0 : 2.0; 

        double error = w - y;
        double u = pid.compute(error);
        y = model.next(y, u);

        out << t << "," << w << "," << y << "," << u << "\n";
    }

    out.close();
    std::cout << "Симуляция завершена. Данные сохранены в doc/data_pid_step.csv\n";
    return 0;
}