/**
 * @file test_3.cpp
 * @brief Модульные тесты для системы ПИД-регулирования
 * @author Соловчук И.Г.
 * @version 1.0
 * @date 2025
 * 
 * @copyright Copyright (c) 2025
 * 
 * @test_suite PID_TestSuite Тесты ПИД-регулятора
 * @test_suite Model_TestSuite Тесты модели объекта
 * @test_suite Utility_TestSuite Тесты вспомогательных функций
 */

#include <gtest/gtest.h>
#include <cmath>
#include <array>
#include "../src/module.h"

/**
 * @test Тест расчета коэффициентов ПИД-регулятора
 * @brief Проверка корректности вычисления коэффициентов дискретного ПИД
 * @test_id PID_001
 */
TEST(PID_TestSuite, CoefficientsCalculation) {
    // Тестовые данные
    double K = 0.8;    // Коэффициент усиления
    double T = 10.0;   // Постоянная времени интегрирования
    double Td = 0.3;   // Постоянная времени дифференцирования
    double T0 = 1.0;   // Время дискретизации
    
    double q0, q1, q2;
    
    // Вычисление коэффициентов
    calculatePidCoefficients(K, T, Td, T0, q0, q1, q2);
    
    // Проверка ожидаемых значений (расчет вручную)
    double expected_q0 = K * (1.0 + Td / T0);               // 0.8 * (1 + 0.3) = 1.04
    double expected_q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / T); // -0.8 * (1 + 0.6 - 0.1) = -1.2
    double expected_q2 = K * Td / T0;                      // 0.8 * 0.3 = 0.24
    
    // Проверка с допустимой погрешностью
    EXPECT_NEAR(q0, expected_q0, 0.001);
    EXPECT_NEAR(q1, expected_q1, 0.001);
    EXPECT_NEAR(q2, expected_q2, 0.001);
}

/**
 * @test Тест ограничения управляющего воздействия
 * @brief Проверка функции ограничения сигнала управления
 * @test_id PID_002
 */
TEST(PID_TestSuite, ControlLimitsApplication) {
    // Тест 1: Значение выше верхнего предела
    EXPECT_DOUBLE_EQ(applyControlLimits(150.0), 100.0);
    
    // Тест 2: Значение ниже нижнего предела
    EXPECT_DOUBLE_EQ(applyControlLimits(-50.0), 0.0);
    
    // Тест 3: Значение в допустимом диапазоне
    EXPECT_DOUBLE_EQ(applyControlLimits(75.0), 75.0);
    
    // Тест 4: Граничные значения
    EXPECT_DOUBLE_EQ(applyControlLimits(0.0), 0.0);
    EXPECT_DOUBLE_EQ(applyControlLimits(100.0), 100.0);
    
    // Тест 5: Дробные значения
    EXPECT_DOUBLE_EQ(applyControlLimits(25.5), 25.5);
    EXPECT_DOUBLE_EQ(applyControlLimits(100.1), 100.0);
}

/**
 * @test Тест вычисления управляющего воздействия
 * @brief Проверка алгоритма расчета ПИД-регулятора
 * @test_id PID_003
 */
TEST(PID_TestSuite, ControlSignalCalculation) {
    // Подготовка тестовых данных
    ControlParams params = {
        1.0,    // q0
        -0.5,   // q1
        0.3,    // q2
        10.0,   // e_k
        5.0,    // e_prev
        3.0,    // e_prev2
        20.0    // u_prev
    };
    
    // Расчет управления
    double result = calculateControl(params);
    
    // Проверка вычислений:
    // delta_u = 1.0*10.0 + (-0.5)*5.0 + 0.3*3.0 = 10.0 - 2.5 + 0.9 = 8.4
    // u = 20.0 + 8.4 = 28.4
    double expected_control = 20.0 + (1.0 * 10.0 + (-0.5) * 5.0 + 0.3 * 3.0);
    
    EXPECT_NEAR(result, expected_control, 0.001);
    
    // Дополнительные проверки
    EXPECT_GE(result, 0.0);      // Управление не должно быть отрицательным
    EXPECT_LE(result, 100.0);    // Управление не должно превышать 100%
}

/**
 * @test Тест нелинейной модели объекта
 * @brief Проверка корректности моделирования объекта
 * @test_id MODEL_001
 */
TEST(Model_TestSuite, NonlinearModelSimulation) {
    // Подготовка тестовых данных
    ModelParams params = {
        0.9,    // a
        0.005,  // b
        1.0,    // c
        0.1,    // d
        20.1,   // y1
        20.0,   // y0
        25.0,   // u1
        0.0     // u0
    };
    
    // Расчет выходного значения
    double output = calculateNonlinearModel(params);
    
    // Проверка корректности результата
    EXPECT_GT(output, 0.0);              // Температура должна быть положительной
    EXPECT_FALSE(std::isnan(output));    // Результат не должен быть NaN
    EXPECT_FALSE(std::isinf(output));    // Результат не должен быть бесконечностью
    
    // Проверка расчета (примерные значения)
    double expected_output = params.a * params.y1 -
                           params.b * params.y0 * params.y0 +
                           params.c * params.u1 +
                           params.d * std::sin(params.u0);
    
    EXPECT_NEAR(output, expected_output, 0.001);
}

/**
 * @test Тест функции вычисления ошибки
 * @brief Проверка корректности расчета ошибки регулирования
 * @test_id UTIL_001
 */
TEST(Utility_TestSuite, ErrorCalculation) {
    // Тест 1: Текущее значение ниже уставки
    EXPECT_DOUBLE_EQ(calculateError(25.0, 20.0), 5.0);
    
    // Тест 2: Текущее значение выше уставки
    EXPECT_DOUBLE_EQ(calculateError(25.0, 30.0), -5.0);
    
    // Тест 3: Текущее значение равно уставке
    EXPECT_DOUBLE_EQ(calculateError(25.0, 25.0), 0.0);
    
    // Тест 4: Дробные значения
    EXPECT_DOUBLE_EQ(calculateError(25.5, 25.0), 0.5);
    EXPECT_DOUBLE_EQ(calculateError(25.0, 25.5), -0.5);
}

/**
 * @test Тест защиты температуры
 * @brief Проверка функции ограничения температуры снизу
 * @test_id UTIL_002
 */
TEST(Utility_TestSuite, TemperatureProtection) {
    // Тест 1: Положительная температура
    EXPECT_DOUBLE_EQ(applyTemperatureProtection(25.5), 25.5);
    
    // Тест 2: Нулевая температура
    EXPECT_DOUBLE_EQ(applyTemperatureProtection(0.0), 0.0);
    
    // Тест 3: Отрицательная температура
    EXPECT_DOUBLE_EQ(applyTemperatureProtection(-10.0), 0.0);
    
    // Тест 4: Маленькая положительная температура
    EXPECT_DOUBLE_EQ(applyTemperatureProtection(0.001), 0.001);
}

/**
 * @test Тест обновления переменных состояния
 * @brief Проверка корректности обновления истории системы
 * @test_id UTIL_003
 */
TEST(Utility_TestSuite, StateVariablesUpdate) {
    // Исходное состояние системы
    StateVariables state = {
        {10.0, 20.0, 30.0},  // y: [y(k), y(k-1), y(k-2)]
        {40.0, 50.0},        // u: [u(k), u(k-1)]
        60.0,                // e_prev
        70.0,                // e_prev2
        80.0,                // u_prev
        90.0                 // e_k
    };
    
    // Сохраняем исходные значения для проверки
    double original_y0 = state.y[0];
    double original_y1 = state.y[1];
    double original_u0 = state.u[0];
    double original_e_prev = state.e_prev;
    double original_e_prev2 = state.e_prev2;
    double original_u_prev = state.u_prev;
    double original_e_k = state.e_k;
    
    // Выполняем обновление состояния
    updateStateVariables(state);
    
    // Проверка обновления ошибок
    EXPECT_DOUBLE_EQ(state.e_prev2, original_e_prev);   // e_prev2 ← e_prev
    EXPECT_DOUBLE_EQ(state.e_prev, original_e_k);       // e_prev ← e_k
    
    // Проверка обновления управления
    EXPECT_DOUBLE_EQ(state.u_prev, original_u0);        // u_prev ← u[0]
    
    // Проверка сдвига массива температур
    EXPECT_DOUBLE_EQ(state.y[0], original_y1);          // y[0] ← y[1]
    EXPECT_DOUBLE_EQ(state.y[1], 30.0);                 // y[1] ← y[2] (бывшее значение)
    
    // Проверка сдвига массива управлений
    EXPECT_DOUBLE_EQ(state.u[1], original_u0);          // u[1] ← u[0]
}

/**
 * @test Комплексный тест системы
 * @brief Проверка взаимодействия компонентов системы
 * @test_id SYSTEM_001
 */
TEST(System_TestSuite, IntegratedSystemTest) {
    // Шаг 1: Расчет коэффициентов ПИД
    double q0, q1, q2;
    calculatePidCoefficients(1.0, 5.0, 0.5, 1.0, q0, q1, q2);
    
    EXPECT_GT(q0, 0.0);
    EXPECT_LT(q1, 0.0);
    EXPECT_GT(q2, 0.0);
    
    // Шаг 2: Расчет ошибки
    double error = calculateError(25.0, 20.0);
    EXPECT_DOUBLE_EQ(error, 5.0);
    
    // Шаг 3: Расчет управления
    ControlParams control_params = {q0, q1, q2, error, 0.0, 0.0, 0.0};
    double control = calculateControl(control_params);
    
    EXPECT_GE(control, 0.0);
    EXPECT_LE(control, 100.0);
    
    // Шаг 4: Моделирование объекта
    ModelParams model_params = {0.8, 0.01, 0.5, 0.1, 20.0, 19.0, control, 0.0};
    double temperature = calculateNonlinearModel(model_params);
    
    EXPECT_GE(temperature, 0.0);
    EXPECT_LT(temperature, 100.0);
}

/**
 * @brief Основная функция запуска тестов
 */
int main(int argc, char **argv) {
    // Инициализация тестовой среды
    ::testing::InitGoogleTest(&argc, argv);
    
    // Запуск всех тестов
    return RUN_ALL_TESTS();
}