#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "functions.h"

// ------------------------------
// Тесты для simulateLinear()
// ------------------------------

TEST(SimulateLinearfuncTest, HandlesEmptyInput) {
    std::vector<double> u;
    auto result = simulateLinearfunc(5, 10.0, u);
    EXPECT_TRUE(result.empty());
}

TEST(SimulateLinearfuncTest, HandlesSingleStep) {
    std::vector<double> u = {1.0};
    auto result = simulateLinearfunc(1, 10.0, u);
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
}

TEST(SimulateLinearfuncTest, ProducesCorrectSequence) {
    std::vector<double> u = {5.0, 5.0, 5.0, 5.0};
    auto result = simulateLinearfunc(5, 10.0, u);

    ASSERT_EQ(result.size(), 5);
    EXPECT_NEAR(result[1], 0.9 * 10.0 + 0.1 * 5.0, 1e-6);
    EXPECT_NEAR(result[2], 0.9 * result[1] + 0.1 * 5.0, 1e-6);
}

// ------------------------------
// Тесты для simulateNonlinear()
// ------------------------------

TEST(SimulateNonlinearfuncTest, HandlesZeroSteps) {
    std::vector<double> u = {5.0, 5.0};
    auto result = simulateNonlinearfunc(0, 10.0, u);
    EXPECT_TRUE(result.empty());
}

TEST(SimulateNonlinearfuncTest, HandlesOneStep) {
    std::vector<double> u = {5.0, 5.0};
    auto result = simulateNonlinearfunc(1, 10.0, u);
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
}

TEST(SimulateNonlinearfuncTest, ProducesCorrectValues) {
    std::vector<double> u = {5.0, 5.0, 5.0};
    auto result = simulateNonlinearfunc(3, 10.0, u);

    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[1], 0.9 * 10.0 + 0.1 * 5.0, 1e-6);
    double expected2 = 0.9 * result[1] - 0.1 * std::pow(10.0, 2) + 0.05 * 5.0 + 0.02 * std::sin(5.0);
    EXPECT_NEAR(result[2], expected2, 1e-6);
}
