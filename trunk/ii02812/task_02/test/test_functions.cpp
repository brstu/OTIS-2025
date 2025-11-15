#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/functions.h"

TEST(LinearModelTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(linear_model(2.0, 3.0, 1.0, 4.0), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(1.5, 2.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear_model(-1.0, 2.0, 3.0, -4.0), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(NonLinearModelTest, BasicCalculation) {
    double res = nonlinear_model(1.0, 1.0, 1.0, 0.0, 2.0, 3.0, 1.0, 0.0);
    EXPECT_NEAR(res, 1.0 * 3.0 - 1.0 * pow(2.0, 2) + 1.0 * 1.0 + 0.0 * sin(0.0), 1e-9);
}

TEST(NonLinearModelTest, IncludesSineTerm) {
    double res1 = nonlinear_model(1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, M_PI / 2);
    EXPECT_NEAR(res1, 1.0 * 1.0 - 0.0 * 0.0 + 0.0 * 0.0 + 1.0 * sin(M_PI / 2), 1e-9);
}

TEST(NonLinearModelTest, NegativeInput) {
    double res = nonlinear_model(-1.0, 1.0, 2.0, -1.0, 1.0, -2.0, 3.0, M_PI);
    double expected = -1.0 * -2.0 - 1.0 * 1.0 + 2.0 * 3.0 - 1.0 * sin(M_PI);
    EXPECT_NEAR(res, expected, 1e-9);
}
