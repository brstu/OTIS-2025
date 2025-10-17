#include "test.h"
#include <gtest/gtest.h>
#include <vector>

TEST(LinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = linear_func(3, 1.0, 1.0, u, 0.0, 1.0);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0 + 1.0);
}

TEST(NonLinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = nonlinear_func(3, 1.0, 1.0, 1.0, 0.0, u, 0.0, 1.0);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0*1.0 - 1.0*0.0 + 1.0*1.0 + 0.0);
}