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
<p align="right">Туз Г.C.</p>
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

using namespace std;


float a = 0.5, b = 0.2, c = 0.15, d = 0.3, u = 1.2;


float linearModel(float y1, float u) {
    return a * y1 + b * u;
}


float nonlinearModel(float y0, float y1, float u) {
    return a * y1 - b * y0 * y0 + c * u + d * sin(u);
}


void runLinearModel(int n, float initialY1) {
    float y0, y1, y2;
    y1 = initialY1;
    y0 = y1;
    
    cout << endl << "Linear Model" << endl;
    for (int i = 0; i < n; i++) {
        cout << "t" << i + 1 << " = ";
        y2 = linearModel(y1, u);
        cout << y2 << endl;
        y0 = y1;
        y1 = y2;
    }
}


void runNonlinearModel(int n, float initialY1) {
    float y0, y1, y2;
    y1 = initialY1;
    y0 = y1;
    
    cout << endl << "Nonlinear Model:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "t" << i + 1 << " = ";
        y2 = nonlinearModel(y0, y1, u);
        cout << y2 << endl;
        y0 = y1;
        y1 = y2;
    }
}

int main() {
    float y_temp;
    cout << "y1 = ?";
    cin >> y_temp;
    
    int n = 10;
    runLinearModel(n, y_temp);
    runNonlinearModel(n, y_temp);
    
    return 0;
}
#include <gtest/gtest.h>
#include <cmath>
#include "test.h"


TEST(ModelTest, LinearModelBasic) {
    float result = linearModel(1.0, 1.0);
    EXPECT_FLOAT_EQ(result, 0.7f);
}

TEST(ModelTest, NonlinearModelBasic) {
    float result = nonlinearModel(1.0, 1.0, 1.0);
    float expected = 0.5f - 0.2f + 0.15f + 0.3f * sin(1.0f);
    EXPECT_NEAR(result, expected, 1e-6f);
}

TEST(ModelTest, ZeroInput) {
    EXPECT_FLOAT_EQ(linearModel(0.0, 0.0), 0.0f);
    EXPECT_FLOAT_EQ(nonlinearModel(0.0, 0.0, 0.0), 0.0f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
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