#include <gtest/gtest.h>
#include "model.h"
#include "pid.h" 

constexpr double PI = 3.14159265358979323846;

TEST(ModelTest, LinearZeroParams) {
    double y_next = linear(5.0, 3.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(y_next, 0.0);
}

TEST(ModelTest, LinearBasic) {
    double y_next = linear(2.0, 4.0, 1.0, 2.0);
    EXPECT_DOUBLE_EQ(y_next, 2.0*1.0 + 4.0*2.0); // 10.0
}

TEST(ModelTest, NonlinearWithoutControlTerms) {
    double y_next = nonlinear(0.0, 2.0, 0.0, 1.0, 0.0, 2.0);
    EXPECT_DOUBLE_EQ(y_next, 4.0 - 4.0); // 0.0
}



TEST(ModelTest, NonlinearWithSin) {
    double y_next = nonlinear(0.0, 0.0, 1.0, 0.0, 0.0, PI / 2);
    EXPECT_NEAR(y_next, 1.0, 1e-9); // sin(pi/2) = 1
}


TEST(PIDTest, ZeroError) {
    PID pid(1.0, 1.0, 0.0, 1.0);
    double u = pid.compute(0.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}

TEST(PIDTest, ConstantError) {
    PID pid(2.0, 1.0, 0.0, 1.0);
    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);
    EXPECT_NE(u1, u2); 
}