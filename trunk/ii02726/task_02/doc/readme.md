<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульные тесты”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Юшкевич А.Ю.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>


<hr>


# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

# Выполнение задания #
Код программы:
#include <iostream>
#include <cmath>
#include "test.h"



int main() {
    int max_steps = 100;
    int steps;
    double a;
    double b;
    double c;
    double d;
    double y0;
    double y1;

    std::cout << "enter steps: ";
    std::cin >> steps;
    if (steps > max_steps || steps < 2) {
        std::cout << "Error: steps must be between 2 and 100: \n";
        return 1;
    }

    std::cout << "enter a: \n";
    std::cin >> a;

    std::cout << "enter b: \n";
    std::cin >> b;

    std::cout << "enter c: \n";
    std::cin >> c;

    std::cout << "enter d: \n";
    std::cin >> d;

    std::cout << "enter y0: \n";
    std::cin >> y0;

    std::cout << "enter y1: \n";
    std::cin >> y1;

    std::cout << "enter u: \n";
    std::vector<double> u(steps);
    for (int i = 0; i < steps; i++) {
        std::cout << "u[" << i << "] = ";
        std::cin >> u[i];
    }

    int model;
    std::cout << "choose model: 1-linear; 2-non-linear\n";
    std::cin >> model;

    std::vector<double> y;
    const abcd str_fun {a,b,c,d};

    if (model == 1) {
        y = linear_func(steps, a, b, u, y0, y1);
    } else {
        y = nonlinear_func(steps, str_fun, u, y0, y1);
    }

    for (int i = 0; i < steps; i++) {
        std::cout << "step " << i << ": y = " << y[i] << "\n";
    }

    return 0;
}
#include "test.h"
#include <gtest/gtest.h>
#include <vector>

TEST(LinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = linear_func(1, 0.1, 0.4, u, 0.1, 0.2);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0 + 1.0);
}

TEST(NonLinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = nonlinear_func(3, {0.5, 2.0, 0.1, 0.8}, u, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0*1.0 - 1.0*0.0 + 1.0*1.0 + 0.0);
}#pragma once
#include <vector>

struct abcd{
    double a;
    double b;
    double c;
    double d;
};
enum class ModelType { linear = 1, nonlinear = 2};

std::vector<double> linear_func(int steps, double a, double b, std::vector<double>& u, double y0, double y1);
std::vector<double> nonlinear_func(int steps, const abcd& srt_fun, std::vector<double>& u, double y0, double y1);
#include "test.h"
#include <cmath>

std::vector<double> linear_func(int steps, double a, double b, std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; i++) {
        y[i] = a * y[i-1] + b * u[i-1];
    }
    return y;
}


std::vector<double> nonlinear_func(int steps, const abcd& str_fun, std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; i++) {
        y[i] = str_fun.a * y[i - 1] - str_fun.b * y[i - 2] * y[i - 2] + str_fun.c * u[i - 1] + str_fun.d * std::sin(u[i - 2]);
    }

    return y;
}

Вывод программы:
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 2 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from LinearModelTest
[ RUN      ] LinearModelTest.SimpleCase
[       OK ] LinearModelTest.SimpleCase (0 ms)
[----------] 1 test from LinearModelTest (0 ms total)

[----------] 1 test from NonLinearModelTest
[ RUN      ] NonLinearModelTest.SimpleCase
[       OK ] NonLinearModelTest.SimpleCase (0 ms)
[----------] 1 test from NonLinearModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 2 tests.