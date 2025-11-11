<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учебное заведение</p>
<p align="center">Брестский государственный технический университет</p>
<p align="center">Кафедра информационных и интеллектуальных технологий</p>
<div style="margin-bottom: 8em;"></div>
<p align="center">Лабораторная работа №2</p>
<p align="center">Дисциплина: «Общая теория интеллектуальных систем»</p>
<p align="center">Тема: «Написать модульные тесты для программы, разработанной в лабораторной работе №1.»</p>
<div style="margin-bottom: 8em;"></div>
<p align="right">Автор работы:</p>
<p align="right">Студент второго курса</p>
<p align="right">Группа ИИ-27/24</p>
<p align="right">Козел А. В.</p>
<p align="right">Преподаватель:</p>
<p align="right">Иванюк Д. С.</p>
<div style="margin-bottom: 8em;"></div>
<p align="center">Брест, 2025</p>

---

# Задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

Использовать следующий фреймворк для модульного тестирования - Google Test.
Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\ii02709\task_02\test.
Исходный код модифицированной программы разместить в каталоге: trunk\ii02709\task_02\src.
В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, gcovr).
Также необходимо отразить выполнение работы в общем файле readme.md в соответствующей строке.

# Код программы test_lab2.cpp #

#include <gtest/gtest.h>
#include <cmath>
#include "../src/lab2.h"

TEST(Lab2Test, LinearUpdateWorks) {
    long double y = 1.5L, u = 2.0L;
    long double expected = lab2::a * y + lab2::b * u;
    EXPECT_NEAR(lab2::next_linear(y, u), expected, 1e-9);
}

TEST(Lab2Test, NonlinearUpdateWorks) {
    long double y = 1.5L, u = 2.0L;
    long double expected = lab2::a * y - lab2::b * y * y + lab2::c1 * u + lab2::c2 * std::sinh(u);
    EXPECT_NEAR(lab2::next_nonlinear(y, u), expected, 1e-9);
}

TEST(Lab2Test, LinearSimulationNegativeStepsReturnsEmpty) {
    auto result = lab2::simulate_linear(-1, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, NonlinearSimulationNegativeStepsReturnsEmpty) {
    auto result = lab2::simulate_nonlinear(-1, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, LinearSimulationProducesExpectedSequence) {
    auto result = lab2::simulate_linear(3, 1.0L, 2.0L);
    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.9L * 1.0L + 0.5L * 2.0L, 1e-9);  // Шаг 1
    EXPECT_NEAR(result[1], 0.9L * result[0] + 0.5L * 2.0L, 1e-9);  // Шаг 2
    EXPECT_NEAR(result[2], 0.9L * result[1] + 0.5L * 2.0L, 1e-9);  // Шаг 3
}

TEST(Lab2Test, NonlinearSimulationProducesExpectedSequence) {
    auto result = lab2::simulate_nonlinear(3, 1.0L, 2.0L);
    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.9L * 1.0L - 0.5L * 1.0L * 1.0L + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 1
    EXPECT_NEAR(result[1], 0.9L * result[0] - 0.5L * result[0] * result[0] + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 2
    EXPECT_NEAR(result[2], 0.9L * result[1] - 0.5L * result[1] * result[1] + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 3
}

TEST(Lab2Test, LinearSimulationZeroStepsReturnsEmpty) {
    auto result = lab2::simulate_linear(0, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, NonlinearSimulationZeroStepsReturnsEmpty) {
    auto result = lab2::simulate_nonlinear(0, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

---

# Код программы main.cpp #

#include <iostream>
#include <vector>
#include "lab2.h"

int main() {
    int steps = 20;
    long double y0 = 1.5L;
    long double u = 2.0L;

    auto linear_values = lab2::simulate_linear(steps, y0, u);
    auto nonlinear_values = lab2::simulate_nonlinear(steps, y0, u);

    std::cout << "Step\tLinear\t\tNonLinear\n";
    for (int t = 0; t < steps; ++t) {
        std::cout << t << "\t" 
                  << linear_values[t] << "\t"
                  << nonlinear_values[t] << "\n";
    }
    return 0;
}

---

# Код программы lab2.cpp #

#include "lab2.h"
#include <cmath>

namespace lab2 {

long double next_linear(long double y_current, long double u) {
    return a * y_current + b * u;
}

long double next_nonlinear(long double y_current, long double u) {
    return a * y_current - b * y_current * y_current + c1 * u + c2 * std::sinh(u);
}

std::vector<long double> simulate_linear(int steps, long double y0, long double u) {
    if (steps < 0) return {};
    std::vector<long double> values;
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        y = next_linear(y, u);
        values.push_back(y);
    }
    return values;
}

std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u) {
    if (steps < 0) return {};
    std::vector<long double> values;
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        y = next_nonlinear(y, u);
        values.push_back(y);
    }
    return values;
}

}

---

# Код программы lab2.h #

#ifndef LAB2_H
#define LAB2_H

#include <vector>

namespace lab2 {
constexpr long double a = 0.9L;
constexpr long double b = 0.5L;
constexpr long double c1 = 0.1L;
constexpr long double c2 = 0.05L;
long double next_linear(long double y_current, long double u);
long double next_nonlinear(long double y_current, long double u);
std::vector<long double> simulate_linear(int steps, long double y0, long double u);
std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u);

}

#endif

---

# Результат тестов #

Running main() from C:\Users\user\OTIS-2025\trunk\ii02709\task_02\test\build\_deps\googletest-src\googletest\src\gtest_main.cc
[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from Lab2Test
[ RUN      ] Lab2Test.LinearUpdateWorks
[       OK ] Lab2Test.LinearUpdateWorks (0 ms)
[ RUN      ] Lab2Test.NonlinearUpdateWorks
[       OK ] Lab2Test.NonlinearUpdateWorks (0 ms)
[ RUN      ] Lab2Test.LinearSimulationNegativeStepsReturnsEmpty
[       OK ] Lab2Test.LinearSimulationNegativeStepsReturnsEmpty (0 ms)
[ RUN      ] Lab2Test.NonlinearSimulationNegativeStepsReturnsEmpty
[       OK ] Lab2Test.NonlinearSimulationNegativeStepsReturnsEmpty (0 ms)
[ RUN      ] Lab2Test.LinearSimulationProducesExpectedSequence
[       OK ] Lab2Test.LinearSimulationProducesExpectedSequence (0 ms)
[ RUN      ] Lab2Test.NonlinearSimulationProducesExpectedSequence
[       OK ] Lab2Test.NonlinearSimulationProducesExpectedSequence (0 ms)
[ RUN      ] Lab2Test.LinearSimulationZeroStepsReturnsEmpty
[       OK ] Lab2Test.LinearSimulationZeroStepsReturnsEmpty (0 ms)
[ RUN      ] Lab2Test.NonlinearSimulationZeroStepsReturnsEmpty
[       OK ] Lab2Test.NonlinearSimulationZeroStepsReturnsEmpty (0 ms)
[----------] 8 tests from Lab2Test (78 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (97 ms total)
[  PASSED  ] 8 tests.

---

Review

![alt text](image.png)

---