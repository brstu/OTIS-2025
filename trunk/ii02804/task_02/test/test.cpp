#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/task_01.h"
#include <cmath>

// === Тесты линейной модели ===
TEST(LinearModelSuite, CalculatesCorrectly) {
    double y = 2.1;
    double u = 3.2;
    double a = 1.4;
    double b = -0.6;
    double expected = a * y + b * u;

    EXPECT_NEAR(linear(y, u, a, b), expected, 1e-9);
}

TEST(LinearModelSuite, HandlesZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.5, 4.4, 0.0, 0.0), 0.0);
}

TEST(LinearModelSuite, WorksWithNegatives) {
    EXPECT_DOUBLE_EQ(linear(-1.5, -2.5, 1.0, 2.0), -1.5 + (-2.5 * 2.0));
}

// === Тесты нелинейной модели ===
TEST(NonLinearModelSuite, ComputesExpectedValue) {
    double y = 0.9;
    double y_prev = 0.0;
    double u = 0.45;
    double a = 2.1;
    double b = 0.95;
    double c = 0.55;
    double d = 1.05;

    double expected = a * y - b * y * y + c * u + d * std::sin(u);
    double result = non_linear(y, y_prev, u, a, b, c, d);

    EXPECT_NEAR(result, expected, 1e-9);
    EXPECT_DOUBLE_EQ(y_prev, y);
}

TEST(NonLinearModelSuite, ZeroCoeffsGiveZero) {
    double y = 2.2;
    double y_prev = 0.0;
    double u = 1.1;
    EXPECT_DOUBLE_EQ(non_linear(y, y_prev, u, 0, 0, 0, 0), 0.0);
}

TEST(NonLinearModelSuite, SinComponentOnly) {
    double y = 0.0;
    double y_prev = 0.0;
    double u = M_PI / 3;  // угол
    double result = non_linear(y, y_prev, u, 0, 0, 0, 2.2);
    double expected = 2.2 * std::sin(u);  // учитываем синус
    EXPECT_NEAR(result, expected, 1e-9);
}
