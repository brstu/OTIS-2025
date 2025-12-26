#include <gtest/gtest.h>
#include <cmath>
#include "../src/functions.h"

TEST(LinearTest, CalculatesCorrectly) {
    const int steps = 3;
    std::vector<double> y;
	y.resize(steps);
    double a = 0.8;
    double b = 0.5;
    y[0] = 10.0;

    linear(a, b, y, steps);

    EXPECT_DOUBLE_EQ(y[1], 0.8 * 10.0 + 0.5 * (1.6 * 90.0 + 0.32 * 90.0 + 0.4 * 90.0)); // 112,4
    EXPECT_DOUBLE_EQ(y[2], 0.8 * 112.4 + 0.5 * (1.6 * -12.4 + 0.32 * 77.6 + 0.4 * -102.4)); // 71,936
}
