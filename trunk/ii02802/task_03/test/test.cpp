#include <gtest/gtest.h>
#include "pid.h"
#include "control_object.h"

/**
 * @file test.cpp
 * @brief Модульные тесты для классов PID и ControlObject с использованием Google Test.
 */

// Тесты для класса PID
TEST(PIDTest, ConstructorAndCompute) {
    double K = 10.0;
    double Ti = 0.1;
    double Td = 0.05;
    double Ts = 0.01;
    
    PID pid(K, Ti, Td, Ts);
    
    // Проверяем начальные вычисления
    double e1 = 1.0;
    double u1 = pid.compute(e1);
    EXPECT_DOUBLE_EQ(u1, K * (1.0 + Ts / Ti + Td / Ts) * e1);  // Поскольку предыдущие ошибки = 0
    
    double e2 = 0.5;
    double u2 = pid.compute(e2);
    // Расчет на основе формулы
    double expected_u2 = u1 + K * (1.0 + Ts / Ti + Td / Ts) * e2 - K * (1.0 + 2.0 * Td / Ts) * e1 + K * (Td / Ts) * 0.0;
    EXPECT_DOUBLE_EQ(u2, expected_u2);
}

// Тесты для класса ControlObject
TEST(ControlObjectTest, ConstructorAndUpdate) {
    double K_obj = 3.0;
    double T_obj = 0.1;
    double xi = 1.0;
    
    ControlObject obj(K_obj, T_obj, xi);
    
    EXPECT_DOUBLE_EQ(obj.getY(), 0.0);
    
    double u = 1.0;
    double dt = 0.01;
    double y1 = obj.update(u, dt);
    // Простая проверка: y должен измениться
    EXPECT_GT(y1, 0.0);
    
    // Дополнительное обновление для проверки динамики
    double y2 = obj.update(u, dt);
    EXPECT_GT(y2, y1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}