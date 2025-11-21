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