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
<p align="right">Сыч А.Д.</p>
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
    double y1 = 2.0;
    double u1 = 3.0;
    double a1 = 1.5;
    double b1 = -0.5;
    double expected1 = a1 * y1 + b1 * u1;
    EXPECT_DOUBLE_EQ(linear(y1, u1, a1, b1), expected1);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y2 = 1.0;
    double y2_p2 = 0.0;
    double u2 = 0.5;
    double a2 = 2.0;
    double b2 = 1.0;
    double c2 = 0.5;
    double d2 = 1.0;

    double expected2 = a2 * y2 - b1 * y2 * y2 + c2 * u2 + d2 * std::sin(u2);
    double result2 = non_linear(y2, y2_p2, u2, a2, b2, c2, d2);

    EXPECT_DOUBLE_EQ(result2, expected2);
    EXPECT_DOUBLE_EQ(y2_p2, y2);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y3 = 2.0;
    double y3_p3 = 0.0;
    double u3 = 1.0;
    double result3 = non_linear(y3, y3_p3, u3, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result3, 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y4 = 0.0;
    double y4_p4 = 0.0;
    double u4 = M_PI / 2;
    double result4 = non_linear(y4, y4_p4, u4, 0.0, 0.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(result4, 2.0);
}
```
## Результаты тестирования ##
![Результаты тестирования:](images/img1.png)
## Покрытие тестами (OpenCppCoverage) ##
![Покрытие тестами:](images/img2.png)
