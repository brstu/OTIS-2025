#include "pid.hpp"
#include <algorithm>

PIDController::PIDController(double kp, double ki, double kd, 
                             double min_out, double max_out,
                             double min_int, double max_int,
                             double step_time) 
    : Kp(kp), Ki(ki), Kd(kd),
      min_output(min_out), max_output(max_out),
      min_integral(min_int), max_integral(max_int),
      dt(step_time) {
    reset();
}

double PIDController::calculate(double setpoint, double measured_value) {
    double error = setpoint - measured_value;
    double P = Kp * error;
    
    integral += error * dt;
    integral = std::clamp(integral, min_integral, max_integral);
    double I = Ki * integral;
    
    double derivative = (error - prev_error) / dt;
    double D = Kd * derivative;

    prev_error = error;
    double output = P + I + D;

    return std::clamp(output, min_output, max_output);
}

void PIDController::reset() {
    integral = 0.0;
    prev_error = 0.0;
}

void PIDController::setParameters(double kp, double ki, double kd) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
}

void PIDController::setOutputLimits(double min, double max) {
    min_output = min;
    max_output = max;
}

void PIDController::setIntegralLimits(double min, double max) {
    min_integral = min;
    max_integral = max;
}