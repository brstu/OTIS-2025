#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/models.h"
#include "../src/pid.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y = 2.0;
    double u = 3.0;
    double a = 1.5;
    double b = -0.5;
    double expected = a * y + b * u;

    EXPECT_DOUBLE_EQ(linear(y, u, a, b), expected);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y   = 1.0;
    double y_p = 0.0;
    double u   = 0.5;
    double u_p = 0.2;
    NonLinearCoeffs coeffs{2.0, 1.0, 0.5, 1.0};
    double expected = coeffs.a * y - coeffs.b * y_p * y_p + coeffs.c * u + coeffs.d * std::sin(u_p);

    EXPECT_DOUBLE_EQ(non_linear(y, y_p, u, u_p, coeffs), expected);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y   = 2.0;
    double y_p = 1.0;
    double u   = 1.0;
    double u_p = 0.5;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 0.0};

    EXPECT_DOUBLE_EQ(non_linear(y, y_p, u, u_p, coeffs), 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y   = 0.0;
    double y_p = 0.0;
    double u   = 0.0;
    double u_p = M_PI / 2;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 2.0};

    EXPECT_DOUBLE_EQ(non_linear(y, y_p, u, u_p, coeffs), 2.0);
}

TEST(PidTest, Initialization) {
    pid_coeffs coeffs(2.0, 1.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double e = 1.0;
    double expected = PID.process(e);

    EXPECT_DOUBLE_EQ(expected, 12.0);
}

TEST(PidTest, StateUpdate) {
    pid_coeffs coeffs(1.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u1 = PID.process(1.0);
    double u2 = PID.process(2.0);

    EXPECT_NE(u1, u2);
}

TEST(PidTest, ZeroCoefficients) {
    pid_coeffs coeffs(0.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double result = PID.process(5.0);

    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(PidTest, MultipleSteps) {
    pid_coeffs coeffs(1.0, 2.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u1 = PID.process(1.0);
    double u2 = PID.process(1.0);
    double u3 = PID.process(1.0);

    EXPECT_NE(u1, u2);
    EXPECT_NE(u2, u3);
}