/**
 * @file main.cpp
 * @brief Основная программа для тестирования ПИД-регулятора
 *
 * Демонстрация работы ПИД-регулятора с различными объектами управления
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "model.h"
#include "pid.h"

/**
 * @brief Моделирование системы с ПИД-регулятором
 * @param plant Объект управления
 * @param pid ПИД-регулятор
 * @param setpoint Задание (уставка)
 * @param simulation_time Время моделирования
 * @param use_nonlinear Флаг использования нелинейной модели
 * @return Вектор результатов [время, задание, выход, управление]
 */
std::vector<std::vector<double>> simulateSystem(
    PlantModel &plant,
    PIDController &pid,
    double setpoint,
    int simulation_time,
    bool use_nonlinear = false)
{
    std::vector<std::vector<double>> results(4);

    plant.setState(0.0, 0.0, 0.0, 0.0);
    pid.reset();

    for (int k = 0; k < simulation_time; k++)
    {
        double y = plant.getOutput();
        double e = setpoint - y;
        double u = pid.calculate(e);

        if (use_nonlinear)
        {
            plant.nonlinearStep(u);
        }
        else
        {
            plant.linearStep(u);
        }

        results[0].push_back(k);
        results[1].push_back(setpoint);
        results[2].push_back(y);
        results[3].push_back(u);
    }

    return results;
}

/**
 * @brief Запись результатов в файл
 * @param results Результаты моделирования
 * @param filename Имя файла
 */
void writeResultsToFile(const std::vector<std::vector<double>> &results, const std::string &filename)
{
    std::ofstream file(filename);
    file << "Time,Setpoint,Output,Control\n";

    for (size_t i = 0; i < results[0].size(); i++)
    {
        file << results[0][i] << "," << results[1][i] << ","
             << results[2][i] << "," << results[3][i] << "\n";
    }

    file.close();
}

int main()
{
    std::cout << "=== Лабораторная работа №3: ПИД-регуляторы ===\n"
              << std::endl;

    // Создание объекта управления
    PlantModel plant(0.8, 0.2, 0.1, 0.05);

    // Тест 1: П-регулятор
    std::cout << "Тест 1: П-регулятор (K=2.0)" << std::endl;
    PIDController p_controller(2.0, 1.0, 0.0, 1.0);
    p_controller.setLimits(-10.0, 10.0);

    auto results_p = simulateSystem(plant, p_controller, 5.0, 50, false);
    // Тест 2: ПИ-регулятор
    std::cout
        << "Тест 2: ПИ-регулятор (K=1.5, Ti=2.0)" << std::endl;
    PIDController pi_controller(1.5, 2.0, 0.0, 1.0);
    pi_controller.setLimits(-10.0, 10.0);

    auto results_pi = simulateSystem(plant, pi_controller, 5.0, 50, false);

    // Тест 3: ПИД-регулятор
    std::cout << "Тест 3: ПИД-регулятор (K=1.2, Ti=1.5, Td=0.5)" << std::endl;
    PIDController pid_controller(1.2, 1.5, 0.5, 1.0);
    pid_controller.setLimits(-10.0, 10.0);

    auto results_pid = simulateSystem(plant, pid_controller, 5.0, 50, false);

    // Тест 4: ПИД-регулятор с нелинейной моделью
    std::cout << "Тест 4: ПИД-регулятор с нелинейной моделью" << std::endl;
    PlantModel nonlinear_plant(0.9, 0.1, 0.3, 0.2);
    PIDController pid_nonlinear(1.0, 2.0, 0.3, 1.0);
    pid_nonlinear.setLimits(-15.0, 15.0);

    auto results_nonlinear = simulateSystem(nonlinear_plant, pid_nonlinear, 5.0, 50, true);

    std::cout << "Моделирование завершено!" << std::endl;

    return 0;
}