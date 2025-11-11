 Модульное тестирование моделей температурной системы

 Описание проекта
Проект реализует линейную и нелинейную модели температурной системы с модульными тестами на Google Test.

 Структура проекта

<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Шумский И.Н.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

Использовать следующий фреймворк для модульного тестирования - Google Test.
Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\ii02826\task_02\test.
Исходный код модифицированной программы разместить в каталоге: trunk\ii02826\task_02\src.
В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, gcovr).
Также необходимо отразить выполнение работы в общем файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 -

Код Тестов:

#include <gtest/gtest.h>
#include <iostream>

struct ModelParams{
    double a;
    double b;
    double c;
    double d;
};

// Линейная модель (только параметры a и b)
inline double linear_model(double y_prev, double u, const ModelParams& p) {
    return p.a * y_prev + p.b * u;
}

// Нелинейная модель
inline double nonlinear_model(double y_prev, double y_prev_2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * std::pow(y_prev_2, 2) + p.c * u + p.d * std::sin(u);
}

// Тесты для линейной модели
TEST(LinearModelTest, BasicCalculation) {
    ModelParams params{ 0.5, 0.2, 0.0, 0.0 };
    double result = linear_model(10.0, 5.0, params);
    EXPECT_DOUBLE_EQ(result, 0.5 * 10.0 + 0.2 * 5.0);
}

TEST(LinearModelTest, ZeroInput) {
    ModelParams params{ 1.0, 1.0, 0.0, 0.0 };
    double result = linear_model(0.0, 0.0,params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    ModelParams params{ 2.0, 1.0, 0.0, 0.0 };
    double result = linear_model(-5.0, -3.0, params);
    EXPECT_DOUBLE_EQ(result, 2.0 * (-5.0) + 1.0 * (-3.0));
}

TEST(LinearModelTest, UnitCoefficients) {
    ModelParams params{ 1.0, 1.0, 0.0, 0.0 };
    double result = linear_model(7.5, 2.5, params);
    EXPECT_DOUBLE_EQ(result, 7.5 + 2.5);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BasicCalculation) {
    ModelParams params{ 0.5, 0.1, 0.3, 0.2 };
    double result = nonlinear_model(10.0, 8.0, 5.0, params);
    double expected = 0.5 * 10.0 - 0.1 * std::pow(8.0, 2) + 0.3 * 5.0 + 0.2 * std::sin(5.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, ZeroInput) {
    ModelParams params{ 1.0, 1.0, 1.0, 1.0 };
    double result = nonlinear_model(0.0, 0.0, 0.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, NegativeValues) {
    ModelParams params{ 2.0, 0.5, 1.0, 0.1 };
    double result = nonlinear_model(-3.0, -2.0, -1.0, params);
    double expected = 2.0 * (-3.0) - 0.5 * std::pow(-2.0, 2) + 1.0 * (-1.0) + 0.1 * std::sin(-1.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, ZeroCoefficients) {
    ModelParams params{ 0.0, 0.0, 0.0, 0.0 };
    double result = nonlinear_model(5.0, 3.0, 2.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, SineComponentOnly) {
    ModelParams params{ 0.0, 0.0, 0.0, 1.0 };
    double u = 3.14159265358979323846 / 2;
    double result = nonlinear_model(10.0, 8.0, u, params);
    EXPECT_DOUBLE_EQ(result, std::sin(u));
}

// Тесты для структуры ModelParams
TEST(ModelParamsTest, DefaultInitialization) {
    ModelParams params{};
    EXPECT_DOUBLE_EQ(params.a, 0.0);
    EXPECT_DOUBLE_EQ(params.b, 0.0);
    EXPECT_DOUBLE_EQ(params.c, 0.0);
    EXPECT_DOUBLE_EQ(params.d, 0.0);
}

TEST(ModelParamsTest, CustomInitialization) {
    ModelParams params{ 1.1, 2.2, 3.3, 4.4 };
    EXPECT_DOUBLE_EQ(params.a, 1.1);
    EXPECT_DOUBLE_EQ(params.b, 2.2);
    EXPECT_DOUBLE_EQ(params.c, 3.3);
    EXPECT_DOUBLE_EQ(params.d, 4.4);
}

// Интеграционные тесты
TEST(IntegrationTest, LinearModelStability) {
    ModelParams params{ 0.5, 0.2, 0.0, 0.0 };
    double y_prev = 100.0;
    double u = 10.0;

    for (int i = 0; i < 10; ++i) {
        y_prev = linear_model(y_prev, u, params);
        EXPECT_TRUE(std::isfinite(y_prev));
    }
}

TEST(IntegrationTest, NonlinearModelStability) {
    ModelParams params{ 0.8, 0.01, 0.1, 0.05 };
    double y_prev = 50.0;
    double y_prev_2 = 45.0;
    double u = 5.0;

    for (int i = 0; i < 10; ++i) {
        double y_next = nonlinear_model(y_prev, y_prev_2, u, params);
        y_prev_2 = y_prev;
        y_prev = y_next;
        EXPECT_TRUE(std::isfinite(y_prev));
    }
}

// Тесты на граничные значения
TEST(BoundaryTest, LargeValues) {
    ModelParams params1{ 1.0, 1.0, 0.0, 0.0 };
    double result = linear_model(1e6, 1e6, params1);
    EXPECT_DOUBLE_EQ(result, 2e6);

    ModelParams params2{ 1.0, 1.0, 1.0, 1.0 };
    result = nonlinear_model(1e6, 1e6, 1e6, params2);
    EXPECT_TRUE(std::isfinite(result));
}

TEST(BoundaryTest, SmallValues) {
    ModelParams params1{ 1.0, 1.0, 0.0, 0.0 };
    double result = linear_model(1e-6, 1e-6, params1);
    EXPECT_DOUBLE_EQ(result, 2e-6);

    ModelParams params2{ 1.0, 1.0, 1.0, 1.0 };
    result = nonlinear_model(1e-6, 1e-6, 1e-6, params2);
    EXPECT_TRUE(std::isfinite(result));
}

int main(int argc, char** argv) {
    std::cout << "Running model tests..." << std::endl;

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    std::cout << "Tests completed with result: " << result << std::endl;

    system("pause");

    return result;
}

Результаты тестирования

<img width="418" height="708" alt="Без имени" src="https://github.com/user-attachments/assets/75afdc85-490f-4f0b-ab16-db6e3fb537c9" />

Количество тестов:
Всего написано: 15 модульных тестов
Тесты линейной модели: 4 теста
Тесты нелинейной модели: 5 тестов
Тесты структуры данных: 2 теста
Интеграционные тесты: 2 теста
Тесты граничных значений: 2 теста

Результат выполнения:
 Пройдено: 15 тестов
 Не пройдено: 0 тестов

Общий результат: 100% тестов пройдено

Статус тестов:
LinearModelTest: 4/4 тестов пройдено
NonlinearModelTest: 5/5 тестов пройдено
ModelParamsTest: 2/2 тестов пройдено
IntegrationTest: 2/2 тестов пройдено
BoundaryTest: 2/2 тестов пройдено

Время выполнения: 12 ms 

Покрытие кода

Для анализа покрытия использовался инструмент gcovr.

Процент покрытия: 
