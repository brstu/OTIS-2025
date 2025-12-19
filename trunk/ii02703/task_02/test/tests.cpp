#include <gtest/gtest.h>
#include "../src/models.hpp" 
#include <cmath>


TEST(LinearModelTest, BasicCalculation) {
    double result = linear_model(10.0, 10.0, 0.5, 0.5);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

TEST(LinearModelTest, ZeroInputs) {
    double result = linear_model(0.0, 0.0, 0.5, 0.5);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(LinearModelTest, NegativeCoefficients) {
    double result = linear_model(10.0, 10.0, -1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}


TEST(NonlinearModelTest, BasicCalculation) {
    double y_curr = 10.0;
    double y_prev = 5.0;  
    double u = 2.0;
    double u_prev = 0.0;
    
    double a = 1.0;
    double b = 0.1;
    double c = 0.5;
    double d = 1.0;

    double result = nonlinear_model(y_curr, y_prev, u, u_prev, a, b, c, d);
    EXPECT_DOUBLE_EQ(result, 8.5);
}

TEST(NonlinearModelTest, SinusImpact) {
    double u_prev = 1.57079632679; 
    double d = 10.0;
    double result = nonlinear_model(0, 0, 0, u_prev, 0, 0, 0, d);
    
    EXPECT_NEAR(result, 10.0, 0.0001);
}