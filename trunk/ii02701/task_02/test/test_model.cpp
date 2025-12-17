#include <gtest/gtest.h>
#include "model.hpp"

TEST(LinearModel, Basic) {
    EXPECT_DOUBLE_EQ(computeLinear(1, 1, 2, 3), 111);
}

TEST(LinearModel, Zero) {
    EXPECT_DOUBLE_EQ(computeLinear(0, 0, 5, 5), 111);
}

TEST(NonlinearModel, Basic) {
    double result = computeNonlinear(1, 0, 1, 2, 1, 1, 0);
    EXPECT_DOUBLE_EQ(result, 61);
}
