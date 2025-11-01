#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y = 2.0;
    double u = 3.0;
    double a = 1.5;
    double b = -0.5;
    double expected = a * y + b * u;
    EXPECT_DOUBLE_EQ(linear(y, u, a, b), expected);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y = 1.0;
    double y_p = 0.0;
    double u = 0.5;
    double a = 2.0;
    double b = 1.0;
    double c = 0.5;
    double d = 1.0;

    double expected = a * y - b * y * y + c * u + d * std::sin(u);
    double result = non_linear(y, y_p, u, a, b, c, d);

    EXPECT_DOUBLE_EQ(result, expected);
    EXPECT_DOUBLE_EQ(y_p, y);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y = 2.0;
    double y_p = 0.0;
    double u = 1.0;
    double result = non_linear(y, y_p, u, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y = 0.0;
    double y_p = 0.0;
    double u = M_PI / 2;
    double result = non_linear(y, y_p, u, 0.0, 0.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(result, 2.0);
}