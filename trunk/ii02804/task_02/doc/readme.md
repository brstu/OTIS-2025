<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Гойшик Т.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>


# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/ii0xxyy/task_02/test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk/ii0xxyy/task_02/src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

## Код task_01.cpp ##
```
#include "task_01.h"
#include <cmath>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double non_linear_model(double y, double& y_prev, double u, double& u_prev, const NonLinearParams& p) {
    y_prev = y;  
    double linear_part = p.a * y + p.c * u;
    double nonlinear_part = -p.b * y * y + p.d * std::sin(u); 
    u_prev = u;
    return linear_part + nonlinear_part;
}

```

## Код task_01.h ##
```
#pragma once

struct NonLinearParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_model(double y, double u, double a, double b);
double non_linear_model(double y, double& y_prev, double u, double& u_prev, const NonLinearParams& p);


```

## Код тестов ##
```
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

// Тесты линейной модели
TEST(LinearModel_ii02804, ComputesCorrectly) {
    double y = 2.3;
    double u = 3.7;
    double a = 1.5;
    double b = -0.8;
    double expected = a * y + b * u;
    EXPECT_NEAR(linear_model(y, u, a, b), expected, 1e-9);
}

TEST(LinearModel_ii02804, ZeroCoefficientsReturnZero) {
    EXPECT_DOUBLE_EQ(linear_model(5.1, 4.2, 0.0, 0.0), 0.0);
}

TEST(LinearModel_ii02804, HandlesNegativeInputs) {
    EXPECT_DOUBLE_EQ(linear_model(-1.2, -2.3, 1.0, 2.0), -1.2 + (-2.3 * 2.0));
}

// Тесты нелинейной модели
TEST(NonLinearModel_ii02804, ComputesExpectedValue) {
    double y = 1.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = 0.5;
    NonLinearParams p{2.0, 1.0, 0.6, 1.1};

    double linear_part = p.a * y + p.c * u;
    double nonlinear_part = -p.b * y * y + p.d * std::sin(u);
    double expected = linear_part + nonlinear_part;

    double result = non_linear_model(y, y_prev, u, u_prev, p);
    EXPECT_NEAR(result, expected, 1e-9);
    EXPECT_DOUBLE_EQ(y_prev, y);
}

TEST(NonLinearModel_ii02804, ZeroCoefficientsReturnZero) {
    double y = 2.4;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = 1.2;
    NonLinearParams p{0.0, 0.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(non_linear_model(y, y_prev, u, u_prev, p), 0.0);
}

TEST(NonLinearModel_ii02804, SinComponentOnlyWorks) {
    double y = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = M_PI / 4;
    NonLinearParams p{0.0, 0.0, 0.0, 2.5};

    double result = non_linear_model(y, y_prev, u, u_prev, p);
    double expected = 2.5 * std::sin(u);
    EXPECT_NEAR(result, expected, 1e-9);
}



```
## Результаты тестирования ##
![Результаты тестирования:](https://github.com/tgoyshik/OTIS-2025/blob/task_02/trunk/ii02804/task_02/doc/images/img1.png)
## Покрытие тестами ##
![Покрытие тестами:](https://github.com/tgoyshik/OTIS-2025/blob/task_02/trunk/ii02804/task_02/doc/images/img2.png)
