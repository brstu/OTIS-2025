/**
 * @file pid_ruslan.cpp
 * @brief Implementation of PID controller class
 * @author Ruslan
 * @date 2024
 */

#include "pid_ruslan.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Constructor for PID controller
 * @param Kp_ Proportional gain
 * @param Ki_ Integral gain
 * @param Kd_ Derivative gain  
 * @param dt_ Time step
 */
PID_ruslan::PID_ruslan(double Kp_, double Ki_, double Kd_, double dt_)
    : Kp(Kp_), Ki(Ki_), Kd(Kd_)
{
    if (dt_ <= 0.0) {
        std::cerr << "PID_ruslan::PID_ruslan: invalid dt <= 0, using DEFAULT_DT=" << DEFAULT_DT << "\n";
        dt = DEFAULT_DT;
    } else {
        dt = dt_;
    }
    inv_dt = 1.0 / dt;
}

/**
 * @brief Compute PID control signal
 * @param setpoint Desired setpoint
 * @param measured Current measured value
 * @return Control output signal
 */
double PID_ruslan::compute(double setpoint, double measured) noexcept {
    const double error = setpoint - measured;

    // Integral component with anti-windup
    integral = std::clamp(integral + error * dt, integral_min, integral_max);

    // Derivative component
    double derivative = 0.0;
    if (prev_error_initialized) {
        derivative = (error - prev_error) * inv_dt;
    } else {
        prev_error_initialized = true;
    }
    prev_error = error;

    // PID output (with clamping)
    const double output = Kp * error + Ki * integral + Kd * derivative;
    return std::clamp(output, output_min, output_max);
}

/**
 * @brief Reset PID controller internal state
 */
void PID_ruslan::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
    prev_error_initialized = false;
}

/**
 * @brief Set output limits for controller
 * @param min Minimum output value
 * @param max Maximum output value
 */
void PID_ruslan::setOutputLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID_ruslan::setOutputLimits ignored invalid limits: min > max\n";
        return;
    }
    output_min = min;
    output_max = max;
}

/**
 * @brief Set integral limits for anti-windup
 * @param min Minimum integral value
 * @param max Maximum integral value
 */
void PID_ruslan::setIntegralLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID_ruslan::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }

    integral_min = min;
    integral_max = max;

    // Clamp current integral to new bounds
    integral = std::clamp(integral, integral_min, integral_max);
}

/**
 * @brief Set new time step for controller
 * @param new_dt New time step value
 */
void PID_ruslan::setDt(double new_dt) {
    if (new_dt <= 0.0) {
        std::cerr << "PID_ruslan::setDt ignored invalid dt <= 0\n";
        return;
    }
    dt = new_dt;
    inv_dt = 1.0 / dt;
}