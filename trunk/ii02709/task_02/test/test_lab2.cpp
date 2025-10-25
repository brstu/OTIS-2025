#include <gtest/gtest.h>
#include <cmath>
#include "../src/lab2.h"

TEST(Lab2Test, LinearUpdateWorks) {
    long double y = 1.5L, u = 2.0L;
    long double expected = lab2::a * y + lab2::b * u;
    EXPECT_NEAR(lab2::next_linear(y, u), expected, 1e-9);
}

TEST(Lab2Test, NonlinearUpdateWorks) {
    long double y = 1.5L, u = 2.0L;
    long double expected = lab2::a * y - lab2::b * y * y + lab2::c1 * u + lab2::c2 * std::sinh(u);
    EXPECT_NEAR(lab2::next_nonlinear(y, u), expected, 1e-9);
}

TEST(Lab2Test, LinearSimulationNegativeStepsReturnsEmpty) {
    auto result = lab2::simulate_linear(-1, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, NonlinearSimulationNegativeStepsReturnsEmpty) {
    auto result = lab2::simulate_nonlinear(-1, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, LinearSimulationProducesExpectedSequence) {
    auto result = lab2::simulate_linear(3, 1.0L, 2.0L);
    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.9L * 1.0L + 0.5L * 2.0L, 1e-9);  // Шаг 1
    EXPECT_NEAR(result[1], 0.9L * result[0] + 0.5L * 2.0L, 1e-9);  // Шаг 2
    EXPECT_NEAR(result[2], 0.9L * result[1] + 0.5L * 2.0L, 1e-9);  // Шаг 3
}

TEST(Lab2Test, NonlinearSimulationProducesExpectedSequence) {
    auto result = lab2::simulate_nonlinear(3, 1.0L, 2.0L);
    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.9L * 1.0L - 0.5L * 1.0L * 1.0L + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 1
    EXPECT_NEAR(result[1], 0.9L * result[0] - 0.5L * result[0] * result[0] + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 2
    EXPECT_NEAR(result[2], 0.9L * result[1] - 0.5L * result[1] * result[1] + 0.1L * 2.0L + 0.05L * std::sinh(2.0L), 1e-9);  // Шаг 3
}

TEST(Lab2Test, LinearSimulationZeroStepsReturnsEmpty) {
    auto result = lab2::simulate_linear(0, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}

TEST(Lab2Test, NonlinearSimulationZeroStepsReturnsEmpty) {
    auto result = lab2::simulate_nonlinear(0, 1.0L, 2.0L);
    EXPECT_TRUE(result.empty());
}