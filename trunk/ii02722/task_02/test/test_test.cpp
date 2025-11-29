#include <gtest/gtest.h>
#include "../src/test.h"
#include <cmath>

TEST(LinearModelTest, BasicCalculation)
{
    float result = linear_step(1.0f, 1.2f, 0.5f, 0.2f);
    EXPECT_NEAR(result, 0.5f * 1.0f + 0.2f * 1.2f, 1e-5);
}

TEST(NonLinearModelTest, BasicCalculation)
{
    float result = nonlinear_step(1.0f, 1.0f, 1.2f, 0.5f, 0.2f, 0.15f, 0.3f);
    float expected = 0.5f * 1.0f - 0.2f * 1.0f * 1.0f + 0.15f * 1.2f + 0.3f * sin(1.2f);
    EXPECT_NEAR(result, expected, 1e-5);
}
