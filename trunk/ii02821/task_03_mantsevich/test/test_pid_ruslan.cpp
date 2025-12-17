/**
 * @file test_pid_ruslan.cpp
 * @brief Unit tests for PID controller class
 * @author Ruslan
 * @date 2024
 */

#include "pid_ruslan.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

constexpr double EPS = 1e-6;   ///< Tolerance for floating point comparisons

/**
 * @brief Test basic PID response with positive error
 */
TEST(PID_Ruslan_Test, BasicResponse) {
    PID_ruslan pid(1.0, 0.5, 0.1, 0.1);

    double setpoint = 1.0;
    double measured = 0.0;

    // take a few steps to let integral accumulate
    double prev_u = pid.compute(setpoint, measured);
    EXPECT_GT(prev_u, 0.0);

    for (int i = 0; i < 5; ++i) {
        double u = pid.compute(setpoint, measured);
        // should remain positive and not immediately drop below previous (basic sanity)
        EXPECT_GT(u, 0.0);
        // relax tolerance a bit to avoid flaky failures on different platforms/optimizations
        EXPECT_GE(u, prev_u - EPS);
        prev_u = u;
    }
}

/**
 * @brief Test initialization with invalid time step
 */
TEST(PID_Ruslan_Test, InvalidDtInitializesInvDt) {
    PID_ruslan pid(1.0, 0.0, 1.0, -0.5); // invalid dt, will use DEFAULT_DT

    // Compute once to ensure no crash or undefined behavior
    double u = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u)); // Output must be finite (no NaN or inf)
}

/**
 * @brief Test derivative term scaling with different time steps
 */
TEST(PID_Ruslan_Test, DerivativeScaling) {
    // isolate derivative: Kp = 0, Ki = 0, Kd = 1.0
    PID_ruslan pid_fast(0.0, 0.0, 1.0, 0.1);
    PID_ruslan pid_slow(0.0, 0.0, 1.0, 1.0);

    double setpoint = 1.0;

    // initial measurement to set prev_error
    double u_fast_before = pid_fast.compute(setpoint, 0.0);
    double u_slow_before = pid_slow.compute(setpoint, 0.0);

    // Now introduce small change in measurement
    double u_fast_after = pid_fast.compute(setpoint, 0.9);
    double u_slow_after = pid_slow.compute(setpoint, 0.9);

    // With smaller dt (larger inv_dt), derivative term produces larger change in output
    double delta_u_fast = u_fast_after - u_fast_before;
    double delta_u_slow = u_slow_after - u_slow_before;

    // be conservative: require strictly larger magnitude for fast
    EXPECT_GT(std::fabs(delta_u_fast), std::fabs(delta_u_slow));
}

/**
 * @brief Test that invalid output limits are ignored
 */
TEST(PID_Ruslan_Test, InvalidOutputLimitsIgnored) {
    PID_ruslan pid(1.0, 0.0, 0.0, 0.1);
    pid.setOutputLimits(-1.0, 1.0);

    // Invalid call: should be ignored
    pid.setOutputLimits(2.0, -2.0);

    // After invalid call, old limits must remain valid
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 1.0 + EPS);
    EXPECT_GE(u, -1.0 - EPS);
}

/**
 * @brief Test integral anti-windup limits
 */
TEST(PID_Ruslan_Test, IntegralLimitsWork) {
    // Ki = 1 so output == integral (before output clamping), Kp = Kd = 0
    PID_ruslan pid(0.0, 1.0, 0.0, 0.1);
    pid.setIntegralLimits(-0.5, 0.5);

    // Force integral windup
    for (int i = 0; i < 100; ++i)
        pid.compute(10.0, 0.0);

    // Integral should be clamped; output == integral (Ki = 1)
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 0.5 + EPS);
    EXPECT_GE(u, -0.5 - EPS);
}

/**
 * @brief Test reset functionality and dynamic time step change
 */
TEST(PID_Ruslan_Test, ResetAndSetDt) {
    PID_ruslan pid(1.0, 1.0, 1.0, 0.1);
    pid.compute(1.0, 0.0);
    pid.reset();
    double u_after_reset = pid.compute(1.0, 0.0);

    // After reset, integral and prev_error cleared — output should be finite and reasonable
    EXPECT_TRUE(std::isfinite(u_after_reset));

    // Changing dt should not crash and should affect derivative scaling
    pid.setDt(0.05);
    double u_after_dt_change = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u_after_dt_change));
}