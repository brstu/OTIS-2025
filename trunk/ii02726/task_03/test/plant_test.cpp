#include <gtest/gtest.h>
#include "plant.h"
#include <vector>
#include <cmath>

TEST(PlantLinearTest, ConstantInput) {
    int steps = 10;
    std::vector<double> u(steps, 1.0);
    auto y = linear_func(steps, 0.5, 0.5, u, 0.0, 0.0);

    ASSERT_EQ(y.size(), static_cast<size_t>(steps));
    EXPECT_NEAR(y[2], 0.5 * y[1] + 0.5 * u[1], 1e-9);
}

TEST(PlantNonlinearTest, BasicCheck) {
    int steps = 10;
    std::vector<double> u(steps, 1.0);
    abcd coeff{1.0, 0.1, 0.5, 0.2};
    auto y = nonlinear_func(steps, coeff, u, 0.0, 0.0);

    ASSERT_EQ(y.size(), static_cast<size_t>(steps));
    EXPECT_NEAR(y[2], coeff.a * y[1] - coeff.b * y[0] * y[0] + coeff.c * u[1] + coeff.d * std::sin(u[0]), 1e-9);
}
