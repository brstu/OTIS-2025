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
<p align="right">Группы ИИ-28</p>
<p align="right">Маковей Е.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>


# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).


## Код тестов
```C++
#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "../src/models.h"

// Тесты для computeLinear
TEST(ComputeLinearTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(computeLinear(0.0, 0.0, 2.0, 3.0), 0.0);
}

TEST(ComputeLinearTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(computeLinear(2.0, 3.0, 2.0, 3.0), 2.0*2.0 + 3.0*3.0);
}

TEST(ComputeLinearTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(computeLinear(-1.0, -2.0, 1.0, 2.0), -1.0 + -4.0);
}

// Тесты для computeNonlinear
TEST(ComputeNonlinearTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(computeNonlinear(0.0, 0.0, 1.0, 1.0, 1.0, 1.0), 0.0);
}

TEST(ComputeNonlinearTest, PositiveValues) {
    double result = computeNonlinear(2.0, 1.0, 2.0, 1.0, 3.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 4.0 - 4.0 + 3.0);
}

TEST(ComputeNonlinearTest, WithSinus) {
    double result = computeNonlinear(1.0, M_PI/2, 1.0, 0.0, 0.0, 2.0);
    EXPECT_NEAR(result, 1.0 + 2.0*sin(M_PI/2), 1e-9);
}
```

## Результаты тестирования
st_main.cc
[==========] Running 6 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from ComputeLinearTest
[ RUN      ] ComputeLinearTest.ZeroInput
[       OK ] ComputeLinearTest.ZeroInput (0 ms)
[ RUN      ] ComputeLinearTest.PositiveValues
[       OK ] ComputeLinearTest.PositiveValues (0 ms)
[ RUN      ] ComputeLinearTest.NegativeValues
[       OK ] ComputeLinearTest.NegativeValues (0 ms)
[----------] 3 tests from ComputeLinearTest (4 ms total)

[----------] 3 tests from ComputeNonlinearTest
[ RUN      ] ComputeNonlinearTest.ZeroInput
[       OK ] ComputeNonlinearTest.ZeroInput (0 ms)
[ RUN      ] ComputeNonlinearTest.PositiveValues
[       OK ] ComputeNonlinearTest.PositiveValues (0 ms)
[ RUN      ] ComputeNonlinearTest.WithSinus
[       OK ] ComputeNonlinearTest.WithSinus (0 ms)
[----------] 3 tests from ComputeNonlinearTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test suites ran. (12 ms total)
[  PASSED  ] 6 tests.

