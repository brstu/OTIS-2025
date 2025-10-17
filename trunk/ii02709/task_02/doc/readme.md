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
#include "lab2.h"
#include <cmath>

TEST(NextLinearTest, Basic) {
    long double y = 1.5L;
    long double u = 2.0L;
    long double expected = lab2::a * y + lab2::b * u;
    ASSERT_NEAR(lab2::next_linear(y, u), expected, 1e-15L);
}

TEST(NextNonlinearTest, Basic) {
    long double y = 1.5L;
    long double u = 2.0L;
    long double expected = lab2::a * y - lab2::b * y * y + lab2::c1 * u + lab2::c2 * std::sinh(u);
    ASSERT_NEAR(lab2::next_nonlinear(y, u), expected, 1e-14L);
}

TEST(SimulateLinearTest, LengthAndValues) {
    int steps = 5;
    long double y0 = 1.0L;
    long double u = 0.5L;
    auto vals = lab2::simulate_linear(steps, y0, u);
    ASSERT_EQ((int)vals.size(), steps);
    // проверить первый элемент
    long double first_expected = lab2::next_linear(y0, u);
    ASSERT_NEAR(vals[0], first_expected, 1e-15L);
}

TEST(SimulateNonlinearTest, LengthAndValues) {
    int steps = 5;
    long double y0 = 1.0L;
    long double u = -1.2L; // тест с отрицательным u
    auto vals = lab2::simulate_nonlinear(steps, y0, u);
    ASSERT_EQ((int)vals.size(), steps);
    long double first_expected = lab2::next_nonlinear(y0, u);
    ASSERT_NEAR(vals[0], first_expected, 1e-14L);
}

TEST(SimulateEdgeCases, ZeroSteps) {
    auto v1 = lab2::simulate_linear(0, 1.0L, 0.0L);
    auto v2 = lab2::simulate_nonlinear(0, 1.0L, 0.0L);
    ASSERT_TRUE(v1.empty());
    ASSERT_TRUE(v2.empty());
}

TEST(SimulateEdgeCases, NegativeSteps) {
    EXPECT_THROW(lab2::simulate_linear(-1, 1.0L, 0.0L), std::invalid_argument);
    EXPECT_THROW(lab2::simulate_nonlinear(-5, 1.0L, 0.0L), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

---

# Код программы main.cpp #

#include <iostream>
#include <vector>
#include <iomanip> 
#include "lab2.h"

int main() {
    int steps = 20;
    long double y_linear = 1.5L;
    long double y_nonlinear = 1.5L;
    long double u = 2.0L;

    auto linear_values = lab2::simulate_linear(steps, y_linear, u);
    auto nonlinear_values = lab2::simulate_nonlinear(steps, y_nonlinear, u);

    std::cout << std::setprecision(18);
    std::cout << "Step\tLinear\t\t\tNonLinear\n";
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
#include <stdexcept>

namespace lab2 {

long double next_linear(long double y_current, long double u) {
    return a * y_current + b * u;
}

long double next_nonlinear(long double y_current, long double u) {
    return a * y_current - b * y_current * y_current + c1 * u + c2 * std::sinh(u);
}

std::vector<long double> simulate_linear(int steps, long double y0, long double u) {
    if (steps < 0) throw std::invalid_argument("steps must be non-negative");
    std::vector<long double> values;
    values.reserve(steps);
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        long double next = next_linear(y, u);
        values.push_back(next);
        y = next;
    }
    return values;
}

std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u) {
    if (steps < 0) throw std::invalid_argument("steps must be non-negative");
    std::vector<long double> values;
    values.reserve(steps);
    long double y = y0;
    for (int t = 0; t < steps; ++t) {
        long double next = next_nonlinear(y, u);
        values.push_back(next);
        y = next;
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


#endif

---