/**
 * @file main.cpp
 * @brief Основной файл программы, реализующей ПИД-регулирование температуры
 * @author Соловчук И.Г.
 * @version 1.0
 * @date 2025
 * 
 * @copyright Copyright (c) 2025
 * 
 * @mainpage Система управления температурой с ПИД-регулятором
 * 
 * @section overview Обзор
 * Данная программа предназначена для моделирования системы автоматического
 * управления температурой объекта с использованием дискретного ПИД-регулятора.
 * Объект управления описывается нелинейной математической моделью.
 * 
 * @section features Основные возможности
 * - Моделирование нелинейной динамики объекта
 * - Реализация дискретного ПИД-алгоритма
 * - Визуализация процесса регулирования
 * - Защита от физически некорректных значений
 */

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include "module.h"

/**
 * @brief Выводит заголовок программы на экран
 */
void printProgramHeader() {
    std::cout << "========================================\n";
    std::cout << "   СИСТЕМА УПРАВЛЕНИЯ ТЕМПЕРАТУРОЙ\n";
    std::cout << "      с ПИД-регулятором\n";
    std::cout << "========================================\n\n";
}

/**
 * @brief Выводит шаг моделирования с форматированием
 * @param step Номер текущего шага
 * @param temperature Текущая температура
 * @param control Текущее управляющее воздействие
 * @param error Текущая ошибка регулирования
 */
void printStepInfo(int step, double temperature, double control, double error) {
    std::cout << "Шаг " << std::setw(3) << step << ": ";
    std::cout << "Температура = " << std::fixed << std::setprecision(2) 
              << std::setw(7) << temperature << "°C, ";
    std::cout << "Управление = " << std::setw(6) << control << "%, ";
    std::cout << "Ошибка = " << std::setw(7) << error << "°C\n";
}

/**
 * @brief Основная функция программы
 * @return Код завершения программы (0 - успешно)
 * 
 * @detaileddescription Функция выполняет следующие действия:
 * 1. Запрашивает у пользователя параметры системы
 * 2. Инициализирует переменные состояния
 * 3. Вычисляет коэффициенты ПИД-регулятора
 * 4. Запускает цикл моделирования
 * 5. Выводит результаты на каждом шаге
 * 
 * @note Время моделирования фиксировано - 500 шагов
 * @warning При вводе некорректных параметров поведение системы может быть непредсказуемым
 */
int main() {
    printProgramHeader();
    
    // Константы программы
    const int TOTAL_STEPS = 500;      ///< Общее количество шагов моделирования
    const int PRINT_INTERVAL = 10;    ///< Интервал вывода информации
    const double SAMPLING_TIME = 1.0; ///< Время дискретизации (сек)

    // === 1. Ввод параметров нелинейной модели ===
    std::cout << "ВВЕДИТЕ ПАРАМЕТРЫ НЕЛИНЕЙНОЙ МОДЕЛИ:\n";
    std::cout << "Коэффициенты a, b, c, d: ";
    double model_a;
    double model_b;
    double model_c;
    double model_d;
    std::cin >> model_a; 
    std::cin >> model_b;
    std::cin >> model_c;
    std::cin >> model_d;

    // === 2. Ввод начальных условий ===
    std::cout << "\nВВЕДИТЕ НАЧАЛЬНЫЕ УСЛОВИЯ:\n";
    std::cout << "Температура на шаге 0 и шаге 1: ";
    double temp_0;
    double temp_1;
    std::cin >> temp_0; 
    std::cin >> temp_1;

    // === 3. Ввод параметров ПИД-регулятора ===
    std::cout << "\nВВЕДИТЕ НАСТРОЙКИ ПИД-РЕГУЛЯТОРА:\n";
    std::cout << "Коэффициенты K, T, Td: ";
    double pid_K;
    double pid_T;
    double pid_Td;
    std::cin >> pid_K;
    std::cin >> pid_T;
    std::cin >> pid_Td;

    // === 4. Ввод целевого значения ===
    std::cout << "\nЗАДАЙТЕ ЦЕЛЕВУЮ ТЕМПЕРАТУРУ:\n";
    std::cout << "Температура уставки: ";
    double target_temperature;
    std::cin >> target_temperature;

    // === 5. Инициализация переменных состояния ===
    std::array<double, 3> temperature_history = {temp_0, temp_1, 0.0};
    std::array<double, 2> control_history = {0.0, 0.0};
    
    double previous_error = 0.0;
    double error_before_previous = 0.0;
    double previous_control = 0.0;

    // === 6. Вычисление коэффициентов ПИД ===
    double coeff_q0;
    double coeff_q1;
    double coeff_q2;
    calculatePidCoefficients(pid_K, pid_T, pid_Td, SAMPLING_TIME,
                             coeff_q0, coeff_q1, coeff_q2);

    std::cout << "\nРАСЧЕТНЫЕ КОЭФФИЦИЕНТЫ ПИД-РЕГУЛЯТОРА:\n";
    std::cout << "q0 = " << coeff_q0 << ", q1 = " << coeff_q1 
              << ", q2 = " << coeff_q2 << "\n";

    // === 7. Основной цикл моделирования ===
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "НАЧАЛО МОДЕЛИРОВАНИЯ\n";
    std::cout << std::string(60, '=') << "\n\n";

    for (int current_step = 1; current_step <= TOTAL_STEPS; ++current_step) {
        // Расчет текущей ошибки
        double current_error = calculateError(target_temperature, 
                                              temperature_history[1]);

        // Формирование структуры параметров управления
        ControlParams control_parameters = {
            coeff_q0, coeff_q1, coeff_q2,
            current_error, previous_error, error_before_previous,
            previous_control
        };

        // Расчет управляющего воздействия
        double current_control = calculateControl(control_parameters);
        control_history[0] = current_control;

        // Формирование структуры параметров модели
        ModelParams model_parameters = {
            model_a, model_b, model_c, model_d,
            temperature_history[1], temperature_history[0],
            control_history[0], control_history[1]
        };

        // Расчет новой температуры
        double new_temperature = calculateNonlinearModel(model_parameters);
        temperature_history[2] = new_temperature;

        // Вывод информации о текущем шаге
        if (current_step % PRINT_INTERVAL == 0) {
            printStepInfo(current_step, temperature_history[1], 
                         current_control, current_error);
        }

        // Подготовка структур для обновления состояния
        StateVariables system_state = {
            temperature_history, control_history,
            previous_error, error_before_previous,
            previous_control, current_error
        };

        // Обновление переменных состояния
        updateStateVariables(system_state);
        
        // Обновление локальных переменных
        temperature_history = system_state.y;
        control_history = system_state.u;
        previous_error = system_state.e_prev;
        error_before_previous = system_state.e_prev2;
        previous_control = system_state.u_prev;
    }

    // === 8. Завершение программы ===
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "МОДЕЛИРОВАНИЕ ЗАВЕРШЕНО УСПЕШНО!\n";
    std::cout << std::string(60, '=') << "\n";

    return 0;
}