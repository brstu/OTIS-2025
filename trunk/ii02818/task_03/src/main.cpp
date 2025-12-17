/**
 * @file    main.cpp
 * @brief   Основная программа тестирования ПИД-регулятора
 * @details Тестирование линейной и нелинейной моделей с ПИД-регулятором.
 *          Результаты сохраняются в CSV файлы для дальнейшего анализа.
 * @author  Vladimir
 * @date    2025-12-09
 * @version 1.0
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "pid.h"
#include "model.h"

/**
 * @brief Главная функция программы
 * @return Код завершения программы (0 - успешно)
 * 
 * Программа выполняет два теста:
 * 1. Линейная модель с постоянным задающим воздействием
 * 2. Нелинейная модель с плавным изменением задания
 * 
 * @note Для корректной работы требуется наличие файлов pid.h и model.h
 */
int main() {
    setlocale(LC_ALL,"ru");
    std::cout << "PID Controller - Variant 18\n";
    std::cout << "==========================\n\n";
    
    std::cout << "\n=== TEST 1: Linear Model ===\n";
    
    // Инициализация линейной модели
    Model model_lin(0.2, 0.3, 0.4, 0.5);
    model_lin.init(20.0, 21.0, 0.0, 0.0);
    
    // Инициализация ПИД-регулятора для линейной модели
    PID pid_lin(0.8, 2.0, 0.5, 1.0);
    
    // Создание файла для записи результатов
    std::ofstream file_lin("results_linear.csv");
    file_lin << "Step,Setpoint,Temperature,Control\n";
    
    const double linear_setpoint = 30.0; ///< Задающее воздействие для линейной модели
    
    // Основной цикл моделирования линейной системы
    for (int i = 0; i < 50; i++) {
        double temp = model_lin.getCurrentValue();
        double control = pid_lin.calculate(linear_setpoint, temp);
        model_lin.linearModel(control);
        
        file_lin << i << "," << linear_setpoint << "," << temp << "," << control << "\n";
        
        // Периодический вывод в консоль
        if (i % 10 == 0) {
            std::cout << "Step " << i << ": T=" << temp 
                      << "°C, U=" << control << "%\n";
        }
    }
    
    file_lin.close();
    
    // ============================================================
    
    std::cout << "\n=== TEST 2: Nonlinear Model ===\n";
    
    // Инициализация нелинейной модели
    Model model_nl(0.2, 0.15, 0.4, 0.5);

    double y0 = 21.0;
    model_nl.init(y0, y0, 0.0, 0.0);

    // Инициализация ПИД-регулятора для нелинейной модели
    PID pid_nl(0.3, 5.0, 0.2, 1.0);
    pid_nl.reset();

    std::ofstream file_nl("results_nonlinear.csv");
    file_nl << "Step,Setpoint,Temperature,Control\n";

    const double setpoint_start = y0;           ///< Начальное задание
    const double setpoint_final = 40.0;         ///< Конечное задание
    const int ramp_steps = 20;                  ///< Количество шагов нарастания
    const double U_MAX = 100.0;                 ///< Максимальное значение управления

    // Основной цикл моделирования нелинейной системы
    for (int i = 0; i < 150; i++) {
        // Плавное изменение задания (ramp)
        double current_setpoint = (i < ramp_steps)
            ? setpoint_start + (setpoint_final - setpoint_start) * i / ramp_steps
            : setpoint_final;

        double temp = model_nl.getCurrentValue();

        // Расчет управляющего воздействия
        double control = pid_nl.calculate(current_setpoint, temp);
        if (control > U_MAX) control = U_MAX;
        if (control < 0.0)   control = 0.0;

        // Обновление состояния модели
        model_nl.nonlinearModel(control);

        file_nl << i << "," << current_setpoint << "," << temp << "," << control << "\n";
    }

    file_nl.close();
    
    // ============================================================
    
    std::cout << "\n==========================\n";
    std::cout << "Results saved:\n";
    std::cout << "- Linear model: results_linear.csv\n";
    std::cout << "- Nonlinear model: results_nonlinear.csv\n";
    
    return 0;
}