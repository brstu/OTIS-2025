#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

TEST(LinearModel_ii02804, ComputesCorrectly) {
    double y = 2.3, u = 3.7, a = 1.5, b = -0.8;
    double expected = a * y + b * u;
    EXPECT_NEAR(linear_model_ii02804(y, u, a, b), expected, 1e-9);
}

TEST(LinearModel_ii02804, ZeroCoefficientsReturnZero) {
    EXPECT_DOUBLE_EQ(linear_model_ii02804(5.1, 4.2, 0.0, 0.0), 0.0);
}

TEST(LinearModel_ii02804, HandlesNegativeInputs) {
    EXPECT_DOUBLE_EQ(linear_model_ii02804(-1.2, -2.3, 1.0, 2.0), -1.2 + (-2.3 * 2.0));
}

TEST(NonLinearModel_ii02804, ComputesExpectedValue) {
    double y = 1.0, y_prev = 0.0, u = 0.5, u_prev = 0.0;
    double a = 2.0, b = 1.0, c = 0.6, d = 1.1;
    double linear_part = a * y + c * u;
    double nonlinear_part = -b * y * y + d * std::sin(u_prev);
    double expected = linear_part + nonlinear_part;
    double result = non_linear_model_ii02804(y, y_prev, u, u_prev, a, b, c, d);
    EXPECT_NEAR(result, expected, 1e-9);
    EXPECT_DOUBLE_EQ(y_prev, y);
}

TEST(NonLinearModel_ii02804, ZeroCoefficientsReturnZero) {
    double y = 2.4, y_prev = 0.0, u = 1.2, u_prev = 0.0;
    EXPECT_DOUBLE_EQ(non_linear_model_ii02804(y, y_prev, u, u_prev, 0, 0, 0, 0), 0.0);
}

TEST(NonLinearModel_ii02804, SinComponentOnlyWorks) {
    double y = 0.0, y_prev = 0.0, u = M_PI / 4, u_prev = 0.0;
    double result = non_linear_model_ii02804(y, y_prev, u, u_prev, 0, 0, 0, 2.5);
    double expected = 2.5 * std::sin(u_prev);
    EXPECT_NEAR(result, expected, 1e-9);
}
