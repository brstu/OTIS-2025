<img width="1261" height="182" alt="image" src="https://github.com/user-attachments/assets/1a4086e7-0af2-4af2-beeb-8c7f748008d8" /><p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Google tests”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Малич А.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.
Использовать следующий фреймворк для модульного тестирования - Google Test.
Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\ii0xxyy\task_02\test.
Исходный код модифицированной программы разместить в каталоге: trunk\ii0xxyy\task_02\src.
В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, gcovr).
Также необходимо отразить выполнение работы в общем файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

## Код модульных тестов

#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

TEST(ModelTest, LinearFunction) {
    double y = 23.0;
    double u = 10.0;
    double a = 0.95;
    double b = 0.002;
    
    double result = linear(y, u, a, b);
    double expected = a * y + b * u;
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(ModelTest, LinearFunctionMultipleSteps) {
    double y = 23.0;
    double a = 0.95;
    double b = 0.002;
    
    double u1 = 10.0;
    y = linear(y, u1, a, b);
    EXPECT_NEAR(y, 21.87, 0.01);
    
    double u2 = 15.0;
    y = linear(y, u2, a, b);
    EXPECT_NEAR(y, 20.8065, 0.01);
}

TEST(ModelTest, NonlinearFunction) {
    double y_current = 23.0;
    double y_prev = 23.0;
    double u = 10.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double result = non_linear(y_current, y_prev, u, a, b, c, d);
    double expected = a * y_current - b * y_prev * y_prev + c * u + d * sin(u);
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST(ModelTest, NonlinearFunctionSequence) {
    double y_prev = 23.0;
    double y_current = 23.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double u1 = 10.0;
    double result1 = non_linear(y_current, y_prev, u1, a, b, c, d);
    EXPECT_NEAR(result1, 21.2376, 0.01);
    
    y_prev = y_current;
    y_current = result1;
    
    double u2 = 15.0;
    double result2 = non_linear(y_current, y_prev, u2, a, b, c, d);
    EXPECT_NEAR(result2, 19.9327, 0.01);
}

TEST(ModelTest, CompareLinearAndNonlinear) {
    double y_linear = 23.0;
    double y_nonlinear_prev = 23.0;
    double y_nonlinear_current = 23.0;
    
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    double u = 10.0;
    
    y_linear = linear(y_linear, u, a, b);
    double y_nonlinear = non_linear(y_nonlinear_current, y_nonlinear_prev, u, a, b, c, d);
    
    EXPECT_NE(y_linear, y_nonlinear);
    EXPECT_NEAR(y_linear, 21.87, 0.01);
    EXPECT_NEAR(y_nonlinear, 21.2376, 0.01);
}

TEST(ModelTest, LinearWithZeroInput) {
    double y = 23.0;
    double u = 0.0;
    double a = 0.95;
    double b = 0.002;
    
    double result = linear(y, u, a, b);
    EXPECT_DOUBLE_EQ(result, a * y);
}

TEST(ModelTest, NonlinearWithZeroInput) {
    double y_current = 23.0;
    double y_prev = 23.0;
    double u = 0.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double result = non_linear(y_current, y_prev, u, a, b, c, d);
    double expected = a * y_current - b * y_prev * y_prev;
    EXPECT_NEAR(result, expected, 1e-10);
}

![test](C:\Users\anton\OneDrive\Изображения\Пленка\google_test.png)



![покрытие]()
