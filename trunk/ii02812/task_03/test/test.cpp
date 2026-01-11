/**
 * @file test.cpp
 * @brief Набор модульных тестов для класса PID и линейной модели.
 */

#include "../src/PID.h"
#include "../src/lin_model.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(LinearModelTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(linear_model(2.0, 3.0, 1.0, 4.0), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(1.5, 2.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear_model(-1.0, 2.0, 3.0, -4.0), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(LinearModelTest, MixedValues) {
    double result = linear_model(6, 8, 0.5, 0.2);
    EXPECT_DOUBLE_EQ(result, 0.5 * 6 + 0.2 * 8);
}

TEST(PIDTest, CoefficientsCalculation) {
    double K = 0.5;
    double T = 2.0;
    double Td = 0.3;
    double T0 = 1.0;

    PID pid(K, T, Td, T0);

    double expected_q0 = K * (1.0 + Td / T0);
    double expected_q1 = -K * (1 + 2 * Td / T0 - T0 / T);
    double expected_q2 = K * Td / T0;

    double u1 = pid.u_calc(0.7);
    double expected_u = 0.0 + expected_q0 * 0.7 + expected_q1 * 0.0 + expected_q2 * 0.0;

    EXPECT_NEAR(u1, expected_u, 1e-10);
}

TEST(PIDTest, SequentialCalculations) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    double u1 = pid.u_calc(1.0);
    double u2 = pid.u_calc(0.5);
    double u3 = pid.u_calc(0.2);

    EXPECT_NE(u1, u2);
    EXPECT_NE(u2, u3);
}

TEST(PIDTest, ZeroError) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    double u1 = pid.u_calc(0.0);
    EXPECT_DOUBLE_EQ(u1, 0.0);
}

TEST(PIDSystemTest, SystemStabilization) {
    PID pid(1.5, 3.0, 0.2, 1.0);

    double y_prev = 15.0;
    double w = 35.0;
    double a = 0.8;
    double b = 0.1;
    double y = y_prev;

    for (int i = 0; i < 50; i++) {
        double e = w - y;
        double u = pid.u_calc(e);
        y = linear_model(y, u, a, b);
    }

    EXPECT_NEAR(y, w, 2.0);
}

TEST(PIDSystemTest, ConvergenceTest) {
    PID pid(0.8, 2.0, 0.1, 0.5);

    double y = 10.0;
    double w = 25.0;
    double a = 0.9;
    double b = 0.15;

    std::vector<double> errors;

    for (int i = 0; i < 30; i++) {
        double e = w - y;
        errors.push_back(std::abs(e));
        double u = pid.u_calc(e);
        y = linear_model(y, u, a, b);
    }

    EXPECT_LT(errors.back(), errors.front());
}


TEST(PIDTest, ExtremeCoefficients) {

    PID pid_small(0.001, 0.001, 0.001, 0.001);
    double u_small = pid_small.u_calc(1.0);
    EXPECT_NEAR(u_small, 0.002, 1e-10); 

    PID pid_large(10.0, 10.0, 10.0, 10.0);
    double u_large = pid_large.u_calc(1.0);
    EXPECT_NEAR(u_large, 20.0, 1e-10);
}

TEST(PIDTest, ConstantError) {
    PID pid(1.0, 2.0, 0.5, 1.0);

    double constant_error = 2.0;

    for (int i = 0; i < 5; i++) {
        double u = pid.u_calc(constant_error);
        if (i > 0) {
            EXPECT_NE(u, 0.0);
        }
    }
}

TEST(PIDTest, NegativeError) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    double u_positive = pid.u_calc(1.0);
    PID pid_negative(1.0, 1.0, 0.1, 0.1);
    double u_negative = pid_negative.u_calc(-1.0);

    EXPECT_LT(u_negative, 0.0);
    EXPECT_GT(u_positive, 0.0);
}

TEST(PIDTest, InvalidState) {
    PID pid(1.0, 1.0, 1.0, 1.0);

    pid.invalidate();

    double u = pid.u_calc(1.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}
