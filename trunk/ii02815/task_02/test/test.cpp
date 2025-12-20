#include <gtest/gtest.h>
#include "../src/model.h"

TEST(LinearModelTest, BasicCalculation) {
    ModelParameters params{ 0.5, 0.3, 0, 0 };
    double result = linearModel(2.0, 1.0, params);
    EXPECT_DOUBLE_EQ(result, 0.5 * 2.0 + 0.3 * 1.0);
}

TEST(LinearModelTest, ZeroParameters) {
    ModelParameters params{ 0.0, 0.0, 0, 0 };
    double result = linearModel(5.0, 3.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    ModelParameters params{ -1.0, -2.0, 0, 0 };
    double result = linearModel(3.0, 4.0, params);
    EXPECT_DOUBLE_EQ(result, -3.0 - 8.0);
}

TEST(NonlinearModelTest, BasicCalculation) {
    ModelParameters params{ 1.0, 0.1, 0.5, 0.2 };
    double result = nonlinearModel(2.0, 1.0, 3.0, 0.5, params);
    double expected = 1.0 * 2.0 - 0.1 * 1.0 * 1.0 + 0.5 * 3.0 + 0.2 * sin(0.5);
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST(NonlinearModelTest, ZeroParameters) {
    ModelParameters params{ 0.0, 0.0, 0.0, 0.0 };
    double result = nonlinearModel(5.0, 3.0, 2.0, 1.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, SinFunction) {
    ModelParameters params{ 0.0, 0.0, 0.0, 1.0 };
    double result = nonlinearModel(0.0, 0.0, 0.0, 0.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);

    result = nonlinearModel(0.0, 0.0, 0.0, 3.14159265358979323846 / 2, params);
    EXPECT_NEAR(result, 1.0, 1e-10);
}