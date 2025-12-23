#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

// Тесты линейной модели
TEST(LinearModel_ii02804, ComputesCorrectly) {
    double y = 2.3;
    double u = 3.7;
    double a = 1.5;
    double b = -0.8;
    double expected = a * y + b * u;
    EXPECT_NEAR(linear_model(y, u, a, b), expected, 1e-9);
}

TEST(LinearModel_ii02804, ZeroCoefficientsReturnZero) {
    EXPECT_DOUBLE_EQ(linear_model(5.1, 4.2, 0.0, 0.0), 0.0);
}

TEST(LinearModel_ii02804, HandlesNegativeInputs) {
    EXPECT_DOUBLE_EQ(linear_model(-1.2, -2.3, 1.0, 2.0), -1.2 + (-2.3 * 2.0));
}

// Тесты нелинейной модели
TEST(NonLinearModel_ii02804, ComputesExpectedValue) {
    double y = 1.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = 0.5;
    NonLinearParams p{2.0, 1.0, 0.6, 1.1};

    double linear_part = p.a * y + p.c * u;
    double nonlinear_part = -p.b * y * y + p.d * std::sin(u);
    double expected = linear_part + nonlinear_part;

    double result = non_linear_model(y, y_prev, u, u_prev, p);
    EXPECT_NEAR(result, expected, 1e-9);
    EXPECT_DOUBLE_EQ(y_prev, y);
}

TEST(NonLinearModel_ii02804, ZeroCoefficientsReturnZero) {
    double y = 2.4;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = 1.2;
    NonLinearParams p{0.0, 0.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(non_linear_model(y, y_prev, u, u_prev, p), 0.0);
}

TEST(NonLinearModel_ii02804, SinComponentOnlyWorks) {
    double y = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    double u = M_PI / 4;
    NonLinearParams p{0.0, 0.0, 0.0, 2.5};

    double result = non_linear_model(y, y_prev, u, u_prev, p);
    double expected = 2.5 * std::sin(u);
    EXPECT_NEAR(result, expected, 1e-9);
}
