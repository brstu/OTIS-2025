<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Хотенко В.В.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).


## Код юнит-тестов [ src/main.cpp ]
#include <iostream>
#include <vector>
#include <cmath>
#include <locale>
#include "module.h"

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    int steps_count;
    
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> steps_count;
    
    bool invalid_count = steps_count >= 100;

    if (bool negative_count = steps_count < 0; invalid_count || negative_count)
    {
        std::cout << "Ошибка: N должно быть в диапазоне 0 <= N < 100\n";
        return 1;
    }

    double parameter_a;
    
    double parameter_b;
    
    double parameter_c;
    
    double parameter_d;
    
    std::cout << "Введите константы a, b, c, d через пробел: ";
    std::cin >> parameter_a;
    std::cin >> parameter_b;
    std::cin >> parameter_c;
    std::cin >> parameter_d;

    std::vector<double> input_values(steps_count);
    
    if (steps_count > 0)
    {
        std::cout << "Введите значения u(t) для t = 0." << steps_count - 1 << ":\n"; 
        
        for (int current_time = 0; current_time < steps_count; ++current_time)
        {
            std::cout << "u[" << current_time << "] = ";
            std::cin >> input_values[current_time];
        }
    }

    std::vector<double> linear_output(steps_count + 1, 0.0);
    
    std::vector<double> nonlinear_output(steps_count + 1, 0.0);

    if (steps_count > 0)
    {
        std::cout << "Введите начальную температуру y[0]: ";
        std::cin >> linear_output[0];
        nonlinear_output[0] = linear_output[0];
    }

    if (bool need_second_value = steps_count > 1; need_second_value)
    {
        std::cout << "Введите y[1] для нелинейной модели: ";
        std::cin >> nonlinear_output[1];
    }

    if (steps_count > 0)
    {
        calculate_linear_model(steps_count, parameter_a, parameter_b, input_values, linear_output);
        
        if (bool calculate_nonlinear = steps_count > 1; calculate_nonlinear)
        {
            calculate_nonlinear_model(steps_count, parameter_a, parameter_b, parameter_c, parameter_d, input_values, nonlinear_output);
        }
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t\ty_lin\ty_nl\n";
    
    for (int output_time = 0; output_time <= steps_count; ++output_time)
    {
        std::cout << output_time << "\t" << linear_output[output_time] << "\t" << nonlinear_output[output_time] << "\n";
    }

    return 0;
}

## Код юнит-тестов [ src/modul.cpp ]
#include "module.h"
#include <cmath>

void calculate_linear_model(
    int total_steps,
    double coefficient_a,
    double coefficient_b,
    const std::vector<double>& input_signal,
    std::vector<double>& linear_result
)
{
    for (int current_step = 0; current_step < total_steps; ++current_step)
    {
        int next_index = current_step + 1;
        double current_value = linear_result[current_step];
        double input_value = input_signal[current_step];
        
        linear_result[next_index] = coefficient_a * current_value + coefficient_b * input_value;
    }
}

void calculate_nonlinear_model(
    int iteration_count,
    double alpha,
    double beta,
    double gamma,
    double delta,
    const std::vector<double>& control_input,
    std::vector<double>& nonlinear_result
)
{
    for (int step_index = 1; step_index < iteration_count; ++step_index)
    {
        bool valid_previous_index = step_index - 1 >= 0;
        bool valid_current_index = step_index < static_cast<int>(nonlinear_result.size());
        
        if (valid_previous_index && valid_current_index)
        {
            double first_component = alpha * nonlinear_result[step_index];
            
            double second_component = beta * nonlinear_result[step_index - 1];
            second_component = second_component * nonlinear_result[step_index - 1];
            
            double third_component = gamma * control_input[step_index];
            
            double fourth_component = delta * std::sin(control_input[step_index - 1]);
            
            int target_index = step_index + 1;
            
            nonlinear_result[target_index] = first_component - second_component + third_component + fourth_component;
        }
    }
}

## Код юнит-тестов [ src/modul.h ]
#ifndef MODULE_H
#define MODULE_H

#include <vector>

const int MAXIMUM_STEPS = 101;

void calculate_linear_model(
    int total_steps,
    double coefficient_a,
    double coefficient_b,
    const std::vector<double>& input_signal,
    std::vector<double>& linear_result
);

void calculate_nonlinear_model(
    int iteration_count,
    double alpha,
    double beta,
    double gamma,
    double delta,
    const std::vector<double>& control_input,
    std::vector<double>& nonlinear_result
);

#endif

## Код юнит-тестов [ tests/test.cpp ]
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/module.h"

TEST(LinearModelTest, BasicCalculation)
{
    int steps = 3;
    double coeff_a = 0.5;
    double coeff_b = 1.0;
    std::vector<double> inputs = {1.0, 2.0, 3.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 1.0;

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[1], 1.5, 1e-10);
    EXPECT_NEAR(results[2], 2.75, 1e-10);
    EXPECT_NEAR(results[3], 4.375, 1e-10);
}

TEST(LinearModelTest, OneStep)
{
    int steps = 1;
    double coeff_a = 1.0;
    double coeff_b = 2.0;
    std::vector<double> inputs = {5.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 10.0;

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[1], 20.0, 1e-10);
}

TEST(LinearModelTest, NoSteps)
{
    int steps = 0;
    double coeff_a = 1.0;
    double coeff_b = 1.0;
    std::vector<double> inputs = {};
    std::vector<double> results(1, 10.0);

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[0], 10.0, 1e-10);
    EXPECT_EQ(results.size(), 1);
}

TEST(NonlinearModelTest, TwoStepsCase)
{
    int steps = 2;
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double delta = 1.0;
    std::vector<double> inputs = {1.0, 2.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 5.0;
    results[1] = 10.0;

    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);

    EXPECT_NEAR(results[2], -12.15852902, 1e-8);
}

TEST(NonlinearModelTest, SingleStepNoComputation)
{
    int steps = 1;
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double delta = 1.0;
    std::vector<double> inputs = {1.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 5.0;
    results[1] = 10.0;

    double initial_value = results[0];
    double second_value = results[1];
    
    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);

    EXPECT_NEAR(results[0], initial_value, 1e-10);
    EXPECT_NEAR(results[1], second_value, 1e-10);
}

TEST(NonlinearModelTest, ThreeStepsCase)
{
    int steps = 3;
    double alpha = 0.5;
    double beta = 0.2;
    double gamma = 1.5;
    double delta = 0.8;
    std::vector<double> inputs = {0.5, 1.0, 1.5};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 2.0;
    results[1] = 3.0;
    
    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);
    
    EXPECT_NEAR(results[2], 2.5835404309, 1e-9);
}

Google Test:
[==========] Running 6 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.BasicCalculation
[       OK ] LinearModelTest.BasicCalculation (0 ms)
[ RUN      ] LinearModelTest.OneStep
[       OK ] LinearModelTest.OneStep (0 ms)
[ RUN      ] LinearModelTest.NoSteps
[       OK ] LinearModelTest.NoSteps (0 ms)
[----------] 3 tests from LinearModelTest (6 ms total)

[----------] 3 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.TwoStepsCase
[       OK ] NonlinearModelTest.TwoStepsCase (0 ms)
[ RUN      ] NonlinearModelTest.SingleStepNoComputation
[       OK ] NonlinearModelTest.SingleStepNoComputation (0 ms)
[ RUN      ] NonlinearModelTest.ThreeStepsCase
[       OK ] NonlinearModelTest.ThreeStepsCase (0 ms)
[----------] 3 tests from NonlinearModelTest (8 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test suites ran. (22 ms total)
[  PASSED  ] 6 tests.


Gcovr (перед этим запустили main)
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
main.cpp                                      38      33    86%   20-21,64-65,74
modul.cpp                                     20      20   100%
------------------------------------------------------------------------------
TOTAL                                         58      53    91%
------------------------------------------------------------------------------

