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
    // Тестирование граничных значений
    EXPECT_DOUBLE_EQ(TemperatureModel::linearModel(0, 0, 0, 0), 0);
    EXPECT_DOUBLE_EQ(TemperatureModel::linearModel(1, 0, 1, 0), 1);
}