#include <gtest/gtest.h>
#include "model.h"

TEST(ModelTest, LinearModel) {
    double result = linear_model(23.0, 10.0, 0.95, 0.002);
    EXPECT_NEAR(result, 21.87, 0.01);
}

TEST(ModelTest, NonlinearModel) {
    double result = nonlinear_model(23.0, 22.0, 10.0, 0.95, 0.05, 0.05, 0.0001);
    EXPECT_NEAR(result, 23.46, 0.01);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}