#include <gtest/gtest.h>
#include <cmath>
#include "../src/module.h"

/**
 * @brief Тест расчета коэффициентов ПИД
 */
TEST(PIDTest, CoefficientsCalculation) {
    double q0;
    double q1;
    double q2;
    calculatePidCoefficients(0.8, 10.0, 0.3, 1.0, q0, q1, q2);
    
    EXPECT_NEAR(q0, 1.04, 0.001);
    EXPECT_NEAR(q1, -1.2, 0.001);  
    EXPECT_NEAR(q2, 0.24, 0.001);
}

/**
 * @brief Тест ограничений управления
 */
TEST(PIDTest, ControlLimits) {
    EXPECT_DOUBLE_EQ(applyControlLimits(150), 100);
    EXPECT_DOUBLE_EQ(applyControlLimits(-50), 0);
    EXPECT_DOUBLE_EQ(applyControlLimits(75), 75);
}

/**
 * @brief Тест нелинейной модели
 */
TEST(ModelTest, NonlinearModel) {
    ModelParams params = {0.9, 0.005, 1.0, 0.1, 20.1, 20.0, 25.0, 0.0};
    double y2 = calculateNonlinearModel(params);
    
    EXPECT_GT(y2, 20.1);
    EXPECT_GE(y2, 0);
}

/**
 * @brief Тест расчета управления ПИД
 */
TEST(PIDTest, ControlCalculation) {
    ControlParams params = {1.0, -0.5, 0.3, 10.0, 5.0, 3.0, 20.0};
    double control = calculateControl(params);
    
    EXPECT_NEAR(control, 28.4, 0.001);
    EXPECT_GE(control, 0);
    EXPECT_LE(control, 100);
}