#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../../task_01/src/main.h"
#include <cmath>

struct NonLinearParams {
    double a;
    double b;
    double c;
    double d;
};

TEST(LinearModel_ii02811, ComputesCorrectly) {
    double y = 2.3;
    double u = 3.7;
    double a = 1.5;
    double b = -0.8;
    double expected = a * y + b * u;
    EXPECT_NEAR(x(y, u, a, b), expected, 1e-9);
}

TEST(LinearModel_ii02811, ZeroCoefficientsReturnZero) {
    EXPECT_DOUBLE_EQ(x(5.1, 4.2, 0.0, 0.0), 0.0);
}

TEST(LinearModel_ii02811, HandlesNegativeInputs) {
    EXPECT_DOUBLE_EQ(x(-1.2, -2.3, 1.0, 2.0), -1.2 + (-2.3 * 2.0));
}

TEST(NonLinearModel_ii02811, ComputesExpectedValue) {
    double y = 1.0;
    double u = 0.5;
    double yx = 0.0;
    NonLinearParams p{2.0, 1.0, 0.6, 1.1};

    double expected = p.a * y - p.b * y * yx + p.c * u + p.d * sin(u);
    
    double result = x1(y, u, p.a, p.b, p.c, p.d, yx);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonLinearModel_ii02811, ZeroCoefficientsReturnZero) {
    double y = 2.4;
    double u = 1.2;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 0.0);
}

TEST(NonLinearModel_ii02811, SinComponentOnlyWorks) {
    double y = 0.0;
    double u = M_PI / 4;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 0.0, 2.5};

    double result = x1(y, u, p.a, p.b, p.c, p.d, yx);
    double expected = 2.5 * sin(u);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonLinearModel_ii02811, OnlyLinearYComponent) {
    double y = 3.0;
    double u = 0.0;
    double yx = 0.0;
    NonLinearParams p{2.0, 0.0, 0.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 2.0 * 3.0);
}

TEST(NonLinearModel_ii02811, OnlyQuadraticComponent) {
    double y = 3.0;
    double u = 0.0;
    double yx = 2.0; 
    NonLinearParams p{0.0, 1.0, 0.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), -6.0);
}

TEST(NonLinearModel_ii02811, OnlyLinearUComponent) {
    double y = 0.0;
    double u = 4.0;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 3.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 3.0 * 4.0);
}

TEST(NonLinearModel_ii02811, CombinedComponents) {
    double y = 2.0;
    double u = 1.5;
    double yx = 3.0;
    NonLinearParams p{1.5, 0.5, 2.0, 1.0};
    
    double expected = 3.0 + sin(1.5);
    EXPECT_NEAR(x1(y, u, p.a, p.b, p.c, p.d, yx), expected, 1e-9);
}