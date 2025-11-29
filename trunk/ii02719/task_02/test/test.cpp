#include <gtest/gtest.h>
#include <cmath>
#include "../src/functions.h"

TEST(LinearTest, CalculatesCorrectly) {
    const int steps = 3;
    std::vector<double> y;
	y.resize(steps);
	std::vector<double> u;
	u.resize(steps);
    y[0] = 10.0;
    u[0] = 5.0;

    linear(1.0, 0.5, y, u, steps);

    EXPECT_DOUBLE_EQ(y[1], 1.0 * 10.0 + 0.5 * 0.5); // 12.5
    EXPECT_DOUBLE_EQ(u[1], 5.0 * 0.8);              // 4.0
    EXPECT_DOUBLE_EQ(y[2], 1.0 * 12.5 + 0.5 * 0.8); // 14.5
    EXPECT_DOUBLE_EQ(u[2], 4.0 * 0.8);              // 3.2
}

TEST(NonLinearTest, CalculatesCorrectly) {
    const int steps = 4;
    std::vector<double> y;
	y.resize(steps);
	std::vector<double> u;
	u.resize(steps);
    y[0] = 10.0;
    y[1] = 12.0;
    u[0] = 5.0;
    u[1] = u[0] * 0.8;

    nonLinear(1.0, 0.5, 0.2, 0.1, y, u, steps);

    double expected_y2 = 1.0 * 12.0 - 0.5 * 10.0 / 2.0 + 0.2 * u[1] + 0.1 * sin(u[0]);
    EXPECT_NEAR(y[2], expected_y2, 1e-6);

    double expected_u2 = u[1] * 0.8;
    EXPECT_NEAR(u[2], expected_u2, 1e-6);
}