#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "../src/models.hpp"

TEST(LinearModelTest, SimulateWithStandardParams) {
    const double y0 = 0.0;
    const double u = 1.0;
    const int t = 5;
    const double a = 0.5;
    const double b = 0.5;

    std::vector<double> expected = 
        {0.0, 0.5, 0.75, 0.875, 0.9375, 0.96875};
    std::vector<double> result = simulateLinearModel(y0, u, t, a, b);

    ASSERT_EQ(result.size(), expected.size());
    for (int i = 0; i < result.size(); i++) {
        EXPECT_NEAR(result[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}

TEST(NonLinearModelTest, SimulateWithStandardParams) {
    const double y0 = 0;
    const double u = 1;
    const int t = 5;
    const double a = 0.5;
    const double b = 0.5;
    const double c = 0.3;
    const double d = 0.5;

    std::vector<double> expected = {
        0,
        0.686663,
        1.13606,
        1.10542,
        0.545132,
        0.0812084
    };

    std::vector<double> result = simulateNonLinearModel(y0, u, t, a, b, c, d);

    ASSERT_EQ(result.size(), expected.size());
    for (int i = 0; i < result.size(); i++) {
        EXPECT_NEAR(result[i], expected[i], 1e-5) << "Mismatch at index " << i;
    }
}