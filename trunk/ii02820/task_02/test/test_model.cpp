#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

TEST(ModelTest, LinearFunction) {
    double y = 23.0;
    double u = 10.0;
    double a = 0.95;
    double b = 0.002;
    
    double result = linear(y, u, a, b);
    double expected = a * y + b * u;
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(ModelTest, LinearFunctionMultipleSteps) {
    double y = 23.0;
    double a = 0.95;
    double b = 0.002;
    
    double u1 = 10.0;
    y = linear(y, u1, a, b);
    EXPECT_NEAR(y, 21.87, 0.01);
    
    double u2 = 15.0;
    y = linear(y, u2, a, b);
    EXPECT_NEAR(y, 20.8065, 0.01);
}

TEST(ModelTest, NonlinearFunction) {
    double y_current = 23.0;
    double y_prev = 23.0;
    double u = 10.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double result = non_linear(y_current, y_prev, u, a, b, c, d);
    double expected = a * y_current - b * y_prev * y_prev + c * u + d * sin(u);
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST(ModelTest, NonlinearFunctionSequence) {
    double y_prev = 23.0;
    double y_current = 23.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double u1 = 10.0;
    double result1 = non_linear(y_current, y_prev, u1, a, b, c, d);
    EXPECT_NEAR(result1, 21.2376, 0.01);
    
    y_prev = y_current;
    y_current = result1;
    
    double u2 = 15.0;
    double result2 = non_linear(y_current, y_prev, u2, a, b, c, d);
    EXPECT_NEAR(result2, 19.9327, 0.01);
}

TEST(ModelTest, CompareLinearAndNonlinear) {
    double y_linear = 23.0;
    double y_nonlinear_prev = 23.0;
    double y_nonlinear_current = 23.0;
    
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    double u = 10.0;
    
    y_linear = linear(y_linear, u, a, b);
    double y_nonlinear = non_linear(y_nonlinear_current, y_nonlinear_prev, u, a, b, c, d);
    
    EXPECT_NE(y_linear, y_nonlinear);
    EXPECT_NEAR(y_linear, 21.87, 0.01);
    EXPECT_NEAR(y_nonlinear, 21.2376, 0.01);
}

TEST(ModelTest, LinearWithZeroInput) {
    double y = 23.0;
    double u = 0.0;
    double a = 0.95;
    double b = 0.002;
    
    double result = linear(y, u, a, b);
    EXPECT_DOUBLE_EQ(result, a * y);
}

TEST(ModelTest, NonlinearWithZeroInput) {
    double y_current = 23.0;
    double y_prev = 23.0;
    double u = 0.0;
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    
    double result = non_linear(y_current, y_prev, u, a, b, c, d);
    double expected = a * y_current - b * y_prev * y_prev;
    EXPECT_NEAR(result, expected, 1e-10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}