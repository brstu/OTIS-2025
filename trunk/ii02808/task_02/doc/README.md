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
<p align="right">Жукович Е.Д.</p>
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
#include "../src/main.h"


TEST(LinearSimTest, BaseCase)
{
    std::vector<double> result = linearSim(2, 2.0);
    ASSERT_GE(result.size(), 2);
    double expected = 0.8 * 2.0 + 0.6 * 0.8;
    EXPECT_DOUBLE_EQ(result[1], expected);
}

TEST(LinearSimTest, ZeroStartTemp)
{
    std::vector<double> result = linearSim(3, 0.0);
    ASSERT_GE(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 0.6 * 0.8); // 0.48
    EXPECT_DOUBLE_EQ(result[2], 0.8 * 0.48 + 0.6 * 0.8); // 0.384 + 0.48 = 0.864
}

TEST(LinearSimTest, NegativeStartTemp)
{
    std::vector<double> result = linearSim(2, -2.0);
    ASSERT_GE(result.size(), 2);
    double expected = 0.8 * (-2.0) + 0.6 * 0.8; // -1.6 + 0.48 = -1.12
    EXPECT_DOUBLE_EQ(result[1], expected);
}

TEST(NonlinearSimTest, BaseCase)
{
    std::vector<double> result = nonlinearSim(3, 1.0);
    ASSERT_GE(result.size(), 3);
    
    double expected_second = 0.8 * 1.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
    
    double expected_third = 0.8 * result[1] - 0.6 * result[0] * result[0] 
                          + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[2], expected_third);
}

TEST(NonlinearSimTest, ZeroStartTemp)
{
    std::vector<double> result = nonlinearSim(3, 0.0);
    ASSERT_GE(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    
    double expected_second = 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
}

TEST(LinearSimTest, SingleElement)
{
    std::vector<double> result = linearSim(1, 5.0);
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
}

TEST(NonlinearSimTest, TwoElements)
{
    std::vector<double> result = nonlinearSim(2, 3.0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    
    double expected_second = 0.8 * 3.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
}

TEST(LinearSimTest, ZeroSteps)
{
    std::vector<double> result = linearSim(0, 1.0);
    EXPECT_TRUE(result.empty());
}

TEST(NonlinearSimTest, ZeroSteps)
{
    std::vector<double> result = nonlinearSim(0, 1.0);
    EXPECT_TRUE(result.empty());
}

TEST(LinearSimTest, MultipleSteps)
{
    std::vector<double> result = linearSim(5, 10.0);
    ASSERT_EQ(result.size(), 5);
    
    EXPECT_DOUBLE_EQ(result[0], 10.0);
    EXPECT_DOUBLE_EQ(result[1], 0.8 * 10.0 + 0.6 * 0.8); // 8.0 + 0.48 = 8.48
    EXPECT_DOUBLE_EQ(result[2], 0.8 * 8.48 + 0.6 * 0.8); // 6.784 + 0.48 = 7.264
    EXPECT_DOUBLE_EQ(result[3], 0.8 * 7.264 + 0.6 * 0.8); // 5.8112 + 0.48 = 6.2912
    EXPECT_DOUBLE_EQ(result[4], 0.8 * 6.2912 + 0.6 * 0.8); // 5.03296 + 0.48 = 5.51296
}

TEST(NonlinearSimTest, MultipleSteps)
{
    std::vector<double> result = nonlinearSim(4, 2.0);
    ASSERT_EQ(result.size(), 4);
    
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    
    double second_expected = 0.8 * 2.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], second_expected);
    
    double third_expected = 0.8 * result[1] - 0.6 * result[0] * result[0] 
                          + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[2], third_expected);
    
    double fourth_expected = 0.8 * result[2] - 0.6 * result[1] * result[1] 
                           + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[3], fourth_expected);
}

TEST(ComparisonTest, LinearVsNonlinearDifference)
{
    double start_temp = 5.0;
    int n = 4;
    
    auto linear_result = linearSim(n, start_temp);
    auto nonlinear_result = nonlinearSim(n, start_temp);
    
    ASSERT_EQ(linear_result.size(), n);
    ASSERT_EQ(nonlinear_result.size(), n);
    
    EXPECT_DOUBLE_EQ(linear_result[0], nonlinear_result[0]);
    
    for (int i = 1; i < n; i++) {
        EXPECT_NE(linear_result[i], nonlinear_result[i]);
    }
}


```
## Результаты тестирования ##
![Результаты тестирования:](images/img1.png)
## Покрытие тестами (OpenCppCoverage) ##
![Покрытие тестами:](images/img2.png)
