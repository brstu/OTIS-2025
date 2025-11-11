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
<p align="right">Олексюк И.В.</p>
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
#include <gtest/gtest.h>
#include <cmath>
#include "functions.h"

TEST(TemperatureModelTest, LinearModelCalculation) {
    EXPECT_DOUBLE_EQ(TemperatureModel::linearModel(1.0, 2.0, 0.5, 0.3), 1.0 * 0.5 + 2.0 * 0.3);
}

TEST(TemperatureModelTest, NonlinearModelCalculation) {
    double result = TemperatureModel::nonlinearModel(1.0, 0.5, 2.0, 1.5, 0.5, 0.1, 0.2, 0.3);
    double expected = 0.5 * 1.0 - 0.1 * 0.5 * 0.5 + 0.2 * 2.0 + 0.3 * sin(1.5);
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST(TemperatureModelTest, ValidateInputPositive) {
    EXPECT_TRUE(TemperatureModel::validateInput(5.0));
    EXPECT_TRUE(TemperatureModel::validateInput(-3.14));
    EXPECT_TRUE(TemperatureModel::validateInput(0.0));
}

TEST(TemperatureModelTest, ValidateInputNegative) {
    EXPECT_FALSE(TemperatureModel::validateInput(NAN));
    EXPECT_FALSE(TemperatureModel::validateInput(INFINITY));
}

TEST(TemperatureModelTest, ValidateSteps) {
    EXPECT_TRUE(TemperatureModel::validateSteps(1));
    EXPECT_TRUE(TemperatureModel::validateSteps(100));
    EXPECT_FALSE(TemperatureModel::validateSteps(0));
    EXPECT_FALSE(TemperatureModel::validateSteps(-5));
}

TEST(TemperatureModelTest, BoundaryValues) {
    EXPECT_DOUBLE_EQ(TemperatureModel::linearModel(0, 0, 0, 0), 0);
    EXPECT_DOUBLE_EQ(TemperatureModel::linearModel(1, 0, 1, 0), 1);
}