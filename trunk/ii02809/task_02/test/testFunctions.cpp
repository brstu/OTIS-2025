#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>


TEST(LinearModelTest, PositiveValues) {
    ModelParams params{2.0, 3.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(1.0, 4.0, params), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearModelTest, ZeroInput) {
    ModelParams params{1.5, 2.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0, params), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    ModelParams params{-1.0, 2.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(linearModel(3.0, -4.0, params), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(NonlinearModelTest, BasicCalculation) {
    ModelParams params{1.0, 1.0, 1.0, 1.0};
    double res = nonlinearModel(1.0, 1.0, 1.0, 0.0, params);
    EXPECT_NEAR(res, 1.0 * 1.0 - 1.0 * 1.0 * 1.0 + 1.0 * 1.0 + 1.0 * sin(0.0), 1e-9);
}

TEST(NonlinearModelTest, IncludesSineTerm) {
    ModelParams params{1.0, 0.0, 0.0, 1.0};
    double res1 = nonlinearModel(1.0, 0.0, 1.0, M_PI / 2, params);
    EXPECT_NEAR(res1, 1.0 * 1.0 - 0.0 + 0.0 * 1.0 + 1.0 * sin(M_PI / 2), 1e-9);
}

TEST(NonlinearModelTest, NegativeInput) {
    ModelParams params{-1.0, 1.0, 2.0, -1.0};
    double res = nonlinearModel(2.0, 1.0, -2.0, M_PI, params);
    double expected = -1.0 * 2.0 - 1.0 * 1.0 * 1.0 + 2.0 * -2.0 - 1.0 * sin(M_PI);
    EXPECT_NEAR(res, expected, 1e-9);
}
