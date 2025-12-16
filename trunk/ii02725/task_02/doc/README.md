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
#include <locale>
#include "module.h"

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int N{};
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> N;

    if (N < 0 || N >= 100)
    {
        std::cout << "Ошибка: N должно быть в диапазоне 0 <= N < 100\n";
        return 1;
    }

    double a{}, b{}, c{}, d{};
    std::cout << "Введите константы a, b, c, d через пробел: ";
    std::cin >> a >> b >> c >> d;

    std::vector<double> u(N);
    for (int t = 0; t < N; ++t)
    {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> yLin(N + 1);
    std::vector<double> yNon(N + 1);

    std::cout << "Введите начальную температуру y[0]: ";
    std::cin >> yLin[0];
    yNon[0] = yLin[0];

    if (N > 1)
    {
        std::cout << "Введите y[1] для нелинейной модели: ";
        std::cin >> yNon[1];
    }

    calculate_linear_model(N, a, b, u, yLin);

    if (N > 1)
        calculate_nonlinear_model(N, a, b, c, d, u, yNon);

    std::cout << "\nРезультаты:\n";
    std::cout << "t\ty_lin\ty_nl\n";
    for (int t = 0; t <= N; ++t)
        std::cout << t << "\t" << yLin[t] << "\t" << yNon[t] << "\n";

    return 0;
}

## Код юнит-тестов [ src/modul.cpp ]
#include "module.h"
#include <cmath>

void calculate_linear_model(
        int steps,
        double a,
        double b,
        const std::vector<double>& u,
        std::vector<double>& y
)
{
    for (int i = 0; i < steps; ++i)
    {
        double prevValue = y[i];
        double inputValue = u[i];

        y[i + 1] = a * prevValue + b * inputValue;
    }
}



void calculate_nonlinear_model(
        int total,
        double alpha,
        double beta,
        double gamma,
        double delta,
        const std::vector<double>& u,
        std::vector<double>& y
)
{
    for (int i = 1; i < total; ++i)
    {
        double yt = y[i];
        double ym1 = y[i - 1];

        double ut = u[i];
        double um1 = u[i - 1];

        double part1 = alpha * yt;
        double part2 = beta * ym1 * ym1;
        double part3 = gamma * ut;
        double part4 = delta * std::sin(um1);

        y[i + 1] = part1 - part2 + part3 + part4;
    }
}

## Код юнит-тестов [ src/modul.h ]
#ifndef MODULE_H
#define MODULE_H

#include <vector>

constexpr int MAXIMUM_STEPS = 101;

void calculate_linear_model(
        int nSteps,
        double aCoef,
        double bCoef,
        const std::vector<double>& u,
        std::vector<double>& y
);

void calculate_nonlinear_model(
        int numberOfSteps,
        double a,
        double b,
        double c,
        double d,
        const std::vector<double>& u,
        std::vector<double>& y
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

