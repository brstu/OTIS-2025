#pragma once

/**
 * @brief Дискретный ПИД-регулятор в рекуррентной форме
 */
class PIDController {
public:
    explicit PIDController(double Kp = 1.0, double Ti = 1e12, double Td = 0.0,
                           double dt = 1.0, double u_min = 0.0, double u_max = 100.0);

    double calculate(double setpoint, double measured);
    void reset();
    void setParameters(double Kp, double Ti, double Td);

private:
    void updateCoefficients();

    double Kp_   = 0.0;
    double Ti_   = 0.0;
    double Td_   = 0.0;
    double dt_   = 0.0;
    double u_min_ = 0.0;
    double u_max_ = 0.0;

    double q0{};
    double q1{};
    double q2{};

    double u_prev_  = 0.0;
    double e_prev1_ = 0.0;
    double e_prev2_ = 0.0;
};