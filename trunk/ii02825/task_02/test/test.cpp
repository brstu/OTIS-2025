#include <gtest/gtest.h>
#include <cmath>
#include "functions.h" 

// ------------------------
// Тесты для линейной модели
// ------------------------
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(linear(0.1, 0.3, 0.5, 0.0), 0.05 + 0.0*0.3, 1e-6); // 0.05
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(linear(0.2, 0.4, 2.0, 1.0), 2.0*0.2 + 1.0*0.4, 1e-6); // 0.4 + 0.4 = 0.8
}

// ------------------------
// Тесты для нелинейной модели
// ------------------------
TEST(NonlinearModelTest, BaseCase) {
    double result = non_linear(0.15, 0.0, 0.7, 0.9, 0.11, 0.13); // y, u, a, b, c, d
    double expected = 0.7*0.15 - 0.9*0.15*0.15 + 0.11*0.0 + 0.13*std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithValues) {
    double result = non_linear(0.5, 0.3, 0.5, 0.2, 0.3, 0.1);
    double expected = 0.5*0.5 - 0.2*0.5*0.5 + 0.3*0.3 + 0.1*std::sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}
