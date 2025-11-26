#include <gtest/gtest.h>
#include "../src/model.h"
#include "../src/pid.h"

TEST(ModelTest, BasicCase) {
    double y = 2.0;
    double u = 3.0;
    double a = 1.5;
    double b = -0.5;
    double expected = a * y + b * u;
    EXPECT_DOUBLE_EQ(linear(y, u, a, b), expected);
}

TEST(ModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(ModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
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