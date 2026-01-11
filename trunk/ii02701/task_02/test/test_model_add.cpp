#include <gtest/gtest.h>
#include "model.hpp"

TEST(LinearModelA, Basic) {
    EXPECT_DOUBLE_EQ(computeLinear(1, 1, 2, 3), 111);
}

TEST(LinearModelA, NonBasic) {
    EXPECT_DOUBLE_EQ(computeLinear(1, 1, 2, 3), 111);
}

TEST(LinearModelB, Basic) {
    EXPECT_DOUBLE_EQ(computeLinear(1, 1, 2, 3), 111);
}
