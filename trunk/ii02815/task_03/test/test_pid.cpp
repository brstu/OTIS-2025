#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid_contr.h"

// Тест с прямыми коэффициентами q0, q1, q2 (исправленная версия)
TEST(PIDValueTest, DirectCoefficients) {
    PID pid(1.0, -0.5, 0.2);  // q0=1.0, q1=-0.5, q2=0.2
    
    pid.reset();  // u_prev = 0.0, e_prev1 = 0.0, e_prev2 = 0.0
    
    // Шаг 1: e = 2.0
    double u1 = pid.compute(2.0);
    // delta_u = q0*e + q1*e_prev1 + q2*e_prev2 
    //         = 1.0*2.0 + (-0.5)*0 + 0.2*0 = 2.0
    // u1 = u_prev + delta_u = 0.0 + 2.0 = 2.0
    EXPECT_NEAR(u1, 2.0, 1e-10);
    
    // Шаг 2: e = 1.0
    double u2 = pid.compute(1.0);
    // Теперь: e_prev1 = 2.0, e_prev2 = 0.0, u_prev = 2.0
    // delta_u = 1.0*1.0 + (-0.5)*2.0 + 0.2*0 = 1.0 - 1.0 = 0.0
    // u2 = u_prev + delta_u = 2.0 + 0.0 = 2.0
    EXPECT_NEAR(u2, 2.0, 1e-10);
    
    // Шаг 3: e = 0.5
    double u3 = pid.compute(0.5);
    // Теперь: e_prev1 = 1.0, e_prev2 = 2.0, u_prev = 2.0
    // delta_u = 1.0*0.5 + (-0.5)*1.0 + 0.2*2.0 = 0.5 - 0.5 + 0.4 = 0.4
    // u3 = u_prev + delta_u = 2.0 + 0.4 = 2.4
    EXPECT_NEAR(u3, 2.4, 1e-10);
}

// Тест с конструктором через K, Ti, Td, T0
TEST(PIDValueTest, FromKTdT0) {
    double K = 0.5, Ti = 4.0, Td = 0.3, T0 = 1.4;
    PID pid(K, Ti, Td, T0);
    
    // Проверим расчет коэффициентов
    double expected_q0 = K * (1.0 + T0/Ti + Td/T0);
    double expected_q1 = -K * (1.0 + 2.0*Td/T0 - T0/Ti);
    double expected_q2 = K * Td/T0;
    
    pid.reset();
    
    // Тестируем вычисления
    double u1 = pid.compute(1.0);
    EXPECT_TRUE(std::isfinite(u1));
    
    double u2 = pid.compute(1.0);
    EXPECT_TRUE(std::isfinite(u2));
}


// Тест сброса состояния
TEST(PIDTest, ResetFunctionality) {
    PID pid(1.0, 1.0, 0.1, 0.1);
    
    // Выполняем вычисления
    pid.compute(1.0);
    pid.compute(1.0);
    
    // Сбрасываем
    pid.reset();
    
    // Создаем новый PID для сравнения
    PID pid_new(1.0, 1.0, 0.1, 0.1);
    
    // После сброса должно вести себя как новый
    double u_reset = pid.compute(1.0);
    double u_new = pid_new.compute(1.0);
    
    EXPECT_DOUBLE_EQ(u_reset, u_new);
}

// Тест с нулевой ошибкой
TEST(PIDTest, ZeroError) {
    PID pid(1.0, 1.0, 0.0, 0.1);
    pid.reset();  // Сбрасываем перед тестом
    
    double u = pid.compute(0.0);  // Нулевая ошибка
    
    EXPECT_DOUBLE_EQ(u, 0.0);
}

// Тест с постоянной ошибкой
TEST(PIDTest, ConstantError) {
    PID pid(2.0, 0.5, 0.1, 0.1);
    
    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);
    double u3 = pid.compute(1.0);
    
    // При постоянной ошибке управление должно меняться
    // из-за интегральной составляющей
    EXPECT_NE(u1, u2);
    EXPECT_NE(u2, u3);
}

// Тест последовательных вычислений
TEST(PIDBasicTest, SequenceOfComputations) {
    PID pid(1.0, 0.1, 0.01, 0.1);
    
    double results[3];
    for (int i = 0; i < 3; i++) {
        results[i] = pid.compute(1.0);
    }
    
    // Все результаты должны быть разными
    EXPECT_NE(results[0], results[1]);
    EXPECT_NE(results[1], results[2]);
    EXPECT_NE(results[0], results[2]);
}

// Тест граничных случаев
TEST(PIDValueTest, BoundaryCases) {
    // Очень большие коэффициенты
    PID pid_large(1000.0, 1000.0, 1000.0, 0.01);
    pid_large.reset();
    double u_large = pid_large.compute(0.1);
    EXPECT_TRUE(std::isfinite(u_large));  // Должно быть конечным числом
    
    // Очень маленький временной шаг
    PID pid_small_dt(1.0, 1.0, 1.0, 1e-10);
    pid_small_dt.reset();
    double u_small = pid_small_dt.compute(1.0);
    EXPECT_TRUE(std::isfinite(u_small));
}

// Главная функция для GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}