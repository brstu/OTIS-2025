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
<p align="right">Ковалевич Е.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
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
## Код модульных тестов ##
```
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y01 = 2.0;
    double u01 = 3.0;
    double a01 = 1.5;
    double b01 = -0.5;
    double expected01 = a01 * y01 + b01 * u01;
    EXPECT_DOUBLE_EQ(linear(y01, u01, a01, b01), expected01);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y01 = 1.0;
    double y01_p01 = 0.0;
    double u01 = 0.5;
    double a01 = 2.0;
    double b01 = 1.0;
    double c01 = 0.5;
    double d01 = 1.0;

    double expected01 = a01 * y01 - b01 * y01 * y01 + c01 * u01 + d01 * std::sin(u01);
    double result01 = non_linear(y01, y01_p01, u01, a01, b01, c01, d01);

    EXPECT_DOUBLE_EQ(result01, expected01);
    EXPECT_DOUBLE_EQ(y01_p01, y01);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y01 = 2.0;
    double y01_p01 = 0.0;
    double u01 = 1.0;
    double result01 = non_linear(y01, y01_p01, u01, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result01, 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y01 = 0.0;
    double y01_p01 = 0.0;
    double u01 = M_PI / 2;
    double result01 = non_linear(y01, y01_p01, u01, 0.0, 0.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(result01, 2.0);
}
```
## Результаты тестирования ##
![Результаты тестирования:](images/img1.png)
## Покрытие тестами (OpenCppCoverage) ##
![Покрытие тестами:](images/img2.png)
