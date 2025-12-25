#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y01 = 2.0;
    double u01 = 3.0;
    double a01 = 1.5;
    double b01 = -0.5;
    double expected01 = a01 * y01 + b01 * u01;
    EXPECT_DOUBLE_EQ(linear(y01, u01, a01, b01), expected01);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y01 = 1.0;
    double y_p01 = 0.0;
    double u01 = 0.5;
    double a01 = 2.0;
    double b01 = 1.0;
    double c01 = 0.5;
    double d01 = 1.0;

    double expected01 = a01 * y01 - b01 * y01 * y01 + c01 * u01 + d01 * std::sin(u01);
    double result01 = non_linear(y01, y_p01, u01, a01, b01, c01, d01);

    EXPECT_DOUBLE_EQ(result01, expected01);
    EXPECT_DOUBLE_EQ(y_p01, y01);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y01 = 2.0;
    double y_p01 = 0.0;
    double u01 = 1.0;
    double result01 = non_linear(y01, y_p01, u01, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result01, 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y01 = 0.0;
    double y_p01 = 0.0;
    double u01 = M_PI / 2;
    double result01 = non_linear(y01, y_p01, u01, 0.0, 0.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(result01, 2.0);
}