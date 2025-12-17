#include <gtest/gtest.h>
#include "model.h"

TEST(LinearModelTest, BasicCalculation) {
    // y = 0.95*23 + 0.002*10 = 21.85 + 0.02 = 21.87
    EXPECT_NEAR(linear_model(23.0, 10.0, 0.95, 0.002), 21.87, 0.01);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(10.0, 0.0, 0.5, 0.1), 5.0);
}

TEST(LinearModelTest, ZeroParameters) {
    EXPECT_DOUBLE_EQ(linear_model(10.0, 5.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModelTest, BasicCalculation) {
    // y = 0.95*23 + 0.05*22 + 0.05*10 + 0.0001*100
    //   = 21.85 + 1.1 + 0.5 + 0.01 = 23.46
    double result = nonlinear_model(23.0, 22.0, 10.0, 0.95, 0.05, 0.05, 0.0001);
    EXPECT_NEAR(result, 23.46, 0.01);
}

TEST(NonlinearModelTest, AllZeros) {
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModelTest, OnlyInput) {
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0), 10.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}