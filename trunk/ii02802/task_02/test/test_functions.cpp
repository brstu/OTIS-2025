#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>

TEST(LinearTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(linear(2.0, 3.0, 1.0, 4.0), 1.0 * 2.0 + 4.0 * 3.0);
}

TEST(LinearTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0, 2.0, 5.0), 0.0);
}

TEST(LinearTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear(-2.0, 3.0, 2.0, -1.0), 2.0 * -2.0 + -1.0 * 3.0);
}

TEST(NonlinearTest, BasicCalculation) {
    double y = 1.0, u = 2.0, a = 1.0, b = 0.5, c = 2.0, d = 3.0;
    double expected = a * y - b * y * y + c * u + d * sin(u);
    EXPECT_NEAR(nonlinear(y, u, a, b, c, d), expected, 1e-9);
}

TEST(NonlinearTest, IncludesSineTerm) {
    double res = nonlinear(1.0, M_PI / 2, 0.0, 0.0, 0.0, 1.0);
    EXPECT_NEAR(res, sin(M_PI / 2), 1e-9);
}

TEST(NonlinearTest, NegativeInput) {
    double y = -1.0, u = -M_PI, a = 2.0, b = 1.0, c = -3.0, d = 0.5;
    double expected = a * y - b * y * y + c * u + d * sin(u);
    EXPECT_NEAR(nonlinear(y, u, a, b, c, d), expected, 1e-9);
}
