#include "pid.h"
#include <algorithm>
#include <iostream>

// Constructor
PID::PID(double Kp_, double Ki_, double Kd_, double dt_)
    : Kp(Kp_), Ki(Ki_), Kd(Kd_)
{
    if (dt_ <= 0.0) {
        std::cerr << "PID::PID: invalid dt <= 0, using DEFAULT_DT=" << DEFAULT_DT << "\n";
        dt = DEFAULT_DT;
    } else {
        dt = dt_;
    }
    inv_dt = 1.0 / dt;
}

// Compute control signal
double PID::compute(double setpoint, double measured) noexcept {
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

// Reset PID state
void PID::reset() noexcept {
    prev_error = 0.0;
    integral = 0.0;
    prev_error_initialized = false;
}

// Set output limits
void PID::setOutputLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID::setOutputLimits ignored invalid limits: min > max\n";
        return;
    }
    output_min = min;
    output_max = max;
}

// Set integral limits
void PID::setIntegralLimits(double min, double max) {
    if (min > max) {
        std::cerr << "PID::setIntegralLimits ignored invalid limits: min > max\n";
        return;
    }

    integral_min = min;
    integral_max = max;

    // Clamp current integral to new bounds
    integral = std::clamp(integral, integral_min, integral_max);
}

// Change sampling time
void PID::setDt(double new_dt) {
    if (new_dt <= 0.0) {
        std::cerr << "PID::setDt ignored invalid dt <= 0\n";
        return;
    }
    dt = new_dt;
    inv_dt = 1.0 / dt;
}
