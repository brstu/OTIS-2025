#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y1 = 2.0;
    double u1 = 3.0;
    double a1 = 1.5;
    double b1 = -0.5;
    double expected1 = a1 * y1 + b1 * u1;
    EXPECT_DOUBLE_EQ(linear(y1, u1, a1, b1), expected1);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y2 = 1.0;
    double y2_p2 = 0.0;
    double u2 = 0.5;
    double a2 = 2.0;
    double b2 = 1.0;
    double c2 = 0.5;
    double d2 = 1.0;

    double expected2 = a2 * y2 - b1 * y2 * y2 + c2 * u2 + d2 * std::sin(u2);
    double result2 = non_linear(y2, y2_p2, u2, a2, b2, c2, d2);

    EXPECT_DOUBLE_EQ(result2, expected2);
    EXPECT_DOUBLE_EQ(y2_p2, y2);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y3 = 2.0;
    double y3_p3 = 0.0;
    double u3 = 1.0;
    double result3 = non_linear(y3, y3_p3, u3, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result3, 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y4 = 0.0;
    double y4_p4 = 0.0;
    double u4 = M_PI / 2;
    double result4 = non_linear(y4, y4_p4, u4, 0.0, 0.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(result4, 2.0);
}