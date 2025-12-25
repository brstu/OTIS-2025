#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/models.h"
#include "../src/pid.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y01 = 2.0;
    double u01 = 3.0;
    double a01 = 1.5;
    double b01 = -0.5;
    double expected01 = a01 * y01 + b01 * u01;

    EXPECT_DOUBLE_EQ(linear(y01, u01, a01, b01), expected01);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y01   = 1.0;
    double y01_p = 0.0;
    double u01   = 0.5;
    double u01_p = 0.2;
    NonLinearCoeffs coeffs{2.0, 1.0, 0.5, 1.0};
    double expected01 = coeffs.a01 * y01 - coeffs.b01 * y01_p * y01_p + coeffs.c01 * u01 + coeffs.d01 * std::sin(u01_p);

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), expected01);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y01   = 2.0;
    double y01_p = 1.0;
    double u01   = 1.0;
    double u01_p = 0.5;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 0.0};

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y01   = 0.0;
    double y01_p = 0.0;
    double u01   = 0.0;
    double u01_p = M_PI / 2;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 2.0};

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), 2.0);
}

TEST(PidTest, Initialization) {
    pid_coeffs coeffs(2.0, 1.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double e01 = 1.0;
    double expected01 = PID.process(e01);

    EXPECT_DOUBLE_EQ(expected01, 12.0);
}

TEST(PidTest, StateUpdate) {
    pid_coeffs coeffs(1.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u101 = PID.process(1.0);
    double u201 = PID.process(2.0);

    EXPECT_NE(u101, u201);
}

TEST(PidTest, ZeroCoefficients) {
    pid_coeffs coeffs(0.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double result01 = PID.process(5.0);

    EXPECT_DOUBLE_EQ(result01, 0.0);
}

TEST(PidTest, MultipleSteps) {
    pid_coeffs coeffs(1.0, 2.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u101 = PID.process(1.0);
    double u201 = PID.process(1.0);
    double u301 = PID.process(1.0);

    EXPECT_NE(u101, u201);
    EXPECT_NE(u201, u301);
}