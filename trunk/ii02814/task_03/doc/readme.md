<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Козловский Е.Ю.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>
# Общее задание #
1.Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2.Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3.Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4.Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5.Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test.

## Код юнит-тестов [ test/test_3.cpp ]
#include <gtest/gtest.h>
#include <cmath>
#include "../src/module.h"

// Тест 1: Проверка расчета коэффициентов ПИД
TEST(PIDTest, CoefficientsCalculation) {
    double q0, q1, q2;
    calculatePidCoefficients(0.8, 10.0, 0.3, 1.0, q0, q1, q2);
    
    EXPECT_NEAR(q0, 1.04, 0.001);   // 0.8*(1 + 0.3/1) = 1.04
    EXPECT_NEAR(q1, -1.2, 0.001);   // -0.8*(1 + 0.6 - 0.1) = -1.2  
    EXPECT_NEAR(q2, 0.24, 0.001);   // 0.8*0.3 = 0.24
}

// Тест 2: Проверка ограничений управления
TEST(PIDTest, ControlLimits) {
    EXPECT_DOUBLE_EQ(applyControlLimits(150), 100);  // Верхнее ограничение
    EXPECT_DOUBLE_EQ(applyControlLimits(-50), 0);    // Нижнее ограничение
    EXPECT_DOUBLE_EQ(applyControlLimits(75), 75);    // Нормальное значение
}

// Тест 3: Проверка нелинейной модели
TEST(ModelTest, NonlinearModel) {
    double y2 = calculateNonlinearModel(0.9, 0.005, 1.0, 0.1, 20.1, 20.0, 25.0, 0.0);
    
    EXPECT_GT(y2, 20.1);  // Температура должна увеличиться
    EXPECT_GE(y2, 0);     // Температура не отрицательная
}

// Тест 4: Проверка расчета управления ПИД
TEST(PIDTest, ControlCalculation) {
    double control = calculateControl(1.0, -0.5, 0.3, 10.0, 5.0, 3.0, 20.0);
    
    // Δu = 1.0*10 + (-0.5)*5 + 0.3*3 = 10 - 2.5 + 0.9 = 8.4
    // u = 20.0 + 8.4 = 28.4
    EXPECT_NEAR(control, 28.4, 0.001);
    EXPECT_GE(control, 0);    // В пределах ограничений
    EXPECT_LE(control, 100);  // В пределах ограничений
}

## Исходный код: [ main.cpp ]

/**
 * @file main.cpp
 * @brief Главный файл программы с ПИД-регулятором для управления температурой
 * @author Козлоаский Е.Ю. ИИ-28
 * @date 2025
 * 
 * @mainpage Документация ПИД-регулятора
 * 
 * @section intro Введение
 * Программа реализует ПИД-регулятор для управления нелинейным объектом (температурой).
 * Используется дискретная форма ПИД-регулятора и нелинейная модель объекта.
 * 
 * @section algorithm Алгоритм работы
 * 1. Ввод параметров модели объекта и ПИД-регулятора
 * 2. Расчет коэффициентов ПИД-регулятора в дискретной форме
 * 3. Циклическое моделирование системы управления
 * 4. Расчет ошибки, управляющего воздействия и новой температуры
 * 5. Вывод результатов моделирования
 */

#include <iostream>
#include <iomanip>
#include "module.h"

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 * 
 * Функция выполняет моделирование системы управления с ПИД-регулятором.
 * Последовательность работы:
 * - Ввод параметров модели и регулятора
 * - Инициализация переменных состояния
 * - Расчет коэффициентов ПИД-регулятора
 * - Цикл моделирования на 50 шагов
 * - Вывод промежуточных результатов
 * 
 * @note Используется нелинейная модель объекта: 
 *       y(k) = a*y(k-1) - b*y(k-2)^2 + c*u(k-1) + d*sin(u(k-2))
 */
int main() {
    setlocale(LC_ALL, "rus");

    // === 1. Ввод параметров модели объекта (из 1 лабы) ===
    /// @brief Параметры нелинейной модели объекта a, b, c, d
    double a, b, c, d;
    std::cout << "Введите параметры модели a,b,c,d: ";
    std::cin >> a >> b >> c >> d;

    // === 2. Ввод начальных условий ===
    /// @brief Начальные значения температуры y[0] и y[1]
    double y0, y1;
    std::cout << "Введите начальные условия y[0], y[1]: ";
    std::cin >> y0 >> y1;

    // === 3. Ввод параметров ПИД-регулятора ===
    /// @brief Параметры ПИД-регулятора: K - коэффициент усиления, T - постоянная времени, Td - постоянная времени дифференцирования
    double K, T, Td;
    std::cout << "Введите параметры ПИД K,T,Td: ";
    std::cin >> K >> T >> Td;

    // === 4. Ввод желаемой температуры ===
    /// @brief Заданное значение температуры (уставка)
    double setpoint;
    std::cout << "Введите желаемую температуру: ";
    std::cin >> setpoint;

    // === 5. Инициализация переменных ===
    /// @brief Массив температур: y[0], y[1], y[2] - история температур (y(k), y(k-1), y(k-2))
    double y[3] = { y0, y1 };
    /// @brief Массив управлений: u[0], u[1] - история управляющих воздействий (u(k), u(k-1))
    double u[2] = { 0, 0 };

    /// @brief Предыдущее управляющее воздействие u(k-1)
    double u_prev = 0;
    /// @brief Предыдущая ошибка регулирования e(k-1)
    double e_prev = 0;
    /// @brief Предпредыдущая ошибка регулирования e(k-2)
    double e_prev2 = 0;
    /// @brief Шаг квантования (время дискретизации)
    double T0 = 1.0;

    // === 6. Вычисление коэффициентов ПИД ===
    /// @brief Коэффициенты ПИД-регулятора в дискретной форме
    double q0, q1, q2;
    calculatePidCoefficients(K, T, Td, T0, q0, q1, q2);

    std::cout << "Коэффициенты ПИД: q0=" << q0 << ", q1=" << q1 << ", q2=" << q2 << std::endl;

    // === 7. Основной цикл моделирования ===
    /// @brief Основной цикл моделирования системы управления на 50 шагов
    std::cout << "\nНачало моделирования...\n";

    for (int k = 1; k <= 50; k++) {
        // Расчет ошибки
        /// @brief Текущая ошибка регулирования e(k) = setpoint - y(k-1)
        double e_k = calculateError(setpoint, y[1]);

        // Расчет управления
        /// @brief Управляющее воздействие u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
        u[1] = calculateControl(q0, q1, q2, e_k, e_prev, e_prev2, u_prev);

        // Расчет новой температуры
        /// @brief Новая температура по нелинейной модели y(k) = a*y(k-1) - b*y(k-2)^2 + c*u(k-1) + d*sin(u(k-2))
        y[2] = calculateNonlinearModel(a, b, c, d, y[1], y[0], u[1], u[0]);

        // Вывод в консоль
        /// @brief Вывод результатов каждые 10 шагов для мониторинга
        if (k % 10 == 0) {
            std::cout << "Шаг " << k << ": Температура = " << std::fixed << std::setprecision(4) << y[1]
                << ", Управление = " << u[1]
                << ", Ошибка = " << e_k << std::endl;
        }

        // Обновление переменных состояния
        /// @brief Обновление истории температур, управлений и ошибок для следующего шага
        updateStateVariables(y, u, e_prev, e_prev2, u_prev, e_k);
    }

    std::cout << "\nМоделирование завершено!" << std::endl;
    return 0;
}

## Исходный код: [ module.cpp ]
/**
 * @file module.cpp
 * @brief Реализация функций ПИД-регулятора и модели объекта
 * @author Козловский Е.Ю. ИИ-28
 * @date 2025
 */

#include "module.h"
#include <cmath>

/**
 * @brief Расчет коэффициентов ПИД-регулятора для дискретной формы
 */
void calculatePidCoefficients(double K, double T, double Td, double T0, 
                             double& q0, double& q1, double& q2) {
    q0 = K * (1 + Td / T0);
    q1 = -K * (1 + 2 * Td / T0 - T0 / T);
    q2 = K * Td / T0;
}

/**
 * @brief Расчет управляющего воздействия ПИД-регулятором
 */
double calculateControl(double q0, double q1, double q2,
                       double e_k, double e_prev, double e_prev2, 
                       double u_prev) {
    double delta_u = q0 * e_k + q1 * e_prev + q2 * e_prev2;
    double u_k = u_prev + delta_u;
    return applyControlLimits(u_k);
}

/**
 * @brief Применение ограничений к управляющему воздействию
 */
double applyControlLimits(double u) {
    if (u > 100) u = 100;
    if (u < 0) u = 0;
    return u;
}

/**
 * @brief Расчет нелинейной модели объекта управления
 */
double calculateNonlinearModel(double a, double b, double c, double d,
                             double y1, double y0, double u1, double u0) {
    double y2 = a * y1 - b * y0 * y0 + c * u1 + d * sin(u0);
    return applyTemperatureProtection(y2);
}

/**
 * @brief Защита от отрицательной температуры
 */
double applyTemperatureProtection(double temperature) {
    if (temperature < 0) temperature = 0;
    return temperature;
}

/**
 * @brief Расчет ошибки регулирования
 */
double calculateError(double setpoint, double current_value) {
    return setpoint - current_value;
}

/**
 * @brief Обновление переменных состояния для следующей итерации
 */
void updateStateVariables(double y[], double u[], 
                         double& e_prev, double& e_prev2, double& u_prev,
                         double e_k) {
    // Обновление истории температур (y[2] - старейшее, y[0] - новейшее)
    y[2] = y[1];  // y(k-2) ← y(k-1)
    y[1] = y[0];  // y(k-1) ← y(k)
    
    // Обновление истории управлений
    u[2] = u[1];  // u(k-2) ← u(k-1)
    u[1] = u[0];  // u(k-1) ← u(k)
    
    // Обновление переменных ПИД-регулятора
    e_prev2 = e_prev;  // e(k-2) ← e(k-1)
    e_prev = e_k;      // e(k-1) ← e(k)
    u_prev = u[0];     // u(k-1) ← u(k)
}

## Исходный код: [ module.h ]

/**
 * @file module.h
 * @brief Заголовочный файл с функциями ПИД-регулятора и модели объекта
 * @author Козловский Е.Ю. ИИ-28
 * @date 2025
 */

#ifndef MODULE_H
#define MODULE_H

/**
 * @brief Расчет коэффициентов ПИД-регулятора для дискретной формы
 * @param K Коэффициент усиления объекта
 * @param T Постоянная времени объекта
 * @param Td Постоянная времени дифференцирования
 * @param T0 Время дискретизации
 * @param[out] q0 Выходной параметр: коэффициент q0
 * @param[out] q1 Выходной параметр: коэффициент q1  
 * @param[out] q2 Выходной параметр: коэффициент q2
 * 
 * Функция вычисляет коэффициенты ПИД-регулятора в дискретной форме
 * на основе параметров объекта и времени дискретизации.
 */
void calculatePidCoefficients(double K, double T, double Td, double T0, 
                             double& q0, double& q1, double& q2);

/**
 * @brief Расчет управляющего воздействия ПИД-регулятором
 * @param q0 Коэффициент q0 ПИД-регулятора
 * @param q1 Коэффициент q1 ПИД-регулятора
 * @param q2 Коэффициент q2 ПИД-регулятора
 * @param e_k Текущая ошибка регулирования
 * @param e_prev Ошибка на предыдущем шаге
 * @param e_prev2 Ошибка на предпредыдущем шаге
 * @param u_prev Управление на предыдущем шаге
 * @return Рассчитанное управляющее воздействие
 * 
 * Функция реализует алгоритм ПИД-регулятора в дискретной форме:
 * u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
double calculateControl(double q0, double q1, double q2,
                       double e_k, double e_prev, double e_prev2, 
                       double u_prev);

/**
 * @brief Применение ограничений к управляющему воздействию
 * @param u Рассчитанное управляющее воздействие
 * @return Управление с примененными ограничениями
 * 
 * Функция ограничивает управляющее воздействие в диапазоне [0, 100]
 * для предотвращения насыщения исполнительных механизмов.
 */
double applyControlLimits(double u);

/**
 * @brief Расчет нелинейной модели объекта управления
 * @param a Коэффициент a нелинейной модели
 * @param b Коэффициент b нелинейной модели
 * @param c Коэффициент c нелинейной модели
 * @param d Коэффициент d нелинейной модели
 * @param y1 Выход объекта на предыдущем шаге (y(k-1))
 * @param y0 Выход объекта на предпредыдущем шаге (y(k-2))
 * @param u1 Управление на предыдущем шаге (u(k-1))
 * @param u0 Управление на предпредыдущем шаге (u(k-2))
 * @return Текущее значение выхода объекта
 * 
 * Функция реализует нелинейную модель объекта вида:
 * y(k) = a*y(k-1) - b*y(k-2)^2 + c*u(k-1) + d*sin(u(k-2))
 */
double calculateNonlinearModel(double a, double b, double c, double d,
                             double y1, double y0, double u1, double u0);

/**
 * @brief Защита от отрицательной температуры
 * @param temperature Рассчитанная температура
 * @return Скорректированная температура
 * 
 * Функция обеспечивает защиту от физически некорректных 
 * отрицательных значений температуры, ограничивая снизу нулем.
 */
double applyTemperatureProtection(double temperature);

/**
 * @brief Расчет ошибки регулирования
 * @param setpoint Заданное значение (уставка)
 * @param current_value Текущее значение процесса
 * @return Ошибка регулирования
 * 
 * Функция вычисляет разность между заданным и текущим значением.
 * Для систем, где ошибка вычисляется иначе, требуется модификация.
 */
double calculateError(double setpoint, double current_value);

/**
 * @brief Обновление переменных состояния для следующей итерации
 * @param[in,out] y Массив выходных значений объекта
 * @param[in,out] u Массив управляющих воздействий
 * @param[in,out] e_prev Предыдущая ошибка регулирования
 * @param[in,out] e_prev2 Предпредыдущая ошибка регулирования
 * @param[in,out] u_prev Предыдущее управляющее воздействие
 * @param e_k Текущая ошибка регулирования
 * 
 * Функция сдвигает массивы и переменные состояния для подготовки
 * к следующему шагу расчета, сохраняя историю значений.
 */
void updateStateVariables(double y[], double u[], 
                         double& e_prev, double& e_prev2, double& u_prev,
                         double e_k);

#endif

## Результаты юнит-тестирования (GoogleTest)

[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from PIDTest
[ RUN      ] PIDTest.CoefficientsCalculation
[       OK ] PIDTest.CoefficientsCalculation (0 ms)
[ RUN      ] PIDTest.ControlLimits
[       OK ] PIDTest.ControlLimits (0 ms)
[ RUN      ] PIDTest.ControlCalculation
[       OK ] PIDTest.ControlCalculation (0 ms)
[----------] 3 tests from PIDTest (9 ms total)

[----------] 1 test from ModelTest
[ RUN      ] ModelTest.NonlinearModel
[       OK ] ModelTest.NonlinearModel (0 ms)
[----------] 1 test from ModelTest (2 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (22 ms total)
[  PASSED  ] 4 tests.

## Результат действия программы:
https://genji1590.github.io/github_pages/