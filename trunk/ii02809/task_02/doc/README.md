<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Заремская Е.П.</p>
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
```
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>


TEST(LinearModelTest, PositiveValues) {
    ModelParams params{2.0, 3.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(1.0, 4.0, params), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearModelTest, ZeroInput) {
    ModelParams params{1.5, 2.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0, params), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    ModelParams params{-1.0, 2.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(3.0, -4.0, params), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(NonlinearModelTest, BasicCalculation) {
    ModelParams params{1.0, 1.0, 1.0, 1.0};
    double res = nonlinearModel(1.0, 1.0, 1.0, 0.0, params);
    EXPECT_NEAR(res, 1.0 * 1.0 - 1.0 * 1.0 * 1.0 + 1.0 * 1.0 + 1.0 * sin(0.0), 1e-9);
}

TEST(NonlinearModelTest, IncludesSineTerm) {
    ModelParams params{1.0, 0.0, 0.0, 1.0};
    double res1 = nonlinearModel(1.0, 0.0, 1.0, M_PI / 2, params);
    EXPECT_NEAR(res1, 1.0 * 1.0 - 0.0 + 0.0 * 1.0 + 1.0 * sin(M_PI / 2), 1e-9);
}

TEST(NonlinearModelTest, NegativeInput) {
    ModelParams params{-1.0, 1.0, 2.0, -1.0};
    double res = nonlinearModel(2.0, 1.0, -2.0, M_PI, params);
    double expected = -1.0 * 2.0 - 1.0 * 1.0 * 1.0 + 2.0 * -2.0 - 1.0 * sin(M_PI);
    EXPECT_NEAR(res, expected, 1e-9);
}

```
Результаты тестов:


![[image/cover.png]]


![[image/google.png]]