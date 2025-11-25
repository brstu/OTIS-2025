#include <gtest/gtest.h>
#include <cmath>
#include "functions.h" 

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(linear(0.25, 0.45, 0.6, 0.1), 0.6 * 0.25 + 0.1 * 0.45, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(linear(0.35, 0.55, 1.5, 0.8), 1.5 * 0.35 + 0.8 * 0.55, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    double result = non_linear(0.2, 0.1, 0.8, 0.6, 0.15, 0.2);
    double expected = 0.8 * 0.2 - 0.6 * 0.2 * 0.2 + 0.15 * 0.1 + 0.2 * std::sin(0.1);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithValues) {
    double result = non_linear(0.6, 0.4, 0.4, 0.3, 0.25, 0.15);
    double expected = 0.4 * 0.6 - 0.3 * 0.6 * 0.6 + 0.25 * 0.4 + 0.15 * std::sin(0.4);
    EXPECT_NEAR(result, expected, 1e-6);
}