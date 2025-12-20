#include "pid.h"

PID::PID(double kp_, double ki_, double kd_)
    : kp(kp_), ki(ki_), kd(kd_), prev_error(0.0), integral(0.0) {}

void PID::setCoefficients(double kp_, double ki_, double kd_) {
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

double PID::compute(double setpoint, double measurement, double dt) {
    if (dt <= 0.0) {
        // Защита от некорректного шага
        return 0.0;
    }

    double error = setpoint - measurement;

    // Интеграл
    integral += error * dt;

    // Производная (по времени)
    double derivative = (error - prev_error) / dt;

    prev_error = error;

    return kp * error + ki * integral + kd * derivative;
}

void PID::reset() {
    prev_error = 0.0;
    integral = 0.0;
}
