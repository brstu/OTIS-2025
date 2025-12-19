#include "pid.hpp"
#include <algorithm>

PIDController::PIDController(PIDParameters param) 
{
    params = param;
    reset();
}

double PIDController::calculate(double setpoint, double measured_value) {
    double error = setpoint - measured_value;
    double P = params.Kp * error;
    
    integral += error * params.dt;
    integral = std::clamp(integral, params.min_integral, params.max_integral);
    double I = params.Ki * integral;
    
    double derivative = (error - prev_error) / params.dt;
    double D = params.Kd * derivative;

    prev_error = error;
    double output = P + I + D;

    return std::clamp(output, params.min_output, params.max_output);
}

void PIDController::reset() {
    integral = 0.0;
    prev_error = 0.0;
}

void PIDController::setParameters(double kp, double ki, double kd) {
    params.Kp = kp;
    params.Ki = ki;
    params.Kd = kd;
}

void PIDController::setOutputLimits(double min, double max) {
    params.min_output = min;
    params.max_output = max;
}

void PIDController::setIntegralLimits(double min, double max) {
    params.min_integral = min;
    params.max_integral = max;
}