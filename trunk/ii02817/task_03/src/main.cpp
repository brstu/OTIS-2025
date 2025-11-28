#include <iostream>
#include <vector>
#include <fstream>
#include "model.h"
#include "pid.h"

/**
 * @brief Симуляция системы с PID-регулятором
 * @param plant Модель объекта
 * @param pid PID-регулятор
 * @param setpoint Задание
 * @param simulation_time Время симуляции
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
    std::vector<std::vector<double>> results(5);

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
        results[4].push_back(e);
    }

    return results;
}

/**
 * @brief Вывод результатов в консоль
 * @param results Результаты симуляции
 * @param test_name Название теста
 */
void printResultsToConsole(const std::vector<std::vector<double>> &results, const std::string &test_name)
{
    std::cout << "\n"
              << test_name << ":\n";
    std::cout << "Time\tSetpoint\tOutput\t\tControl\t\tE\n";
    std::cout << "----\t--------\t------\t\t-------\t\t-------\n";
    for (size_t i = 0; i < results[0].size(); i++)
    {
        std::cout << results[0][i] << "\t" << results[1][i] << "\t\t"
                  << results[2][i] << "\t\t" << results[3][i] << "\t\t" << results[4][i] << '\n';
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "PID CONTROLLER SIMULATION\n"
              << std::endl;

    // Ввод параметров
    double y0;
    double w;
    int simulation_time;

    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;

    std::cout << "Enter target temperature w: ";
    std::cin >> w;

    std::cout << "Enter number of simulation steps: ";
    std::cin >> simulation_time;

    // Создание моделей объектов
    PlantModel linear_plant(0.8, 0.2, 0.2, 0.15);
    PlantModel nonlinear_plant(0.85, 0.01, 0.15, 0.01);

    linear_plant.setState(y0, 0.0);
    nonlinear_plant.setState(y0, 0.0);

    // Тест 1: PID-регулятор (линейная модель)
    std::cout << "=== TEST 1: PID-controller (linear model) ===" << std::endl;
    PIDController pid_linear(0.4, 3.0, 0.1, 1.0);
    pid_linear.setLimits(w);
    auto results_linear = simulateSystem(linear_plant, pid_linear, w, simulation_time, false);
    printResultsToConsole(results_linear, "PID-controller (linear model)");

    // Тест 2: PID-регулятор (нелинейная модель)
    std::cout << "=== TEST 2: PID-controller (nonlinear model) ===" << std::endl;
    PIDController pid_nonlinear(0.8, 4.0, 0.05, 1.0);
    pid_nonlinear.setLimits(w);
    auto results_nonlinear = simulateSystem(nonlinear_plant, pid_nonlinear, w, simulation_time, true);
    printResultsToConsole(results_nonlinear, "PID-controller (nonlinear model)");

    std::cout << "SIMULATION COMPLETED" << std::endl;
    return 0;
}