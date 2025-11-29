#include "../src/model.h"
#include <gtest/gtest.h>
#include <cmath>
 
TEST(LinearModelTest, NextLinearBasicCalculation) {
    double result = nextLinear(0.5, 0.5, 1.0, 2.0);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(LinearModelTest, NextLinearZeroInput) {
    double result = nextLinear(0.3, 0.7, 0.0, 5.0);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(LinearModelTest, NextLinearBothZero) {
    double result = nextLinear(0.2, 0.8, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}
 
TEST(NonlinearModelTest, NextNonlinearBasicCalculation) {
    NonlinearParams p;
    p.a = 0.1; p.b = 0.2; p.c = 0.3; p.d = 0.4;
    p.u = 1.0; p.uPrev = 0.5; p.y = 2.0; p.yPrev = 1.0;

    double result = nextNonlinear(p);
    double expected = 0.1*2.0 - 0.2*(1.0*1.0) + 0.3*1.0 + 0.4*sin(0.5);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, NextNonlinearAllZero) {
    NonlinearParams p;
    p.a = 0.0; p.b = 0.0; p.c = 0.0; p.d = 0.0;
    p.u = 0.0; p.uPrev = 0.0; p.y = 0.0; p.yPrev = 0.0;

    double result = nextNonlinear(p);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, NextNonlinearOnlyLinearPart) {
    NonlinearParams p;
    p.a = 0.5; p.b = 0.0; p.c = 0.5; p.d = 0.0;
    p.u = 2.0; p.uPrev = 0.0; p.y = 3.0; p.yPrev = 0.0;

    double result = nextNonlinear(p);
    EXPECT_DOUBLE_EQ(result, 2.5);
}