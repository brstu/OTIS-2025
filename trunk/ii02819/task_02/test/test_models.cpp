#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "../src/models.h"

// Тесты для computeLinear
TEST(ComputeLinearTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(computeLinear(0.0, 0.0, 2.0, 3.0), 0.0);
}

TEST(ComputeLinearTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(computeLinear(2.0, 3.0, 2.0, 3.0), 2.0*2.0 + 3.0*3.0);
}

TEST(ComputeLinearTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(computeLinear(-1.0, -2.0, 1.0, 2.0), -1.0 + -4.0);
}

// Тесты для computeNonlinear
TEST(ComputeNonlinearTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(computeNonlinear(0.0, 0.0, 1.0, 1.0, 1.0, 1.0), 0.0);
}

TEST(ComputeNonlinearTest, PositiveValues) {
    double result = computeNonlinear(2.0, 1.0, 2.0, 1.0, 3.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 4.0 - 4.0 + 3.0);
}

TEST(ComputeNonlinearTest, WithSinus) {
    double result = computeNonlinear(1.0, M_PI/2, 1.0, 0.0, 0.0, 2.0);
    EXPECT_NEAR(result, 1.0 + 2.0*sin(M_PI/2), 1e-9);
}

