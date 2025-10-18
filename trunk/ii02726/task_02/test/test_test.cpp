#include "test.h"
#include <gtest/gtest.h>
#include <vector>

TEST(LinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = linear_func(1, 0.1, 0.4, u, 0.1, 0.2);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0 + 1.0);
}

TEST(NonLinearModelTest, SimpleCase) {
    std::vector<double> u = {0, 1, 2, 3};
    auto y = nonlinear_func(3, {0.5, 2.0, 0.1, 0.8}, u, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(y[0], 0.0);
    EXPECT_DOUBLE_EQ(y[1], 1.0);
    EXPECT_DOUBLE_EQ(y[2], 1.0*1.0 - 1.0*0.0 + 1.0*1.0 + 0.0);
}